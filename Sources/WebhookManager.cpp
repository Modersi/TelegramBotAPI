#include "WebhookManager.h"

#include "qhostaddress.h"
#include "qsslsocket.h"
#include "qsslconfiguration.h"
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

Telegram::WebhookManager::WebhookManager() :
	QTcpServer(nullptr),
	SSLConfiguration()
{
	ConfigureSSL(SSL_CERTIFICATE_PATH, CA_SSL_CERTIFICATE_PATH, PRIVATE_KEY_PATH);
	listen(QHostAddress(HOST_ADRESS), PORT);

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

		socket->setSslConfiguration(SSLConfiguration);
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

void Telegram::WebhookManager::ConfigureSSL(const QString& certificatePath, const QString& caCertificatePath, const QString& privateKeyPath)
{
	/* Creating and opening all files related to SSL */
	auto CreateAndOpenQFile = [](const QString& pathToFile) { QFile* file = new QFile(pathToFile); file->open(QIODevice::ReadOnly); return file; };
	std::shared_ptr<QFile> certificateFile(CreateAndOpenQFile(certificatePath));
	std::shared_ptr<QFile> caCertificateFile(CreateAndOpenQFile(caCertificatePath));
	std::shared_ptr<QFile> privateKeyFile(CreateAndOpenQFile(privateKeyPath));
	
	/* Setting up server SSL configuration */
	SSLConfiguration.setLocalCertificate(QSslCertificate(certificateFile.get()));
	SSLConfiguration.addCaCertificate(QSslCertificate(caCertificateFile.get()));
	SSLConfiguration.setPrivateKey(QSslKey(privateKeyFile.get(), QSsl::KeyAlgorithm::Rsa));
	SSLConfiguration.setPeerVerifyMode(QSslSocket::VerifyNone);

#ifdef DEBUG_MODE
	qDebug() << endl << "-| SSL configuration information |-";
	qDebug() << "SSL certificate file is open: " << certificateFile->isOpen();
	qDebug() << "SSL certificate is null: " << SSLConfiguration.localCertificate().isNull();
	qDebug() << "CA SSL certificate file is open: " << caCertificateFile->isOpen();
	qDebug() << "CA SSL certificate is null: " << SSLConfiguration.caCertificates()[0].isNull();
	qDebug() << "SSL private key file is open: " << privateKeyFile->isOpen();
	qDebug() << "SSL private key is null: " << SSLConfiguration.privateKey().isNull();
#endif
}

