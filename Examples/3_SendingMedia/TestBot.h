#include "qobject.h"

#include "TelegramBotAPI.h"

using namespace Telegram;

class TestBot : public QObject {
	Q_OBJECT

public:
	TestBot(const std::shared_ptr<BotSettings>& bot_settings = BotSettings::makeFromFile());

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

	//	Contains an example of how to send animations
	void sendAnimation(const qint32& chat_id);

	//	Contains an example of how to send voice messages
	void sendVoice(const qint32& chat_id);

	//	Contains an example of how to send video notes
	void sendVideoNote(const qint32& chat_id);

	//	Contains example of how to send bunch of medias in one message
	void sendMediaGroup(const qint32& chat_id);

private slots:
	//	Emitted when an error with Telegram Bot API has occurred, prints error description in the console
	void onErrorOccured(Error error);

	//	Emitted when a network error has occurred, prints error code and description in the console
	void onNetworkErrorOccured(Error error);

private:
	Bot telegram_bot;

	//	List of bot commands 
	QVector<BotCommand> bot_commands = { {"send_message",		"Sends a text message!"},
										 {"send_photo",			"Sends a photo!"},
										 {"send_audio",			"Sends a audio!"},
										 {"send_document",		"Sends a document!"},
										 {"send_video",			"Sends a video!"},
										 {"send_animation",		"Sends a animation!"},
										 {"send_voice",			"Sends a voice message!"},
										 {"send_video_note",	"Sends a video note!"},
										 {"send_media_group",	"Sends couple of media combined in one message!"} };
};