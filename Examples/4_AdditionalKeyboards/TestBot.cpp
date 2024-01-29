#include "TestBot.h"

using namespace Telegram;

TestBot::TestBot(const std::shared_ptr<BotSettings>& bot_settings) :
	QObject(),
	telegram_bot(bot_settings)
{
	//	Telegram::Bot::errorOccured is emitted every time when the negative response is received from the Telegram server and holds an Error object in arguments. Error class contains the occurred error description and code. See Error.h for details
	connect(&telegram_bot, &Bot::errorOccured, this, &TestBot::onErrorOccured);
	
	//	Telegram::Bot::networkErrorOccured is emitted every time when there is an error while receiving Updates from the Telegram. Error class contains the occurred error description and code. See Error.h for details
	connect(&telegram_bot, &Bot::networkErrorOccured, this, &TestBot::onNetworkErrorOccured);

	//	Detecting incoming callback data from the button and aswering with an info about callback query
	QObject::connect(&telegram_bot, &Bot::callbackQueryReceived, [&] (qint32 message_id, CallbackQuery callback_query) {
		QString callback_query_answer =
			"\nCallback query received!"
			"\nId: " + callback_query.id +
			"\nFrom: " + callback_query.from.first_name +
			"\nChat instance: " + callback_query.chat_instance;

		telegram_bot.answerCallbackQuery(callback_query.id, callback_query_answer, true);
	});

	//	Detecting incoming inline queries from the user and answering with an info about inline query. See Example_InlineMode for more info
	QObject::connect(&telegram_bot, &Bot::inlineQueryReceived, [&](qint32 message_id, InlineQuery inline_query) {
		QString inline_query_reply =
			"\nInline query received:"
			"\nId: " + inline_query.id +
			"\nFirst name: " + inline_query.from.first_name +
			"\nQuery: " + inline_query.query;
			
		telegram_bot.answerInlineQuery(inline_query.id, { std::make_shared<InlineQueryResultArticle>("test_id", "Inline query received!", std::make_shared<InputTextMessageContent>(inline_query_reply)).get() });
	});

	//	Setting bot commands. If you will do this the Telegram will show hints when somebody typing commands to your bot
	telegram_bot.setMyCommands(bot_commands);

	//	Parsing incoming messages for commands
	QObject::connect(&telegram_bot, &Bot::messageReceived, [&](qint32 update_id, Message message) {
		if (message.text.has_value() == false) return;

		if		(message.text == "/send_inline_keyboard")		sendInlineKeyboard(message.chat->id);
		else if (message.text == "/send_reply_keyboard")		sendReplyKeyboard(message.chat->id);
		else if (message.text == "/remove_reply_keyboard")		removeReplyKeyboard(message.chat->id);
		else if (message.text == "/force_reply")				forceReply(message.chat->id);
	});
}

//	You can attach different additional interface elements that look like buttons under your message or like buttons that appear instead of your default keyboard
// 
//	List of additional interface elements:
//		● InlineKeyboardMarkup	- This struct represents an inline keyboard that appears right next to the message it belongs to. Contains QVector of button rows, each represented by a QVector of InlineKeyboardButton objects. See InlineKeyboardButton.h and InlineKeyboardMarkup.h for details
//		● ReplyKeyboardMarkup	- This struct represents a custom keyboard with reply options. Contains QVector of button rows, each represented by a QVector of KeyboardButton objects. See KeyboardButton.h and ReplyKeyboardMarkup.h for details
//		● ReplyKeyboardRemove	- Upon receiving a message with this object, Telegram clients will remove the current custom keyboard and display the default letter-keyboard. See ReplyKeyboardRemove.h for details
//		● ForceReply			- Upon receiving a message with this object, Telegram clients will display a reply interface to the user (act as if the user has selected the bot's message and tapped 'Reply'). See ForceReply.h for details
// 
//  In order to add additional interfaces to your message you have to specify reply_markup argument when you call the function. Usually, reply_markup is the last argument of such functions
// 
//	List of functions that can be used with additional interfaces:
//		● sendMessage()
//		● copyMessage()
//		● sendPhoto()
//		● sendAudio()
//		● sendDocument()
//		● sendVideo()
//		● sendAnimation()
//		● sendVoice()
//		● sendVideoNote()
//		● sendLocation()
//		● editMessageLiveLocation()
//		● sendVenue()
//		● sendContact()
//		● sendPoll()
//		● sendDice()
//		● editMessageText()
//		● editMessageCaption()
//		● editMessageMedia()
//		● editMessageReplyMarkup()
//		● stopPoll()
//		● sendSticker()

void TestBot::sendInlineKeyboard(const qint32& chat_id) {
	//	Creating all available inline buttons:
	//
	//	● URL button. Offers user to open a link
	InlineKeyboardButton url_button("URL button", "https://core.telegram.org/bots/api");
	//
	//	● Login button. Open specified link with the following parameters from the Telegram in URL query: id, first_name, last_name, username, photo_url, auth_date, and hash;
	InlineKeyboardButton login_button("Login button", std::nullopt, LoginURL("https://telegrambotapi.com"));
	//
	//	● Callback button. Data to be sent in a callback query to the bot when button is pressed, 1-64 bytes. Can be obtained from signal callbackQueryReceived(qint32 update_id, CallbackQuery callback_query)
	InlineKeyboardButton callback_button("Callback button", std::nullopt, std::nullopt, "Test call back data");
	//
	//  ● Switch inline query button. Pressing this button will prompt the user to select one of their chats, open that chat and insert the bot's username and the specified inline query in the input field. Can be empty, in which case just the bot's username will be inserted. Inline query can be obtained from signal inlineQueryReceived(qint32 message_id, Telegram::InlineQuery inline_query)
	InlineKeyboardButton switch_inline_query_button("Switch inline query button", std::nullopt, std::nullopt, std::nullopt, "TestQuery");
	//
	//	● Switch inline query current chat button. Pressing this button will insert the bot's username and the specified inline query in the current chat's input field. Can be empty, in which case only the bot's username will be inserted. Inline query can be obtained from signal inlineQueryReceived(qint32 message_id, Telegram::InlineQuery inline_query)
	InlineKeyboardButton switch_inline_query_current_chat_button("Switch inline query current chat button", std::nullopt, std::nullopt, std::nullopt, std::nullopt, "TestQuery");
	//
	// 	● Callback game button. Description of the game that will be launched when the user presses the button. NOTE: This type of button must always be the first button in the first row
	//InlineKeyboardButton callback_game_button("Callback game button", std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt, "Test call back game secription");
	//
	//	● Specify True, to send a Pay button. NOTE: This type of button must always be the first button in the first row
	// In progress // InlineKeyboardButton pay_button("Pay button", std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt, true);


	//	Combining all available buttons in markup. Since the callback game button and the pay button must be first in a row we can't group them here, they will be sent separately
	InlineKeyboardMarkup inline_keyboard_markup = {
		{url_button, login_button},
		{callback_button},
		{switch_inline_query_button, switch_inline_query_current_chat_button}
	};


	// Sending all inline buttons
	telegram_bot.sendMessage({ .chat_id = chat_id, .text = "Inline buttons:", .reply_markup = inline_keyboard_markup });
	// In progress // telegram_bot.sendMessage(chat_id, "Pay button test:", std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt, InlineKeyboardMarkup({ {pay_button} }));
}

void TestBot::sendReplyKeyboard(const qint32& chat_id) {
	//	Creating all available reply buttons:
	//
	//	● Text button. When you will press this button message with the button's text will be sent
	KeyboardButton text_button("Text button");
	//
	//	● Request contact button. The user's phone number will be sent as a contact when the button is pressed. Available in private chats only 
	KeyboardButton request_contact_button("Request contact", true);
	//
	//	● Request location button. The user's current location will be sent when the button is pressed.. Available in private chats only
	KeyboardButton request_location_button("Request location", std::nullopt, true);
	//
	//	● Request poll button. The user will be asked to create a poll and send it to the bot when the button is pressed. Available in private chats only
	KeyboardButton poll_button("Poll button", std::nullopt, std::nullopt, KeyboardButtonPollType(Poll::Type::REGULAR));


	//	Combining all buttons in markup
	ReplyKeyboardMarkup reply_keyboard_markup = {
		{text_button},
		{request_contact_button, request_location_button, poll_button}
	};


	// Sending reply keyboard
	telegram_bot.sendMessage({ .chat_id = chat_id, .text = "Reply buttons", .reply_markup = reply_keyboard_markup });
}

void TestBot::removeReplyKeyboard(const qint32& chat_id) {
	//	Removing reply keyboard
	telegram_bot.sendMessage({ .chat_id = chat_id, .text = "Removing reply keyboard!", .reply_markup = ReplyKeyboardRemove() });
}

void TestBot::forceReply(const qint32& chat_id) {
	//	Forcing reply
	telegram_bot.sendMessage({ .chat_id = chat_id, .text = "Forcing reply!", .reply_markup = ForceReply("Example input field!") });
}

void TestBot::onErrorOccured(Error error) {
	qDebug() << "\n" << "--| Error occured:"
			 << "\n" << "Error code: " << error.error_code
			 << "\n" << "Description: " << error.description;
}

void TestBot::onNetworkErrorOccured(Error error) {
	qDebug() << "\n" << "--| Network error occured:"
			 << "\n" << "Error code: " << error.error_code
			 << "\n" << "Description: " << error.description;
}

