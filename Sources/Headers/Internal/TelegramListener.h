#ifndef TELEGRAMLISTENER_H
#define TELEGRAMLISTENER_H

#include "Types/Update.h"
#include "Types/Error.h"
#include "BotSettings.h"

#include "qobject.h"
#include "qtcpserver.h"

namespace Telegram { namespace Internal {

	class TelegramListener : public QTcpServer {
		Q_OBJECT

	public:
		TelegramListener(const std::shared_ptr<Telegram::BotSettings>& bot_settings);

	signals:
		void updateReceived(Update update);
		void errorOccured(Error error);

	private:
		std::shared_ptr<Telegram::BotSettings> bot_settings;

		void incomingConnection(qintptr socketDescriptor) override;

		void addConnectedSocket(QSslSocket* socket);
		void removeConnectedSocket(QSslSocket* socket);
		QString* getSocketBuffer(QSslSocket* socket);
		void socketReadyRead(QSslSocket* socket);
		
		QMap<QSslSocket*, QString> sockets_and_buffers;
	};
}}

#endif /* TELEGRAMLISTENER_H */