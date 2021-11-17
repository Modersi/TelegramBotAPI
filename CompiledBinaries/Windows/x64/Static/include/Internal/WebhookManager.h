#ifndef TELEGRAM_WEBHOOKMANAGER_H
#define TELEGRAM_WEBHOOKMANAGER_H

#include "qtcpserver.h"
#include "qsslconfiguration.h"

#include "Types/Update.h"
#include "BotSettings.h"

namespace Telegram
{
	class WebhookManager : public QTcpServer
	{
		Q_OBJECT

	public:
		WebhookManager(const BotSettings& bot_settings);

	signals:
		void UpdateReceived(Update* update);

	protected:
		void incomingConnection(qintptr socketDescriptor) override;

	private slots:
		void SocketReadyToRead();
		void SocketDisconnected();

	private:
		QSslConfiguration ssl_configuration;
	};
}

#endif // TELEGRAM_WEBHOOKMANAGER_H
