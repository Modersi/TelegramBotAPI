#include "qcoreapplication.h"

//  Including library main header */
#include "TelegramBotAPI.h"

int main(int argc, char* argv[])
{
	QCoreApplication coreApplication(argc, argv);

	Telegram::Bot telegram_bot;

	//	Catching occured errors
	QObject::connect(&telegram_bot, &Telegram::Bot::errorOccured, [](Telegram::Error error) {
		qDebug() << "Error occured: " << error.description;
		qDebug() << "Error code: " << error.error_code;
	});

	//// GENERAL ////
	//
	//	Whenever the user typing "@bot_username" and some text after it in any chat your bot receives an incoming inline query, it can be obtained via Telegram::Bot::inlineQueryReceived() signal. This query holds a text that the user wrote and a lot of additional information about this query. See InlineQuery.h for more details
	//	You can answer this query using Telegram::Bot::answerInlineQuery() method to show to the user some results. You can send up to 50 results in answer to a query 
	//	
	//	Full list of all existing results listed below. See header file of every type of result or official Telegram Bot API documentation for more details
	//		• InlineQueryResultCachedAudio		- Represents a link to an MP3 audio file stored on the Telegram servers. By default, this audio file will be sent by the user. Alternatively, you can use input_message_content to send a message with the specified content instead of the audio.
	//		• InlineQueryResultCachedDocument	- Represents a link to a file stored on the Telegram servers. By default, this file will be sent by the user with an optional caption. Alternatively, you can use input_message_content to send a message with the specified content instead of the file
	//		• InlineQueryResultCachedGif		- Represents a link to an animated GIF file stored on the Telegram servers. By default, this animated GIF file will be sent by the user with an optional caption. Alternatively, you can use input_message_content to send a message with specified content instead of the animation
	//		• InlineQueryResultCachedMpeg4Gif	- Represents a link to a video animation (H.264/MPEG-4 AVC video without sound) stored on the Telegram servers. By default, this animated MPEG-4 file will be sent by the user with an optional caption. Alternatively, you can use input_message_content to send a message with the specified content instead of the animation
	//		• InlineQueryResultCachedPhoto		- Represents a link to a photo stored on the Telegram servers. By default, this photo will be sent by the user with an optional caption. Alternatively, you can use input_message_content to send a message with the specified content instead of the photo
	//		• InlineQueryResultCachedSticker	- Represents a link to a sticker stored on the Telegram servers. By default, this sticker will be sent by the user. Alternatively, you can use input_message_content to send a message with the specified content instead of the sticker
	//		• InlineQueryResultCachedVideo		- Represents a link to a video file stored on the Telegram servers. By default, this video file will be sent by the user with an optional caption. Alternatively, you can use input_message_content to send a message with the specified content instead of the video
	//		• InlineQueryResultCachedVoice		- Represents a link to a voice message stored on the Telegram servers. By default, this voice message will be sent by the user. Alternatively, you can use input_message_content to send a message with the specified content instead of the voice message
	//		• InlineQueryResultArticle			- Represents a link to an article or web page
	//		• InlineQueryResultAudio			- Represents a link to an MP3 audio file. By default, this audio file will be sent by the user. Alternatively, you can use input_message_content to send a message with the specified content instead of the audio
	//		• InlineQueryResultContact			- Represents a contact with a phone number. By default, this contact will be sent by the user. Alternatively, you can use input_message_content to send a message with the specified content instead of the contact
	//		• InlineQueryResultGame				- Represents a Game
	//		• InlineQueryResultDocument			- Represents a link to a file. By default, this file will be sent by the user with an optional caption. Alternatively, you can use input_message_content to send a message with the specified content instead of the file. Currently, only .PDF and .ZIP files can be sent using this method
	//		• InlineQueryResultGif				- Represents a link to an animated GIF file. By default, this animated GIF file will be sent by the user with optional caption. Alternatively, you can use input_message_content to send a message with the specified content instead of the animation
	//		• InlineQueryResultLocation			- Represents a location on a map. By default, the location will be sent by the user. Alternatively, you can use input_message_content to send a message with the specified content instead of the location
	//		• InlineQueryResultMpeg4Gif			- Represents a link to a video animation (H.264/MPEG-4 AVC video without sound). By default, this animated MPEG-4 file will be sent by the user with optional caption. Alternatively, you can use input_message_content to send a message with the specified content instead of the animation
	//		• InlineQueryResultPhoto			- Represents a link to a photo. By default, this photo will be sent by the user with optional caption. Alternatively, you can use input_message_content to send a message with the specified content instead of the photo
	//		• InlineQueryResultVenue			- Represents a venue. By default, the venue will be sent by the user. Alternatively, you can use input_message_content to send a message with the specified content instead of the venue
	//		• InlineQueryResultVideo			- Represents a link to a page containing an embedded video player or a video file. By default, this video file will be sent by the user with an optional caption. Alternatively, you can use input_message_content to send a message with the specified content instead of the video
	//		• InlineQueryResultVoice			- Represents a link to a voice recording in an .OGG container encoded with OPUS. By default, this voice recording will be sent by the user. Alternatively, you can use input_message_content to send a message with the specified content instead of the the voice message
	// 
	// 
	// 	Also you can specify input_message_content argument. It represents a message that will be sent as a result when the user chooses some of the inline query results. Telegram clients currently support the following 5 types:
	// 		• InputTextMessageContent		- Represents the content of a text message to be sent as the result of an inline query
	//		• InputLocationMessageContent	- Represents the content of a location message to be sent as the result of an inline query
	//		• InputVenueMessageContent		- Represents the content of a venue message to be sent as the result of an inline query	
	//		• InputContactMessageContent	- Represents the content of a contact message to be sent as the result of an inline query
	//		• InputInvoiceMessageContent	- Represents the content of an invoice message to be sent as the result of an inline query
	//
	// 	   
	//	You can collect "feedback" what inline results users are choosing. To know which of the provided results your users are sending to their chat partners, send @Botfather the /setinlinefeedback command. With this enabled, you will receive the results chosen by your users via Telegram::Bot::chosenInlineResult() signal.
	//	> NOTE: This can create load issues for popular bots – you may receive more results than actual requests due to caching(see the cache_time parameter in answerInlineQuery). For these cases, we recommend adjusting the probability setting to receive 1 / 10, 1 / 100 or 1 / 1000 of the results.
	//
	// 
	//	In this example we will simply answer to an incoming inline query with every of existing inline query result

	//	Telegram::Bot::inlineQueryReceived() emitted every time when new inline query is received. Let's connect it to the lambda where we proceed this inline query
	QObject::connect(&telegram_bot, &Telegram::Bot::inlineQueryReceived, [&](qint32 update_id, Telegram::InlineQuery inline_query) {
		
		// If the user typed "@bot_username Cached audio" we will reply with InlineQueryResultCachedAudio
		if (inline_query.query.toLower() == " ")
			telegram_bot.answerInlineQuery(inline_query.id, { std::make_shared<Telegram::InlineQueryResultCachedAudio>("cached_audio_test_id", "CQACAgIAAxkDAAIDoWGP-KnkOzAbLi5gkTWtX5N2kI5iAAI9FQACLNiASEtlh9RXqNf0IgQ").get() });

		// If the user typed "@bot_username Cached photo" we will reply with InlineQueryResultCachedPhoto
		if (inline_query.query.toLower() == "cached photo")
			telegram_bot.answerInlineQuery(inline_query.id, { std::make_shared<Telegram::InlineQueryResultCachedPhoto>("cached_photo_test_id",  "AgACAgIAAxkDAAIDsWGP-yniee-gNjSiQm9rGyFN2difAAJ7tzEb-ctJSH1nSWMEWCf9AQADAgADeAADIgQ").get() });

		// If the user typed "@bot_username Cached gif" we will reply with InlineQueryResultCachedGif
		if (inline_query.query.toLower() == "cached gif")
			telegram_bot.answerInlineQuery(inline_query.id, { std::make_shared<Telegram::InlineQueryResultCachedGif>("cached_gif_test_id", "CgACAgIAAxkDAAIDqWGP-SPZBB3jSoVtxNGC50vXZu2xAAJHFQACLNiASET0fbOGrYffIgQ").get() });
	});

	return coreApplication.exec();
}

