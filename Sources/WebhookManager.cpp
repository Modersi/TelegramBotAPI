#include "WebhookManager.h"

#include "qsslsocket.h"
#include "qsslkey.h"
#include "qsslcertificate.h"
#include "qfile.h"
#include "qjsondocument.h"
#include "qjsonobject.h"

//#define DEBUG_MODE

void Send200OkResponse(QSslSocket* socket)
{
	socket->write("HTTP/1.1 200 Ok\r\n");
	socket->write("Content-Length: 0\r\n");
	socket->write("Connection: keep-alive\r\n");
	socket->write("\r\n");
	socket->write("");
}

Telegram::WebhookManager::WebhookManager(const BotSettings& bot_settings) :
	QTcpServer(nullptr),
	bot_settings(bot_settings)
{
	listen(bot_settings.host_addres, bot_settings.port);

#ifdef DEBUG_MODE
	qDebug() << endl << "-| Server information |-";
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

		socket->setSslConfiguration(bot_settings.ssl_configuration);
		socket->startServerEncryption();
		addPendingConnection(socket);
	}
	else
		delete socket;

#ifdef DEBUG_MODE
	qDebug() << endl << "-| Incoming connection received |-";
	qDebug() << "Peer Adress: " << socket->peerAddress().toString();
	qDebug() << "Port: " << socket->localPort();
#endif
}

void Telegram::WebhookManager::SocketReadyToRead()
{
	QSslSocket* socket = qobject_cast<QSslSocket*>(QObject::sender());
#ifdef DEBUG_MODE
	qDebug() << endl << "-| Socket is ready to read |-";
	qDebug() << "Peer Adress: " << socket->peerAddress().toString();
	qDebug() << "Port: " << socket->localPort();
#endif

	/* Reading all received data from socket. It must be an HTTP request */
	QString HTTPRequest(socket->readAll());

	/* Trying to find begining of JSON object in received HTTP request */
	int indexOfRequestBodyBegin(HTTPRequest.indexOf('{'));
	if (indexOfRequestBodyBegin == -1)
	{
		Send200OkResponse(socket);
		return;
	}

	/* Creating a reference to substring of HTTP request which is contain JSON data */
	QStringRef requestbody(&HTTPRequest, indexOfRequestBodyBegin, (HTTPRequest.size() - indexOfRequestBodyBegin)); // From indexOfRequestBodyBegin till end of HTTP request

	/* Creating an Update object from received JSON data and emiting signal that shows the new update is received */
	Update* receivedUpdate = new Update(QJsonDocument::fromJson(requestbody.toUtf8()).object());
	emit UpdateReceived(receivedUpdate);

#ifdef DEBUG_MODE
	qDebug() << endl << "Received data: " << HTTPRequest;
	qDebug() << endl << "Index of request body begin: " << indexOfRequestBodyBegin;
	qDebug() << "Request body: " << requestbody;
#endif
	Send200OkResponse(socket);
}

void Telegram::WebhookManager::SocketDisconnected()
{
	/* Destroy memory related to last connected socket */
	QSslSocket* socket = qobject_cast<QSslSocket*>(QObject::sender());
	socket->deleteLater();

#ifdef DEBUG_MODE
	qDebug() << endl << "-| Socket disconnected |-";
	qDebug() << "Peer Adress: " << socket->peerAddress().toString();
	qDebug() << "Port: " << socket->localPort();
#endif
}

