#include "qobject.h"

//	Including library main header
#include "TelegramBotAPI.h"

class TestBot : public QObject
{
	Q_OBJECT

public:
	TestBot(const Telegram::BotSettings& bot_settings = Telegram::BotSettings());

	//	Contains an example of how to send messages
	void sendMessage(const qint32& chat_id);

	//	Contains an example of how to send photos
	void sendPhoto(const qint32& chat_id);

	//	Contains an example of how to send audios
	void sendAudio(const qint32& chat_id);

	//	Contains an example of how to send documents
	void sendDocument(const qint32& chat_id);
		
	//	Contains an example of how to send videos
	void sendVideo(const qint32& chat_id);

	//	Contains an example of how to send animation
	void sendAnimation(const qint32& chat_id);

	//	Contains an example of how to send voice message
	void sendVoice(const qint32& chat_id);

	//	Contains an example of how to send video note
	void sendVideoNote(const qint32& chat_id);

	//	Contains example of how to send bunch of medias in one message
	void sendMediaGroup(const qint32& chat_id);

private slots:
	//	Emitted when an error occurred
	void Error(Telegram::Error error);

private:
	Telegram::Bot telegram_bot;

	//	List of bot commands 
	QVector<Telegram::BotCommand> bot_commands = { Telegram::BotCommand("send_message", "Sends text message!"),
												   Telegram::BotCommand("send_photo", "Sends photo!"),
												   Telegram::BotCommand("send_audio", "Sends audio!"),
												   Telegram::BotCommand("send_document", "Sends document!"),
												   Telegram::BotCommand("send_video", "Sends video!"),
												   Telegram::BotCommand("send_animation", "Sends animation!"),
												   Telegram::BotCommand("send_voice", "Sends voice message!"),
												   Telegram::BotCommand("send_video_note", "Sends video note!"),
												   Telegram::BotCommand("send_media_group", "Sends couple of media combined in one message!") };
};