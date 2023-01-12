#include "TelegramBotAPI.h"

#include "qobject.h"

using namespace Telegram;

class TestBot : public QObject {
	Q_OBJECT

public:
	TestBot(const QVector<BotCommand>& bot_commands, const std::shared_ptr<BotSettings>& bot_settings = std::make_shared<BotSettings>());

signals:
	// Emitted when any command is received
	void commandReceived(const std::shared_ptr<Chat>& chat, const QString& command);

private slots:
	// Emitted when an error with Telegram Bot API has occurred, prints error description in the console
	void onErrorOccured(Error error);

	// Emitted when a network error has occurred, prints error code and description in the console
	void onNetworkErrorOccured(Error error);

public:
	Bot telegram_bot;
	QVector<BotCommand> bot_commands;
};
