#include "qcoreapplication.h"

#include "TelegramBotAPI.h"

using namespace Telegram;

int main(int argc, char* argv[]) {

	QCoreApplication core_application(argc, argv);

    // Creating instance of the Telegram bot, using the bot settings file from the project root directory
    Bot test_bot;

    //	Telegram::Bot::errorOccured is emitted every time when the negative response is received from the Telegram server and holds an Error object in arguments. Error class contains the occurred error description and code. See Error.h for details
	QObject::connect(&test_bot, &Bot::errorOccured, [](Error error) {
		qDebug() << "\n" << "--| Error occured:"
				 << "\n" << "Error code: " << error.error_code
				 << "\n" << "Description: " << error.description;
	});

	//	Telegram::Bot::networkErrorOccured is emitted every time when there is an error while receiving Updates from the Telegram. Error class contains the occurred error description and code. See Error.h for details
	QObject::connect(&test_bot, &Bot::networkErrorOccured, [](Error error) {
		qDebug() << "\n" << "--| Network error occured:"
				 << "\n" << "Error code: " << error.error_code
				 << "\n" << "Description: " << error.description;
	});

    //	All incomings messages can be handled using Qt signal-slot system. An instance of the Telegram::Bot class emitting different signals when bot receives an update from the Telegram
    //
    // 	List of all available signals and their description:
    //      ● messageReceived(qint32 update_id, Message message) - Emitted when the bot receives a new incoming message of any kind - text, photo, sticker, etc.
    //      ● messageWasUpdated(qint32 update_id, Message message) - Emitted when the bot receives a version of a message that is known to the bot and was edited
    //      
    //      ● channelPostReceived(qint32 update_id, Message message) - Emitted when the bot receives a new incoming channel post of any kind - text, photo, sticker, etc.
    //      ● channelPostWasUpdated(qint32 update_id, Message message) - Emitted when the bot receives a new version of a channel post that is known to the bot and was edited
    //      
    //      ● inlineQueryReceived(qint32 update_id, InlineQuery inline_query) - Emitted whe then bot receives a new incoming inline query
    //      ● chosenInlineResult(qint32 update_id, ChosenInlineResult chosen_inline_result) - Emitted when the bot receives the result of an inline query that was chosen by a user and sent to their chat partner. Please see Telegram documentation(https://core.telegram.org/bots/inline#collecting-feedback) for details on how to enable these updates for your bot
    //      
    //      ● pollReceived(qint32 update_id, Poll poll) - Emitted when the bot receives a new poll state. Bots receive only updates about stopped polls and polls, which are sent by the bot
    //      ● pollAnswerReceived(qint32 update_id, PollAnswer poll_answer) - Emitted when a user changed their answer in a non-anonymous poll. bot receives new votes only in polls that were sent by the bot itself
    //
    //      ● myChatMemberStatusUpdated(qint32 update_id, ChatMemberUpdated chat_member_update) - Emitted when the bot's chat member status was updated in a chat. For private chats, this update is received only when the bot is blocked or unblocked by the user
    //      ● chatMemberStatusUpdated(qint32 update_id, ChatMemberUpdated chat_member_update) - Emitted when chat member's status was updated in a chat. The bot must be an administrator in the chat and must explicitly specify "chat_member" in the list of allowed_updates in the BotSettings to receive these updates
    //  
    //      ● callbackQueryReceived(qint32 update_id, CallbackQuery callback_query) - Emitted when the bot receives new incoming callback query
    //	
    //      -------    
    //      **update_id - The update's unique identifier. Update identifiers start at a certain positive number and increase sequentially. This ID becomes especially handy if you're using Webhooks since it allows you to ignore repeated updates or to restore the correct update sequence, should they get out of order. If there are no new updates for at least a week, then the identifier of the next update will be chosen randomly instead of sequentially
    //	
    //  So you can easily connect needed signals to your slot. For example, we will make a simple echo bot below:

    // Connecting messageReceived() signal to a lambda that sends the received message back to the sender
    QObject::connect(&test_bot, &Bot::messageReceived, [&](qint32 update_id, Message message) { 
        test_bot.sendMessage(message.chat->id, message.text.value_or("")); 
    });

	return core_application.exec();
}