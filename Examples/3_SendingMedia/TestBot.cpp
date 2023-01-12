#include "TestBot.h"

using namespace Telegram;

TestBot::TestBot(const std::shared_ptr<BotSettings>& bot_settings) :
	telegram_bot(bot_settings),
    QObject()
{
	//	Telegram::Bot::errorOccured is emitted every time when the negative response is received from the Telegram server and holds an Error object in arguments. Error class contains the occurred error description and code. See Error.h for details
	connect(&telegram_bot, &Bot::errorOccured, this, &TestBot::onErrorOccured);

	//	Telegram::Bot::networkErrorOccured is emitted every time when there is an error while receiving Updates from the Telegram. Error class contains the occurred error description and code. See Error.h for details
	connect(&telegram_bot, &Bot::networkErrorOccured, this, &TestBot::onNetworkErrorOccured);

	//	Setting bot commands. If you will do this the Telegram will show hints when somebody typing commands to your bot
	telegram_bot.setMyCommands(bot_commands);

	//	Parsing incoming messages for commands
	QObject::connect(&telegram_bot, &Bot::messageReceived, [&](qint32 update_id, Message message) {
		if (message.text.has_value() == false) return;

		if		(message.text == "/send_message")		sendMessage(message.chat->id);
		else if (message.text == "/send_photo")			sendPhoto(message.chat->id);
		else if (message.text == "/send_audio")			sendAudio(message.chat->id);
		else if (message.text == "/send_document")		sendDocument(message.chat->id);
		else if (message.text == "/send_video")			sendVideo(message.chat->id);
		else if (message.text == "/send_animation")		sendAnimation(message.chat->id);
		else if (message.text == "/send_voice")			sendVoice(message.chat->id);
		else if (message.text == "/send_video_note")	sendVideoNote(message.chat->id);
		else if (message.text == "/send_media_group")	sendMediaGroup(message.chat->id); 
	});
}

//	In order to send any kind of media (message, photo, audio, etc.) you have to know the destination chat id, it can be either: 
//		● User numerical chat id. Can be obtained when the user sends a message to the bot(Ex. when starts the bot). We'll use it in this example
//		● Group/Channel username (in the format @channelusername). Can be obtained from the Telegram application. The second part of the invite link "t.me/channelusername"
// 
//	Sending files. There are three ways to send files (photos, stickers, audio, media, etc.):
//		1. Post the file using QFile. 10 MB max size for photos, 50 MB for other files
//		2. If the file is already stored somewhere on the Telegram servers, you don't need to reupload it: each file object has a file_id field, simply pass this file_id as a parameter instead of uploading. There are no limits for files sent this way
//		3. Provide Telegram with an HTTP URL for the file to be sent. Telegram will download and send the file. 5 MB max size for photos and 20 MB max for other types of content
//	
//	Also when you send any kind of media - you can use sendChatAction() to send an action that will be shown right next to your bot nickname. This action represents the work that your bot is currently doing (e.x TYPING, UPLOAD_PHOTO). See all chat action types in Telegram::Bot::ChatActionType 

void TestBot::sendMessage(const qint32& chat_id)
{
	//	Preparing text of the message
	QString message_text =
		"<pre>sendMessage(chat_id, text, parse_mode, entities, disable_web_page_preview, disable_notification, reply_to_message_id, allow_sending_without_reply, reply_markup)</pre>\n\n"
		"Use this method to send text messages. On success, the sent Message is returned\n\n"
		"<i>See detailed description with meanings of all parameters in Bot.h</i>";

	//	Show the bot is "typing..." in Telegram
	telegram_bot.sendChatAction(chat_id, Bot::ChatActionType::TYPING);

	//	Sending message. See Telegram::Bot::sendMessage() for detailed description of all arguments
	telegram_bot.sendMessage(chat_id, message_text, Message::FormattingType::HTML);
}

void TestBot::sendPhoto(const qint32& chat_id)
{
	if (auto photo_file = std::make_shared<QFile>("P:/GitHub_repositories/Modersi/TelegramBotAPI/TelegramBotAPI/Examples/SendingMedia/Resources/Photo.png");
		photo_file->open(QIODevice::ReadOnly)) 
	{
		//	Preparing caption of the photo
		QString photo_caption =
			"<pre>sendPhoto(chat_id, photo, caption, parse_mode, caption_entities, disable_notification, reply_to_message_id, allow_sending_without_reply, reply_markup)</pre>\n\n"
			"Use this method to send photos. On success, the sent Message is returned\n\n"
			"<i>See detailed description with meanings of all parameters in Bot.h</i>";

		//	Show the bot is "sending photo..." in Telegram
		telegram_bot.sendChatAction(chat_id, Bot::ChatActionType::UPLOAD_PHOTO);

		//	1. Sending the photo with QFile and storing the reply
		Message send_photo_reply = telegram_bot.sendPhoto(chat_id, photo_file.get(), photo_caption, Message::FormattingType::HTML);

		//	2. Sending the photo with file_id. Obtained from the response of previous sendPhoto()
		if (send_photo_reply.photo.has_value())
			telegram_bot.sendPhoto(chat_id, send_photo_reply.photo->at(2).file_id, photo_caption, Message::FormattingType::HTML);

		//	3. Sending the photo with URL from internet
		telegram_bot.sendPhoto(chat_id, "https://cdn-105.anonfiles.com/p1z8KbU1u1/42e23ea2-1636818981/Photo.png", photo_caption, Message::FormattingType::HTML);
	}
}

void TestBot::sendAudio(const qint32& chat_id)
{
	if (auto audio_file = std::make_shared<QFile>("P:/GitHub_repositories/Modersi/TelegramBotAPI/TelegramBotAPI/Examples/SendingMedia/Resources/Audio.mp3");
		audio_file->open(QIODevice::ReadOnly))
	{
		//	Preparing the caption of the audio
		QString audio_caption =
			"<pre>sendAudio(chat_id, audio, caption, parse_mode, caption_entities, duration, performer, title, thumb, disable_notification, reply_to_message_id, allow_sending_without_reply, reply_markup)</pre>\n\n"
			"Use this method to send audio files, if you want Telegram clients to display them in the music player. On success, the sent Message is returned\n\n"
			"Your audio must be in the .MP3 or .M4A format. Bots can currently send audio files of up to 50 MB in size, this limit may be changed in the future. For sending voice messages, use the sendVoice() instead\n\n"
			"<i>See detailed description with meanings of all parameters in Bot.h</i>";

		//	Show the bot is "sending document..." in Telegram
		telegram_bot.sendChatAction(chat_id, Bot::ChatActionType::UPLOAD_DOCUMENT);

		//	1. Sending the audio with QFile and storing the reply
		Message send_audio_reply = telegram_bot.sendAudio(chat_id, audio_file.get(), audio_caption, Message::FormattingType::HTML, std::nullopt, std::nullopt, "Audio.mp3", "Audio.mp3");

		//	2. Sending audio with file_id. Obtained from the response of previous sendAudio()
		if (send_audio_reply.audio.has_value())
			telegram_bot.sendAudio(chat_id, send_audio_reply.audio->file_id, audio_caption, Message::FormattingType::HTML);

		//	3. Sending the audio with URL from internet
		telegram_bot.sendAudio(chat_id, "https://cdn-127.anonfiles.com/Jd06r6U0ub/4b0ef29c-1636641104/Audio.mp3", audio_caption, Message::FormattingType::HTML);
	}
}

void TestBot::sendDocument(const qint32& chat_id)
{
	if (auto document_file = std::make_shared<QFile>("P:/GitHub_repositories/Modersi/TelegramBotAPI/TelegramBotAPI/Examples/SendingMedia/Resources/Document.zip");
		document_file->open(QIODevice::ReadOnly))
	{
		//	Preparing the caption of the document
		QString document_caption =
			"<pre>sendDocument(chat_id, document, thumb, caption, parse_mode, caption_entities, disable_content_type_detection, disable_notification, reply_to_message_id, allow_sending_without_reply, reply_markup)</pre>\n\n"
			"Use this method to send general files. On success, the sent Message is returned\n\n"
			"Bots can currently send files of any type of up to 50 MB in size, this limit may be changed in the future\n\n"
			"<i>See detailed description with meanings of all parameters in Bot.h</i>";

		//	Show the bot is "sending document..." in Telegram
		telegram_bot.sendChatAction(chat_id, Bot::ChatActionType::UPLOAD_DOCUMENT);

		//	1. Sending the document with QFile and storing the reply
		Message send_document_reply = telegram_bot.sendDocument(chat_id, document_file.get(), std::nullopt, document_caption, Message::FormattingType::HTML);

		//	2. Sending the document with file_id. Obtained from the response of previous sendDocument()
		if (send_document_reply.document.has_value())
			telegram_bot.sendDocument(chat_id, send_document_reply.document->file_id, std::nullopt, document_caption, Message::FormattingType::HTML);

		//	3. Sending the document with URL from internet
		telegram_bot.sendDocument(chat_id, "https://cdn-127.anonfiles.com/1516r4U2ue/e6c27ba5-1636641155/Document.zip", std::nullopt, document_caption, Message::FormattingType::HTML);
	}
}

void TestBot::sendVideo(const qint32& chat_id)
{
	if (auto video_file = std::make_shared<QFile>("P:/GitHub_repositories/Modersi/TelegramBotAPI/TelegramBotAPI/Examples/SendingMedia/Resources/Video.mp4");
		video_file->open(QIODevice::ReadOnly))
	{
		//	Preparing the caption of the video
		QString video_caption =
			"<pre>sendVideo(chat_id, video, duration, width, height, thumb, caption, parse_mode, caption_entities, supports_streaming, disable_notification, reply_to_message_id, allow_sending_without_reply, reply_markup)</pre>\n\n"
			"Use this method to send video files, Telegram clients support mp4 videos (other formats may be sent as Document). On success, the sent Message is returned\n\n"
			"Bots can currently send video files of up to 50 MB in size, this limit may be changed in the future.\n\n"
			"<i>See detailed description with meanings of all parameters in Bot.h</i>";

		//	Show the bot is "sending video..." in Telegram
		telegram_bot.sendChatAction(chat_id, Bot::ChatActionType::UPLOAD_VIDEO);

		//	1. Sending the video with QFile and storing the reply
		Message send_video_reply = telegram_bot.sendVideo(chat_id, video_file.get(), std::nullopt, std::nullopt, std::nullopt, std::nullopt, video_caption, Message::FormattingType::HTML);

		//	2. Sending the video with file_id. Obtained from the response of previous sendVideo()
		if (send_video_reply.video.has_value())
			telegram_bot.sendVideo(chat_id, send_video_reply.video->file_id, std::nullopt, std::nullopt, std::nullopt, std::nullopt, video_caption, Message::FormattingType::HTML);

		//	3. Sending the video with URL from internet
		telegram_bot.sendVideo(chat_id, "https://cdn-130.anonfiles.com/P7vcrfUbu1/ffda5578-1636642158/Video.mp4", std::nullopt, std::nullopt, std::nullopt, std::nullopt, video_caption, Message::FormattingType::HTML);
	}
}

void TestBot::sendAnimation(const qint32& chat_id)
{
	if (auto animation_file = std::make_shared<QFile>("P:/GitHub_repositories/Modersi/TelegramBotAPI/TelegramBotAPI/Examples/SendingMedia/Resources/Animation.gif");
		animation_file->open(QIODevice::ReadOnly))
	{
		//	Preparing the caption of the animation
		QString animation_caption =
			"<pre>sendAnimation(chat_id, animation, duration, width, height, thumb, caption, parse_mode, caption_entities, disable_notification, reply_to_message_id, allow_sending_without_reply, reply_markup)</pre>\n\n"
			"Use this method to send animation files (GIF or H.264/MPEG-4 AVC video without sound). On success, the sent Message is returned\n\n"
			"Bots can currently send animation files of up to 50 MB in size, this limit may be changed in the future\n\n"
			"<i>See detailed description with meanings of all parameters in Bot.h</i>";

		//	Show the bot is "sending document..." in Telegram
		telegram_bot.sendChatAction(chat_id, Bot::ChatActionType::UPLOAD_DOCUMENT);

		//	1. Sending the animation with QFile and storing the reply
		Message send_animation_reply = telegram_bot.sendAnimation(chat_id, animation_file.get(), std::nullopt, std::nullopt, std::nullopt, std::nullopt, animation_caption, Message::FormattingType::HTML);

		//	2. Sending the animation with file_id. Obtained from response of previous sendAnimation()
		if (send_animation_reply.animation.has_value())
			telegram_bot.sendAnimation(chat_id, send_animation_reply.animation->file_id, std::nullopt, std::nullopt, std::nullopt, std::nullopt, animation_caption, Message::FormattingType::HTML);

		//	3. Sending the animation with URL from internet
		telegram_bot.sendAnimation(chat_id, "https://cdn-107.anonfiles.com/j4a5sbUdu6/5ef7ec60-1636644323/Animation.gif", std::nullopt, std::nullopt, std::nullopt, std::nullopt, animation_caption, Message::FormattingType::HTML);
	}
}

void TestBot::sendVoice(const qint32& chat_id)
{
	if (auto voice_file = std::make_shared<QFile>("P:/GitHub_repositories/Modersi/TelegramBotAPI/TelegramBotAPI/Examples/SendingMedia/Resources/Voice.ogg");
		voice_file->open(QIODevice::ReadOnly))
	{
		//	Preparing the caption of the voice
		QString voice_caption =
			"<pre>sendVoice(chat_id, voice, caption, parse_mode, caption_entities, duration, disable_notification, reply_to_message_id, allow_sending_without_reply, reply_markup)</pre>\n\n"
			"Use this method to send audio files, if you want Telegram clients to display the file as a playable voice message. On success, the sent Message is returned\n\n"
			"For this to work, your audio must be in an .OGG file encoded with OPUS (other formats may be sent as Audio or Document). Bots can currently send voice messages of up to 50 MB in size, this limit may be changed in the future\n\n"
			"<i>See detailed description with meanings of all parameters in Bot.h</i>";

		//	Show the bot is "sending voice..." in Telegram
		telegram_bot.sendChatAction(chat_id, Bot::ChatActionType::UPLOAD_VOICE);

		//	1. Sending the voice with QFile and storing the reply
		Message send_voice_reply = telegram_bot.sendVoice(chat_id, voice_file.get(), voice_caption, Message::FormattingType::HTML);

		//	2. Sending the voice with file_id. Obtained from the response of previous sendVoice()
		if (send_voice_reply.voice.has_value())
			telegram_bot.sendVoice(chat_id, send_voice_reply.voice->file_id, voice_caption, Message::FormattingType::HTML);

		//	3. Sending the voice with URL from internet
		telegram_bot.sendVoice(chat_id, "https://cdn-128.anonfiles.com/ffhes4U5u1/248b7d3c-1636644695/Voice.ogg", voice_caption, Message::FormattingType::HTML);
	}
}

void TestBot::sendVideoNote(const qint32& chat_id)
{
	//	Attention! Telegram supports only square(1:1) videos up to 1 minute long for video notes
	if (auto video_note_file = std::make_shared<QFile>("P:/GitHub_repositories/Modersi/TelegramBotAPI/TelegramBotAPI/Examples/SendingMedia/Resources/VideoNote.mp4");
		video_note_file->open(QIODevice::ReadOnly))
	{
		//	Show the bot is "sending video note..." in Telegram
		telegram_bot.sendChatAction(chat_id, Bot::ChatActionType::UPLOAD_VIDEO_NOTE);

		//	1. Sending the video note with QFile and storing reply
		Message send_video_note_reply = telegram_bot.sendVideoNote(chat_id, video_note_file.get());

		//	2. Sending the video note with file_id. Obtained from the response of previous sendVideoNote()
		if (send_video_note_reply.video_note.has_value())
			telegram_bot.sendVideoNote(chat_id, send_video_note_reply.video_note->file_id);

		//	3. Sending the video note with URL from internet is not supported :(
	}
}

void TestBot::sendMediaGroup(const qint32& chat_id)
{
	//	Preparing the media to send
	auto photo_file = std::make_shared<QFile>("P:/GitHub_repositories/Modersi/TelegramBotAPI/TelegramBotAPI/Examples/SendingMedia/Resources/Photo.png");
	auto audio_file = std::make_shared<QFile>("P:/GitHub_repositories/Modersi/TelegramBotAPI/TelegramBotAPI/Examples/SendingMedia/Resources/Audio.mp3");
	auto video_file = std::make_shared<QFile>("P:/GitHub_repositories/Modersi/TelegramBotAPI/TelegramBotAPI/Examples/SendingMedia/Resources/Video.mp4");
	auto document_file = std::make_shared<QFile>("P:/GitHub_repositories/Modersi/TelegramBotAPI/TelegramBotAPI/Examples/SendingMedia/Resources/Photo.png");

	if (photo_file->open(QIODevice::ReadOnly) == false or audio_file->open(QIODevice::ReadOnly) == false or video_file->open(QIODevice::ReadOnly) == false or document_file->open(QIODevice::ReadOnly) == false)
		return;

	//	Since the documents and audios can be only grouped in an album with messages of the same type there is 3 overloads of sendMediaGroup():
	//		1. For documents. Takes QVector<InputMediaDocument> in arguments
	//		2. For audios. Takes QVector<InputMediaAudio> in arguments
	//		3. For photos and videos. Takes QPair of QVector<InputMediaPhoto> and QVector<InputMediaVideo> in arguments

	//	Show the bot is "sending document..." in Telegram
	telegram_bot.sendChatAction(chat_id, Bot::ChatActionType::UPLOAD_DOCUMENT);

	//	1. Sending a bunch of documents
	telegram_bot.sendMediaGroup(chat_id, QVector<InputMediaDocument>{ {document_file.get()}, {document_file.get()}, {document_file.get()} });

	//	2. Sending a bunch of audios
	telegram_bot.sendMediaGroup(chat_id, QVector<InputMediaAudio>{ {audio_file.get()}, { audio_file.get() }, { audio_file.get() } });

	//	3. Sending a bunch of photos and videos
	telegram_bot.sendMediaGroup(chat_id, { 
		{ InputMediaPhoto(photo_file.get()), InputMediaPhoto(photo_file.get()) },
		{ InputMediaVideo(video_file.get()), InputMediaVideo(video_file.get()) }
	});
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
