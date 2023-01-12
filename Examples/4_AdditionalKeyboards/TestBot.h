#include "qobject.h"

#include "TelegramBotAPI.h"

using namespace Telegram;

class TestBot : public QObject {
	Q_OBJECT

public:
	TestBot(const std::shared_ptr<BotSettings>& bot_settings = BotSettings::makeFromFile());

	//	Contains an example of how to send an inline keyboard
	void sendInlineKeyboard(const qint32& chat_id);

	//	Contains an example of how to send a reply keyboard
	void sendReplyKeyboard(const qint32& chat_id);

	//	Contains an example of how to hide a reply keyboard
	void removeReplyKeyboard(const qint32& chat_id);

	//	Contains an example of how to force reply on the message
	void forceReply(const qint32& chat_id);

private slots:

	//	Emitted when an error with Telegram Bot API has occurred, prints error description in the console
	void onErrorOccured(Error error);

	//	Emitted when a network error has occurred, prints error code and description in the console
	void onNetworkErrorOccured(Error error);

private:
	Bot telegram_bot;

	QVector<BotCommand> bot_commands = { {"send_inline_keyboard",	"Sends example of an inline keyboard!"},							 
										 {"send_reply_keyboard",	"Sends example of a reply keyboard!"},							 
										 {"remove_reply_keyboard",	"Removes a reply keyboard!"},								 
										 {"force_reply",			"Forces you to reply on this message!"} };
};