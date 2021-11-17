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
		WebhookManager(const BotSettings& bot_settings = BotSettings());

	signals:
		void UpdateReceived(Update* update);

	protected:
		void incomingConnection(qintptr socketDescriptor) override;

	private slots:
		void SocketReadyToRead();
		void SocketDisconnected();

	private:
		BotSettings bot_settings;
	};
}

#endif // TELEGRAM_WEBHOOKMANAGER_H
