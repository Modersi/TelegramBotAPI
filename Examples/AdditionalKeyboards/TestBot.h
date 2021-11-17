#include "qobject.h"

//	Including library main header
#include "TelegramBotAPI.h"

class TestBot : public QObject
{
	Q_OBJECT

public:
	TestBot(const Telegram::BotSettings& bot_settings = Telegram::BotSettings());

	//	Contains an example of how to send an inline keyboard
	void sendInlineKeyboard(const qint32& chat_id);

	//	Contains an example of how to send an reply keyboard
	void sendReplyKeyboard(const qint32& chat_id);

	//	Contains an example of how to hide an reply keyboard
	void removeReplyKeyboard(const qint32& chat_id);

	//	Contains an example of how to force reply on the message
	void forceReply(const qint32& chat_id);

private slots:
	//	Emitted when an error occurred
	void Error(Telegram::Error error);

private:
	Telegram::Bot telegram_bot;

	//	List of bot commands 
	QVector<Telegram::BotCommand> bot_commands = { Telegram::BotCommand("send_inline_keyboard", "Sends example of inline keyboard!"),
												   Telegram::BotCommand("send_reply_keyboard", "Sends example of reply keyboard!"),
												   Telegram::BotCommand("remove_reply_keyboard", "Removes reply keyboard!"),
												   Telegram::BotCommand("force_reply", "Forces you to reply on this message!") };
};