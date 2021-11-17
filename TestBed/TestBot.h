#include "TelegramBotAPI.h"

#include "qobject.h"

class TestBot : public QObject
{
	Q_OBJECT

public:
	TestBot(const QVector<Telegram::BotCommand>& bot_commands, const Telegram::BotSettings& bot_settings = Telegram::BotSettings());

signals:
	// Emitted when any command received
	void commandReceived(const Telegram::User& from, const QString command);

private slots:;
	//	Emitted when any error with Telegram Bot API is occcured, prints error description to the console
	void onErrorOccured(Telegram::Error error);

public:
	Telegram::Bot telegram_bot;
	QVector<Telegram::BotCommand> bot_commands;
};
