#include "Internal/TelegramListener.h"

#include <exception>

#include "qjsondocument.h"
#include "qsslsocket.h"
#include "qsslerror.h"
#include "qstring.h"
#include "qmap.h"

Telegram::Internal::TelegramListener::TelegramListener(const std::shared_ptr<Telegram::BotSettings>& bot_settings) :
	QTcpServer(),
	bot_settings(bot_settings),
	sockets_and_buffers()
{
	if (bot_settings == nullptr) throw std::invalid_argument("bot_settings in TelegramListener is nullptr");
	if (bot_settings->ssl_configuration == std::nullopt) throw std::invalid_argument("bot_settings->ssl_configuration in TelegramListener is nullopt");
		
	QObject::connect(this, &QTcpServer::acceptError, [this](QAbstractSocket::SocketError error) {
		emit errorOccured({ "New connection attempt results in an error", error });
	});

	this->setMaxPendingConnections(bot_settings->max_connections.value_or(40));
	this->listen(bot_settings->host_addres.value_or(QHostAddress::LocalHost), bot_settings->port.value_or(443));
}

using HttpHeaders = QMultiMap<QString, QString>;
using HttpBody = QString;

std::optional<std::pair<HttpHeaders, HttpBody>> parseForPostRequest(QString* buffer) {

	if (buffer->contains("POST / HTTP") and buffer->contains("\r\n\r\n")) {
		HttpHeaders headers;

		/* Parsing for headers */
		auto headers_begin_index = buffer->indexOf("POST / HTTP");
		auto headers_end_index = buffer->indexOf("\r\n\r\n") + 4;
		auto headers_size = headers_end_index - headers_begin_index;

		auto raw_headers = buffer->sliced(headers_begin_index, headers_size).split("\r\n");
		for (auto&& raw_header : raw_headers) {
			if (auto&& header_delimer_index = raw_header.indexOf(": "); header_delimer_index != -1)
				headers.insert(
					raw_header.sliced(0, header_delimer_index),
					raw_header.sliced(header_delimer_index + 2)
				);
		}

		/* Return if buffer doesn't contain full HTTP request body */
		if (auto buffer_contains_full_body = buffer->count() >= headers_size + headers.value("Content-Length").toInt(); 
			buffer_contains_full_body == false) {
			return {};
		}

		/* Return if Content-Lenght is not provided or zero */
		if (headers.contains("Content-Length") == false or headers.value("Content-Length").toInt() == 0) {
			buffer->remove(headers_begin_index, headers_size);
			return { { headers, {} } };
		}


		/* Copying the request body */
		HttpBody body = buffer->sliced(headers_end_index, headers.value("Content-Length").toInt());

		/* Removing parsed request from buffer */
		buffer->remove(headers_begin_index, headers_size + headers.value("Content-Length").toInt());

		return { { headers, body } };
	}
	else return {};
}

void Telegram::Internal::TelegramListener::socketReadyRead(QSslSocket* socket) {
	if (socket == nullptr) return;

	auto socket_buffer = getSocketBuffer(socket);
	*socket_buffer += socket->readAll();

	if (auto http_request = parseForPostRequest(socket_buffer);
		http_request.has_value() and http_request->second.isEmpty() == false) 
	{
		static auto success_response = "HTTP/1.1 200 OK\r\nConnection: keep-alive\r\nContent-Length: 0\r\n\r\n";
		socket->write(success_response);

		if (http_request->first.contains("Content-Type") and http_request->first.value("Content-Type") == "application/json") 
			emit updateReceived(Telegram::Update(QJsonDocument::fromJson(http_request->second.toUtf8()).object()));
	}
}

void Telegram::Internal::TelegramListener::incomingConnection(qintptr socketDescriptor) {
	if (auto socket = new QSslSocket();
		socket->setSocketDescriptor(socketDescriptor))
	{
		addConnectedSocket(socket);
		socket->setSslConfiguration(*bot_settings->ssl_configuration);
		socket->startServerEncryption();

		addPendingConnection(socket);
	}
	else delete socket;
}

void Telegram::Internal::TelegramListener::addConnectedSocket(QSslSocket* socket) {
	sockets_and_buffers.insert(socket, {});

	QObject::connect(socket, &QSslSocket::readyRead, [this, socket]() {
		if (socket) socketReadyRead(socket);
	});

	QObject::connect(socket, &QSslSocket::disconnected, [this, socket]() {
		if (socket) removeConnectedSocket(socket);
	});

	QObject::connect(socket, &QSslSocket::errorOccurred, [this](QAbstractSocket::SocketError error) {
		emit errorOccured({ "Socket error occured", error });
	});

	QObject::connect(socket, &QSslSocket::sslErrors, [this](const QList<QSslError>& errors) {
		for (auto&& error : errors)
			emit errorOccured({ "Socket SSL error. " + error.errorString(), error.error() });
	});
}

void Telegram::Internal::TelegramListener::removeConnectedSocket(QSslSocket* socket) {
	if (socket == nullptr) return;

	socket->deleteLater();
	sockets_and_buffers.remove(socket);
}

QString* Telegram::Internal::TelegramListener::getSocketBuffer(QSslSocket* socket) {
	if (socket == nullptr) return nullptr;

	return &sockets_and_buffers[socket];
}
