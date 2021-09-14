#ifndef TELEGRAM_WEBHOOKMANAGER_H
#define TELEGRAM_WEBHOOKMANAGER_H

#include "Types/Update.h"

#include "qtcpserver.h"
#include "qsslconfiguration.h"

/* IP address for WebhookServer to be hosted */
#define HOST_ADRESS	"192.168.0.99" 

/* Port for Webhook server to listen for connections */
#define PORT 443

/* Path to SSL certificate file */
#define SSL_CERTIFICATE_PATH "C:/Non-system/GitHubRepositories/Modersi/TelegramBotAPI/SSL Certificate/telegrambotapi.com/telegrambotapi.crt"

/* Path to CA SSL certificate file */
#define CA_SSL_CERTIFICATE_PATH "C:/Non-system/GitHubRepositories/Modersi/TelegramBotAPI/SSL Certificate/telegrambotapi.com/ca.crt"

/* Path to SSL private key */
#define PRIVATE_KEY_PATH "C:/Non-system/GitHubRepositories/Modersi/TelegramBotAPI/SSL Certificate/telegrambotapi.com/private.key"

namespace Telegram
{
	class WebhookManager : public QTcpServer
	{
		Q_OBJECT

	public:
		WebhookManager();

	signals:
		void UpdateReceived(Update* update);

	protected:
		void incomingConnection(qintptr socketDescriptor) override;

	private slots:
		void SocketReadyToRead();
		void SocketDisconnected();

	private:
		void ConfigureSSL(const QString& certificatePath, const QString& caCertificatePath, const QString& privateKeyPath);
		QSslConfiguration SSLConfiguration;
	};
}

#endif // TELEGRAM_WEBHOOKMANAGER_H
