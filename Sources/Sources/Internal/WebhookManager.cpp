#include "qsslsocket.h"
#include "qsslkey.h"
#include "qsslcertificate.h"
#include "qfile.h"
#include "qjsondocument.h"
#include "qjsonobject.h"

#include "Internal/WebhookManager.h"

#define SEND_200_RESPONSE(socket) 		socket->write("HTTP/1.1 200 Ok\r\n");			\
										socket->write("Content-Length: 0\r\n");			\
										socket->write("Connection: keep-alive\r\n");	\
										socket->write("\r\n");							\
										socket->write("");								\

#define SEND_400_RESPONSE(socket) 		socket->write("HTTP/1.1 400 Bad Request\r\n");	\
										socket->write("Content-Length: 0\r\n");			\
										socket->write("Connection: keep-alive\r\n");	\
										socket->write("\r\n");							\
										socket->write("");								\

Telegram::WebhookManager::WebhookManager(const Telegram::BotSettings& bot_settings) :
	ssl_configuration(*bot_settings.ssl_configuration),
	QTcpServer()
{
	listen(bot_settings.host_addres.value_or(QHostAddress::LocalHost), bot_settings.port.value_or(443));

#ifdef DEBUG_MODE
	qDebug() << endl << "---| Webhook server information: ";
	qDebug() << "Server is listening: " << isListening();
	qDebug() << "Adress: " << serverAddress().toString();
	qDebug() << "Port: " << serverPort();
	qDebug() << "Error: " << errorString();
#endif
}

void Telegram::WebhookManager::incomingConnection(qintptr socketDescriptor)
{
	QSslSocket* socket = new QSslSocket();
	if (socket->setSocketDescriptor(socketDescriptor))
	{
		QObject::connect(socket, &QSslSocket::readyRead,
						 this, &WebhookManager::SocketReadyToRead);

		QObject::connect(socket, &QSslSocket::disconnected,
						 this, &WebhookManager::SocketDisconnected);

		socket->setSslConfiguration(ssl_configuration);
		socket->startServerEncryption();
		addPendingConnection(socket);
	}
	else delete socket;

#ifdef DEBUG_MODE
	qDebug() << endl << "---| Incoming connection received. Adress: " << socket->peerAddress().toString();
#endif
}

void Telegram::WebhookManager::SocketReadyToRead()
{
	QSslSocket* socket = qobject_cast<QSslSocket*>(QObject::sender());

#ifdef DEBUG_MODE
	qDebug() << endl << "---| Socket is ready to read. Adress: " << socket->peerAddress().toString();;
#endif

	QString incoming_data(socket->readAll());

	/* Trying to find begining of JSON object in received HTTP request */
	int index_of_request_body_begin(incoming_data.indexOf('{'));
	if (index_of_request_body_begin == -1) {
		SEND_200_RESPONSE(socket);
		return;
	}

	/* Creating a reference to substring of HTTP request which is contain JSON data */
	QStringRef request_body(&incoming_data, index_of_request_body_begin, (incoming_data.size() - index_of_request_body_begin)); // From indexOfRequestBodyBegin till end of HTTP request

	/* Creating an Update object from received JSON data and emiting signal that shows the new update is received */
	Update* received_update = new Update(QJsonDocument::fromJson(request_body.toUtf8()).object());
	emit UpdateReceived(received_update);

#ifdef DEBUG_MODE
	qDebug() << endl << "Received data: " << incoming_data
	<< endl << "Index of request body begin: " << index_of_request_body_begin
	<< endl << "Request body: " << request_body;
#endif
	SEND_200_RESPONSE(socket);
}

void Telegram::WebhookManager::SocketDisconnected()
{
	QSslSocket* socket = qobject_cast<QSslSocket*>(QObject::sender());
	socket->deleteLater();

#ifdef DEBUG_MODE
	qDebug() << endl << "---| Socket disconnected. Adress: " << socket->peerAddress().toString();
#endif
}

