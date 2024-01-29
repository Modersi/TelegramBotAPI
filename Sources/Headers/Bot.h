#ifndef TELEGRAM_BOT_H
#define TELEGRAM_BOT_H

#include <variant>
#include <optional>
#include <future>

#include "qfile.h"
#include "qstring.h"
#include "qjsondocument.h"
#include "qjsonobject.h"
#include "qjsonarray.h"
#include "qvector.h"
#include "qobject.h"

#include "FunctionArguments.h"
#include "BotSettings.h"
#include "Internal/TelegramListener.h"
#include "Internal/Utility/Utility.h"
#include "Types/Error.h"
#include "Types/InlineKeyboardMarkup.h"
#include "Types/ReplyKeyboardMarkup.h"
#include "Types/ReplyKeyboardRemove.h"
#include "Types/ForceReply.h"
#include "Types/MessageId.h"
#include "Types/InputMedia.h"
#include "Types/InputMediaAudio.h"
#include "Types/InputMediaDocument.h"
#include "Types/InputMediaPhoto.h"
#include "Types/InputMediaVideo.h"
#include "Types/UserProfilePhotos.h"
#include "Types/File.h"
#include "Types/ChatPermissions.h"
#include "Types/BotCommand.h"
#include "Types/BotCommandScopeAllChatAdministrators.h"
#include "Types/BotCommandScopeAllGroupChats.h"
#include "Types/BotCommandScopeAllPrivateChats.h"
#include "Types/BotCommandScopeChat.h"
#include "Types/BotCommandScopeChatAdministrators.h"
#include "Types/BotCommandScopeChatMember.h"
#include "Types/BotCommandScopeDefault.h"
#include "Types/StickerSet.h"
#include "Types/InlineQuery.h"
#include "Types/ChosenInlineResult.h"
#include "Types/InlineQueryResult.h"
#include "Types/WebhookInfo.h"

namespace Telegram 
{
    /**
     *
     * @brief This class represents your bot in the Telegram
     *
     */

    class Bot : public QObject
    {
        Q_OBJECT

    public:
        /** @brief Creates a Telegram Bot using settings from bot_settings */
        Bot(const std::shared_ptr<BotSettings>& bot_settings = BotSettings::makeFromFile());

//**  Updates handling signals **//
    signals:
        /** @brief Emited when bot reseive new incoming message of any kind — text, photo, sticker, etc. */
        void messageReceived(qint32 update_id, Message message);

        /** @brief Emited when bot reseive version of a message that is known to the bot and was edited */
        void messageWasUpdated(qint32 update_id, Message message);

        /** @brief Emited when bot reseive new incoming channel post of any kind — text, photo, sticker, etc. */
        void channelPostReceived(qint32 update_id, Message message);

        /** @brief Emited when bot reseive new version of a channel post that is known to the bot and was edited */
        void channelPostWasUpdated(qint32 update_id, Message message);

        /** @brief Emited when bot reseive new incoming inline query */
        void inlineQueryReceived(qint32 update_id, InlineQuery inline_query);

        /** @brief Emited when bot reseive the result of an inline query that was chosen by a user and sent to their chat partner */
        void chosenInlineResult(qint32 update_id, ChosenInlineResult chosen_inline_result);

        /** @brief Emited when bot reseive new incoming callback query */
        void callbackQueryReceived(qint32 update_id, CallbackQuery callback_query);

        /** @brief Emited when bot reseive new poll state. Bots receive only updates about stopped polls and polls, which are sent by the bot  */
        void pollReceived(qint32 update_id, Poll poll);

        /** @brief Emited when a user changed their answer in a non-anonymous poll. Bots receive new votes only in polls that were sent by the bot itself */
        void pollAnswerReceived(qint32 update_id, PollAnswer poll_answer);

        /** @brief Emited when the bot's chat member status was updated in a chat. For private chats, this update is received only when the bot is blocked or unblocked by the user */
        void myChatMemberStatusUpdated(qint32 update_id, ChatMemberUpdated chat_member_update);

        /** @brief Emited when chat member's status was updated in a chat. The bot must be an administrator in the chat and must explicitly specify “chat_member” in the list of allowed_updates of SetWebhook() method to receive these updates */
        void chatMemberStatusUpdated(qint32 update_id, ChatMemberUpdated chat_member_update);

        /** @brief Emited when an error occured */
        void errorOccured(Error error);

        /** @brief Emited when a network error occured */
        void networkErrorOccured(Error error);

    public:
//**  Getting updates **//

        /** @brief Use this method to receive incoming updates using long polling. In case of success a vector of Update objects is returned
         *
         * > Note: This method will not work if an outgoing webhook is set up
         * > Note: In order to avoid getting duplicate updates, recalculate offset after each server response
         *
         * @param offset            qint32	            Optional. Identifier of the first update to be returned. Must be greater by one than the highest among the identifiers of previously received updates. By default, updates starting with the earliest unconfirmed update are returned. An update is considered confirmed as soon as getUpdates is called with an offset higher than its update_id. The negative offset can be specified to retrieve updates starting from -offset update from the end of the updates queue. All previous updates will forgotten
         * @param limit             qint32	            Optional. Limits the number of updates to be retrieved. Values between 1-100 are accepted. Defaults to 100
         * @param timeout           qint32	            Optional. Timeout in seconds for long polling. Defaults to 0, i.e. usual short polling. Should be positive, short polling should be used for testing purposes only
         * @param allowed_updates   QVector of QString  Optional. A list of the update types you want your bot to receive. For example, specify [“message”, “edited_channel_post”, “callback_query”] to only receive updates of these types. See Update for a complete list of available update types. Specify an empty list to receive all update types except chat_member (default). If not specified, the previous setting will be used */
        std::future<QVector<Telegram::Update>> getUpdates(const std::optional<qint32>& offset = std::nullopt, const std::optional<qint32>& limit = std::nullopt, const std::optional<qint32>& timeout = std::nullopt, const std::optional<QVector<QString>>& allowed_updates = std::nullopt);

        /** @brief Use this method to specify a url and receive incoming updates via an outgoing webhook. Returns True on success
         * 
         *  Whenever there is an update for the bot, Telegram will send an HTTPS POST request to the specified url, containing a JSON-serialized Update. You can obtain this updates using Telegram::Bot class signals. In case of an unsuccessful request, we will give up after a reasonable amount of attempts 
         * 
         * @param url	                 QString 	            HTTPS url to send updates to. Use an empty string to remove webhook integration
         * @param certificate	         QFile*	                Optional. Upload your public key certificate so that the root certificate in use can be checked. Has to be opened
         * @param ip_address	         QString	            Optional. The fixed IP address which will be used to send webhook requests instead of the IP address resolved through DNS
         * @param max_connections	     qint32	                Optional. Maximum allowed number of simultaneous HTTPS connections to the webhook for update delivery, 1-100. Defaults to 40. Use lower values to limit the load on your bot's server, and higher values to increase your bot's throughput
         * @param allowed_updates	     QVector of QString	    Optional. A list of the update types you want your bot to receive. For example, specify [“message”, “edited_channel_post”, “callback_query”] to only receive updates of these types. See Telegram::Update fields for a complete list of available update types. Specify an empty list to receive all update types except chat_member (default). If not specified, the previous setting will be used
         * @param drop_pending_updates   bool	                Optional. Pass True to drop all pending updates */
        std::future<bool> setWebhook(const QString& url, QFile* certificate = nullptr, const std::optional<QString>& ip_address = std::nullopt, const std::optional<qint32>& max_connections = std::nullopt, const std::optional<QVector<QString>>& allowed_updates = std::nullopt, const std::optional<bool>& drop_pending_updates = std::nullopt);

        /** @brief Use this method to remove webhook integration if you decide to switch back to getUpdates. Returns True on success
         *
         * @param drop_pending_updates  bool    Optional. Pass True to drop all pending updates */
        std::future<bool> deleteWebhook(const std::optional<bool>& drop_pending_updates = std::nullopt);

        /** @brief Use this method to get current webhook status. Requires no parameters. On success, returns a WebhookInfo object. If the bot is using getUpdates, will return an object with the url field empty */
        std::future<WebhookInfo> getWebhookInfo();

//**  Main methods  **//

        /** @brief A simple method for testing your bot's auth token. Requires no parameters. Returns basic information about the bot in form of a User object */
        std::future<User> getMe();

        /** @brief Use this method to log out from the cloud Bot API server before launching the bot locally. Returns True on success
         * 
         * You must log out the bot before running it locally, otherwise there is no guarantee that the bot will receive updates. After a successful call, you can immediately log in on a local server,
         * but will not be able to log in back to the cloud Bot API server for 10 minutes */
        std::future<bool> logOut();

        /** @brief Use this method to close the bot instance before moving it from one local server to another. Returns True on success
         *
         * You need to delete the webhook before calling this method to ensure that the bot isn't launched again after server restart. The method will return error 429 in the first 10 minutes after the bot is launched */
        std::future<bool> close();

        /** @brief Use this methods to send text messages. On success, the sent Message is returned
		 *
		 * @param chat_id	                    qint64 or QString	                                                                Unique identifier for the target chat or username of the target channel(in the format @channelusername)
		 * @param text	                        QString	                                                                            Text of the message to be sent, 1 - 4096 characters after entities parsing
		 * @param parse_mode	                QString	                                                                            Optional. Mode for parsing entities in the message text. See formatting options for more details
		 * @param entities	                    QVector of MessageEntity	                                                        Optional. List of special entities that appear in message text, which can be specified instead of parse_mode
		 * @param disable_web_page_preview	    bool             	                                                        	    Optional. Disables link previews for links in this message
		 * @param disable_notification	        bool	                                                                            Optional. Sends the message silently. Users will receive a notification with no sound
		 * @param reply_to_message_id	        qint32	                                                                            Optional. If the message is a reply, ID of the original message
		 * @param allow_sending_without_reply   bool	                                                                            Optional. Pass True, if the message should be sent even if the specified replied-to message is not found
		 * @param reply_markup                  InlineKeyboardMarkup or ReplyKeyboardMarkup or ReplyKeyboardRemove or ForceReply    Optional. Additional interface options. An object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user */
        std::future<Message> sendMessage(const std::variant<qint64, QString>& chat_id, const QString& text, const std::optional<Message::FormattingType>& parse_mode = std::nullopt, const std::optional<QVector<MessageEntity>>& entities = std::nullopt, const std::optional<bool>& disable_web_page_preview = std::nullopt, const std::optional<bool>& disable_notification = std::nullopt, const std::optional<qint32>& reply_to_message_id = std::nullopt, const std::optional<bool>& allow_sending_without_reply = std::nullopt, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup = std::nullopt);
        std::future<Message> sendMessage(const FunctionArguments::SendMessage& arguments);

        /** @brief Use this method to forward messages of any kind. Service messages can't be forwarded. On success, the sent Message is returned
         * 
         * @param chat_id	            qint64 or QString	    Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param from_chat_id	        qint64 or QString	    Unique identifier for the chat where the original message was sent (or channel username in the format @channelusername)
         * @param message_id            qint32                  Message identifier in the chat specified in from_chat_id
         * @param disable_notification  bool                    Optional. Sends the message silently. Users will receive a notification with no sound */
        std::future<Message> forwardMessage(const std::variant<qint64, QString>& chat_id, const std::variant<qint64, QString>& from_chat_id, const qint32& message_id, const std::optional<bool>& disable_notification = std::nullopt);
        std::future<Message> forwardMessage(const FunctionArguments::ForwardMessage& arguments);


        /** @brief Use this method to copy messages of any kind. Service messages and invoice messages can't be copied. Returns the MessageId of the sent message on success
         *      
         * This method is analogous to the method forwardMessage, but the copied message doesn't have a link to the original message
         * 
         * @param chat_id	                    qint64 or QString	                                                                Unique identifier for the target chat or username of the target channel(in the format @channelusername)
         * @param from_chat_id	                qint64 or QString	                                                                Unique identifier for the chat where the original message was sent(or channel username in the format @channelusername)
         * @param message_id	                qint32	                                                                            Message identifier in the chat specified in from_chat_id
         * @param caption	                    QString	                                                                            Optional. New caption for media, 0 - 1024 characters after entities parsing.If not specified, the original caption is kept
         * @param parse_mode	                QString	                                                                            Optional. Mode for parsing entities in the new caption.See formatting options for more details
         * @param caption_entities	            QVector of MessageEntity	                                                        Optional. List of special entities that appear in the new caption, which can be specified instead of parse_mode
         * @param disable_notification	        bool	                                                                            Optional. Sends the message silently.Users will receive a notification with no sound
         * @param reply_to_message_id	        qint32	                                                                            Optional. If the message is a reply, ID of the original message
         * @param allow_sending_without_reply   bool	                                                                            Optional. Pass True, if the message should be sent even if the specified replied - to message is not found
         * @param reply_markup                  InlineKeyboardMarkup or ReplyKeyboardMarkup or ReplyKeyboardRemove or ForceReply	Optional. Additional interface options. An object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user */
        std::future<MessageId> copyMessage(const std::variant<qint64, QString>& chat_id, const std::variant<qint64, QString>& from_chat_id, const qint32& message_id, const std::optional<QString>& caption = std::nullopt, const std::optional<Message::FormattingType>& parse_mode = std::nullopt, const std::optional<QVector<MessageEntity>>& caption_entities = std::nullopt, const std::optional<bool>& disable_notification = std::nullopt, const std::optional<qint32>& reply_to_message_id = std::nullopt, const std::optional<bool>& allow_sending_without_reply = std::nullopt, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup = std::nullopt);
        std::future<MessageId> copyMessage(const FunctionArguments::CopyMessage& arguments);

        /** @brief Use this method to send photos. On success, the sent Message is returned
         *
         * @param chat_id	                    qint64 or QString	                                                                Unique identifier for the target chat or username of the target channel(in the format @channelusername)
         * @param photo	                        QFile* or QString	                                                                Photo to send. Pass a file_id as QString to send a photo that exists on the Telegram servers(recommended), pass an HTTP URL as a QString for Telegram to get a photo from the Internet, or upload a new photo using QFile(should be opened). The photo must be at most 10 MB in size.The photo's width and height must not exceed 10000 in total. Width and height ratio must be at most 20
         * @param caption	                    QString	                                                                            Optional. Photo caption(may also be used when resending photos by file_id), 0-1024 characters after entities parsing
         * @param parse_mode	                QString	                                                                            Optional. Mode for parsing entities in the photo caption. See formatting options for more details.
         * @param caption_entities	            QVector of MessageEntity	                                                        Optional. List of special entities that appear in the caption, which can be specified instead of parse_mode
         * @param disable_notification	        bool	                                                                            Optional. Sends the message silently. Users will receive a notification with no sound.
         * @param reply_to_message_id	        qint32	                                                                            Optional. If the message is a reply, ID of the original message
         * @param allow_sending_without_reply   bool	                                                                            Optional. Pass True, if the message should be sent even if the specified replied-to message is not found
         * @param reply_markup                  InlineKeyboardMarkup or ReplyKeyboardMarkup or ReplyKeyboardRemove or ForceReply	Optional. Additional interface options. An object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user.*/
        std::future<Message> sendPhoto(const std::variant<qint64, QString>& chat_id, const std::variant<QFile*, QString>& photo, const std::optional<QString>& caption = std::nullopt, const std::optional<Message::FormattingType>& parse_mode = std::nullopt, const std::optional<QVector<MessageEntity>>& caption_entities = std::nullopt, const std::optional<bool>& disable_notification = std::nullopt, const std::optional<qint32>& reply_to_message_id = std::nullopt, const std::optional<bool>& allow_sending_without_reply = std::nullopt, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup = std::nullopt);
        std::future<Message> sendPhoto(const FunctionArguments::SendPhoto& arguments);

        /** @brief Use this method to send audio files, if you want Telegram clients to display them in the music player. On success, the sent Message is returned
         * 
         * Your audio must be in the .MP3 or .M4A format. Bots can currently send audio files of up to 50 MB in size, this limit may be changed in the future. For sending voice messages, use the sendVoice method instead
         *
         * @param chat_id	                    qint64 or QString	                                                                Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param audio	                        QFile* or QString	                                                                Audio file to send. Pass a file_id as QString to send an audio file that exists on the Telegram servers (recommended), pass an HTTP URL as a QString for Telegram to get an audio file from the Internet, or upload a new photo using QFile(should be opened)
         * @param caption	                    QString	                                                                            Optional. Audio caption, 0-1024 characters after entities parsing
         * @param parse_mode	                QString	                                                                            Optional. Mode for parsing entities in the audio caption. See formatting options for more details.
         * @param caption_entities	            QVector of MessageEntity	                                                        Optional. List of special entities that appear in the caption, which can be specified instead of parse_mode
         * @param duration	                    qint32	                                                                            Optional. Duration of the audio in seconds
         * @param performer	                    QString	                                                                            Optional. Performer
         * @param title	                        QString	                                                                            Optional. Track name
         * @param thumb	                        QFile* or QString	                                                                Optional. Thumbnail of the file sent; can be ignored if thumbnail generation for the file is supported server-side. The thumbnail should be in JPEG format and less than 200 kB in size. A thumbnail's width and height should not exceed 320. Ignored if the file is not uploaded using QFile*. Thumbnails can't be reused and can be only uploaded as a new file, so you can pass QFile*(should be opened) to upload new one
         * @param disable_notification	        bool	                                                                            Optional. Sends the message silently. Users will receive a notification with no sound.
         * @param reply_to_message_id	        qint32	                                                                            Optional. If the message is a reply, ID of the original message
         * @param allow_sending_without_reply   bool	                                                                            Optional. Pass True, if the message should be sent even if the specified replied-to message is not found
         * @param reply_markup                  InlineKeyboardMarkup or ReplyKeyboardMarkup or ReplyKeyboardRemove or ForceReply	Optional. Additional interface options. An object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user */
        std::future<Message> sendAudio(const std::variant<qint64, QString>& chat_id, const std::variant<QFile*, QString>& audio, const std::optional<QString>& caption = std::nullopt, const std::optional<Message::FormattingType>& parse_mode = std::nullopt, const std::optional<QVector<MessageEntity>>& caption_entities = std::nullopt, const std::optional<qint32>& duration = std::nullopt, const std::optional<QString>& performer = std::nullopt, const std::optional<QString>& title = std::nullopt, const std::optional<std::variant<QFile*, QString>>& thumb = std::nullopt, const std::optional<bool>& disable_notification = std::nullopt, const std::optional<qint32>& reply_to_message_id = std::nullopt, const std::optional<bool>& allow_sending_without_reply = std::nullopt, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup = std::nullopt);
        std::future<Message> sendAudio(const FunctionArguments::SendAudio& arguments);

        /** @brief Use this method to send general files. On success, the sent Message is returned
         * 
         * Bots can currently send files of any type of up to 50 MB in size, this limit may be changed in the future
         *
         * @param chat_id	                        qint64 or QString	                                                                Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param document	                        QFile* or QString	                                                                File to send. Pass a file_id as QString to send a file that exists on the Telegram servers (recommended), pass an HTTP URL as a QString for Telegram to get a file from the Internet, or upload a new photo using QFile(should be opened)
         * @param thumb	                            QFile* or QString	                                                                Optional. Thumbnail of the file sent; can be ignored if thumbnail generation for the file is supported server-side. The thumbnail should be in JPEG format and less than 200 kB in size. A thumbnail's width and height should not exceed 320. Ignored if the file is not uploaded using QFile*. Thumbnails can't be reused and can be only uploaded as a new file, so you can pass QFile*(should be opened) to upload new one
         * @param caption	                        QString	                                                                            Optional. Document caption (may also be used when resending documents by file_id), 0-1024 characters after entities parsing
         * @param parse_mode	                    QString	                                                                            Optional. Mode for parsing entities in the document caption. See formatting options for more details.
         * @param caption_entities	                QVector of MessageEntity	                                                        Optional. List of special entities that appear in the caption, which can be specified instead of parse_mode
         * @param disable_content_type_detection    bool	                                                                            Optional. Disables automatic server-side content type detection for files uploaded using multipart/form-data
         * @param disable_notification	            bool	                                                                            Optional. Sends the message silently. Users will receive a notification with no sound.
         * @param reply_to_message_id	            qint32	                                                                            Optional. If the message is a reply, ID of the original message
         * @param allow_sending_without_reply	    bool	                                                                            Optional. Pass True, if the message should be sent even if the specified replied-to message is not found
         * @param reply_markup                      InlineKeyboardMarkup or ReplyKeyboardMarkup or ReplyKeyboardRemove or ForceReply	Optional. Additional interface options. An object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user. */
        std::future<Message> sendDocument(const std::variant<qint64, QString>& chat_id, const std::variant<QFile*, QString>& document, const std::optional<std::variant<QFile*, QString>>& thumb = std::nullopt, const std::optional<QString>& caption = std::nullopt, const std::optional<Message::FormattingType>& parse_mode = std::nullopt, const std::optional<QVector<MessageEntity>>& caption_entities = std::nullopt, const std::optional<bool>& disable_content_type_detection = std::nullopt, const std::optional<bool>& disable_notification = std::nullopt, const std::optional<qint32>& reply_to_message_id = std::nullopt, const std::optional<bool>& allow_sending_without_reply = std::nullopt, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup = std::nullopt);
        std::future<Message> sendDocument(const FunctionArguments::SendDocument& arguments);

        /** @brief Use this method to send video files, Telegram clients support mp4 videos (other formats may be sent as Document). On success, the sent Message is returned
         *
         *  Bots can currently send video files of up to 50 MB in size, this limit may be changed in the future
         * 
         * @param chat_id	                    qint64 or QString	                                                                Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param video	                        QFile* or QString	                                                                Video to send. Pass a file_id as String to send a video that exists on the Telegram servers (recommended), pass an HTTP URL as a String for Telegram to get a video from the Internet, or upload a new photo using QFile(should be opened)
         * @param duration	                    qint32	                                                                            Optional. Duration of sent video in seconds
         * @param width	                        qint32	                                                                            Optional. Video width
         * @param height	                    qint32	                                                                            Optional. Video height
         * @param thumb	                        QFile* or QString	                                                                Optional. Thumbnail of the file sent; can be ignored if thumbnail generation for the file is supported server-side. The thumbnail should be in JPEG format and less than 200 kB in size. A thumbnail's width and height should not exceed 320. Ignored if the file is not uploaded using QFile*. Thumbnails can't be reused and can be only uploaded as a new file, so you can pass QFile*(should be opened) to upload new one
         * @param caption	                    QString	                                                                            Optional. Video caption (may also be used when resending videos by file_id), 0-1024 characters after entities parsing
         * @param parse_mode	                QString	                                                                            Optional. Mode for parsing entities in the video caption. See formatting options for more details.
         * @param caption_entities	            QVector of MessageEntity	                                                        Optional. List of special entities that appear in the caption, which can be specified instead of parse_mode
         * @param supports_streaming	        bool	                                                                            Optional. Pass True, if the uploaded video is suitable for streaming
         * @param disable_notification	        bool	                                                                            Optional. Sends the message silently. Users will receive a notification with no sound.
         * @param reply_to_message_id	        qint32	                                                                            Optional. If the message is a reply, ID of the original message
         * @param allow_sending_without_reply   bool	                                                                            Optional. Pass True, if the message should be sent even if the specified replied-to message is not found
         * @param reply_markup                  InlineKeyboardMarkup or ReplyKeyboardMarkup or ReplyKeyboardRemove or ForceReply	Optional. Additional interface options. An object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user. */
        std::future<Message> sendVideo(const std::variant<qint64, QString>& chat_id, const std::variant<QFile*, QString>& video, const std::optional<qint32>& duration = std::nullopt, const std::optional<qint32>& width = std::nullopt, const std::optional<qint32>& height = std::nullopt, const std::optional<std::variant<QFile*, QString>>& thumb = std::nullopt, const std::optional<QString>& caption = std::nullopt, const std::optional<Message::FormattingType>& parse_mode = std::nullopt, const std::optional<QVector<MessageEntity>>& caption_entities = std::nullopt, const std::optional<bool>& supports_streaming = std::nullopt, const std::optional<bool>& disable_notification = std::nullopt, const std::optional<qint32>& reply_to_message_id = std::nullopt, const std::optional<bool>& allow_sending_without_reply = std::nullopt, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup = std::nullopt);
        std::future<Message> sendVideo(const FunctionArguments::SendVideo& arguments);

        /** @brief Use this method to send animation files (GIF or H.264/MPEG-4 AVC video without sound). On success, the sent Message is returned
         *
         * Bots can currently send animation files of up to 50 MB in size, this limit may be changed in the future
         * 
         * @param chat_id	                    qint64 or QString	                                                                Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param animation	                    QFile* or QString	                                                                Animation to send. Pass a file_id as String to send an animation that exists on the Telegram servers (recommended), pass an HTTP URL as a String for Telegram to get an animation from the Internet, or upload a new photo using QFile(should be opened)
         * @param duration	                    qint32	                                                                            Optional. Duration of sent animation in seconds
         * @param width	                        qint32	                                                                            Optional. Animation width
         * @param height	                    qint32	                                                                            Optional. Animation height
         * @param thumb	                        QFile* or QString	                                                                Optional. Thumbnail of the file sent; can be ignored if thumbnail generation for the file is supported server-side. The thumbnail should be in JPEG format and less than 200 kB in size. A thumbnail's width and height should not exceed 320. Ignored if the file is not uploaded using QFile*. Thumbnails can't be reused and can be only uploaded as a new file, so you can pass QFile*(should be opened) to upload new one
         * @param caption	                    QString	                                                                            Optional. Animation caption (may also be used when resending animation by file_id), 0-1024 characters after entities parsing
         * @param parse_mode	                QString	                                                                            Optional. Mode for parsing entities in the animation caption. See formatting options for more details
         * @param caption_entities	            QVector of MessageEntity	                                                        Optional. List of special entities that appear in the caption, which can be specified instead of parse_mode
         * @param disable_notification	        bool	                                                                            Optional. Sends the message silently. Users will receive a notification with no sound.
         * @param reply_to_message_id	        qint32	                                                                            Optional. If the message is a reply, ID of the original message
         * @param allow_sending_without_reply   bool	                                                                            Optional. Pass True, if the message should be sent even if the specified replied-to message is not found
         * @param reply_markup                  InlineKeyboardMarkup or ReplyKeyboardMarkup or ReplyKeyboardRemove or ForceReply	Optional. Additional interface options. An object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user */
        std::future<Message> sendAnimation(const std::variant<qint64, QString>& chat_id, const std::variant<QFile*, QString>& animation, const std::optional<qint32>& duration = std::nullopt, const std::optional<qint32>& width = std::nullopt, const std::optional<qint32>& height = std::nullopt, const std::optional<std::variant<QFile*, QString>>& thumb = std::nullopt, const std::optional<QString>& caption = std::nullopt, const std::optional<Message::FormattingType>& parse_mode = std::nullopt, const std::optional<QVector<MessageEntity>>& caption_entities = std::nullopt, const std::optional<bool>& disable_notification = std::nullopt, const std::optional<qint32>& reply_to_message_id = std::nullopt, const std::optional<bool>& allow_sending_without_reply = std::nullopt, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup = std::nullopt);
        std::future<Message> sendAnimation(const FunctionArguments::SendAnimation& arguments);

        /** @brief Use this method to send audio files, if you want Telegram clients to display the file as a playable voice message. On success, the sent Message is returned
         *
         * For this to work, your audio must be in an .OGG file encoded with OPUS (other formats may be sent as Audio or Document). Bots can currently send voice messages of up to 50 MB in size, this limit may be changed in the future
         * 
         * @param chat_id	                    qint64 or QString	                                                                Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param voice	                        QFile* or QString	                                                                Audio file to send. Pass a file_id as String to send a file that exists on the Telegram servers (recommended), pass an HTTP URL as a String for Telegram to get a file from the Internet, or upload a new photo using QFile(should be opened)
         * @param caption	                    QString	                                                                            Optional. Voice message caption, 0-1024 characters after entities parsing
         * @param parse_mode	                QString	                                                                            Optional. Mode for parsing entities in the voice message caption. See formatting options for more details.
         * @param caption_entities	            QVector of MessageEntity	                                                        Optional. List of special entities that appear in the caption, which can be specified instead of parse_mode
         * @param duration	                    qint32	                                                                            Optional. Duration of the voice message in seconds
         * @param disable_notification	        bool	                                                                            Optional. Sends the message silently. Users will receive a notification with no sound.
         * @param reply_to_message_id	        qint32	                                                                            Optional. If the message is a reply, ID of the original message
         * @param allow_sending_without_reply   bool	                                                                            Optional. Pass True, if the message should be sent even if the specified replied-to message is not found
         * @param reply_markup                  InlineKeyboardMarkup or ReplyKeyboardMarkup or ReplyKeyboardRemove or ForceReply	Optional. Additional interface options. An object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user */
        std::future<Message> sendVoice(const std::variant<qint64, QString>& chat_id, const std::variant<QFile*, QString>& voice, const std::optional<QString>& caption = std::nullopt, const std::optional<Message::FormattingType>& parse_mode = std::nullopt, const std::optional<QVector<MessageEntity>>& caption_entities = std::nullopt, const std::optional<qint32>& duration = std::nullopt, const std::optional<bool>& disable_notification = std::nullopt, const std::optional<qint32>& reply_to_message_id = std::nullopt, const std::optional<bool>& allow_sending_without_reply = std::nullopt, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup = std::nullopt);
        std::future<Message> sendVoice(const FunctionArguments::SendVoice& arguments);

        /** @brief Use this method to send video messages. As of v.4.0, Telegram clients support rounded square mp4 videos of up to 1 minute long. On success, the sent Message is returned.
         *
         * @param chat_id	                    qint64 or QString	                                                                Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param video_note	                QFile* or QString	                                                                Video note to send. Pass a file_id as String to send a video note that exists on the Telegram servers (recommended) or upload a new photo using QFile*(should be opened). Sending video notes by a URL is currently unsupported
         * @param duration	                    qint32	                                                                            Optional. Duration of sent video in seconds
         * @param length	                    qint32	                                                                            Optional. Video width and height, i.e. diameter of the video message
         * @param thumb	                        QFile* or QString	                                                                Optional. Thumbnail of the file sent; can be ignored if thumbnail generation for the file is supported server-side. The thumbnail should be in JPEG format and less than 200 kB in size. A thumbnail's width and height should not exceed 320. Ignored if the file is not uploaded using QFile*. Thumbnails can't be reused and can be only uploaded as a new file, so you can pass QFile*(should be opened) to upload new one
         * @param disable_notification	        bool	                                                                            Optional. Sends the message silently. Users will receive a notification with no sound
         * @param reply_to_message_id	        qint32	                                                                            Optional. If the message is a reply, ID of the original message
         * @param allow_sending_without_reply   bool	                                                                            Optional. Pass True, if the message should be sent even if the specified replied-to message is not found
         * @param reply_markup                  InlineKeyboardMarkup or ReplyKeyboardMarkup or ReplyKeyboardRemove or ForceReply	Optional. Additional interface options. An object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user */
        std::future<Message> sendVideoNote(const std::variant<qint64, QString>& chat_id, const std::variant<QFile*, QString>& video_note, const std::optional<qint32>& duration = std::nullopt, const std::optional<qint32>& length = std::nullopt, const std::optional<std::variant<QFile*, QString>>& thumb = std::nullopt, const std::optional<bool>& disable_notification = std::nullopt, const std::optional<qint32>& reply_to_message_id = std::nullopt, const std::optional<bool>& allow_sending_without_reply = std::nullopt, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup = std::nullopt);
        std::future<Message> sendVideoNote(const FunctionArguments::SendVideoNote& arguments);

        /** @brief Use this method to send a group of audios as an album. On success, an array of Messages that were sent is returned.
         *
         * @param chat_id	                    qint64 or QString	        Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param media	                        QVector of InputMediaAudio  Vector of InputMediaAudio describing bunch of audios to be sent, must include 2-10 items
         * @param disable_notification	        bool	                    Optional. Sends messages silently. Users will receive a notification with no sound.
         * @param reply_to_message_id	        qint32	                    Optional. If the messages are a reply, ID of the original message
         * @param allow_sending_without_reply   bool	                    Optional. Pass True, if the message should be sent even if the specified replied-to message is not found */
        std::future<QVector<Message>> sendMediaGroup(const std::variant<qint64, QString>& chat_id, const QVector<InputMediaAudio>& media, const std::optional<bool>& disable_notification = std::nullopt, const std::optional<qint32>& reply_to_message_id = std::nullopt, const std::optional<bool>& allow_sending_without_reply = std::nullopt);
        std::future<QVector<Message>> sendMediaGroup(const FunctionArguments::SendMediaGroup_Audio& arguments);

        /** @brief Use this method to send a group of documents as an album. On success, an array of Messages that were sent is returned.
         *
         * @param chat_id	                    qint64 or QString	            Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param media	                        QVector of InputMediaDocument   Vector of InputMediaDocument describing bunch of documents to be sent, must include 2-10 items
         * @param disable_notification	        bool	                        Optional. Sends messages silently. Users will receive a notification with no sound.
         * @param reply_to_message_id	        qint32	                        Optional. If the messages are a reply, ID of the original message
         * @param allow_sending_without_reply   bool	                        Optional. Pass True, if the message should be sent even if the specified replied-to message is not found */
        std::future<QVector<Message>> sendMediaGroup(const std::variant<qint64, QString>& chat_id, const QVector<InputMediaDocument>& media, const std::optional<bool>& disable_notification = std::nullopt, const std::optional<qint32>& reply_to_message_id = std::nullopt, const std::optional<bool>& allow_sending_without_reply = std::nullopt);
        std::future<QVector<Message>> sendMediaGroup(const FunctionArguments::SendMediaGroup_Document& arguments);

        /** @brief Use this method to send a group of photos and videos as an album. On success, an array of Messages that were sent is returned
         *
         * @param chat_id	                  qint64 or QString	            Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param photos	                  QVector of InputMediaPhoto    Vectors of InputMediaPhoto describing bunch of photos to be sent, must include 2-10 items. Can be empty if videos is present
         * @param videos	                  QVector of InputMediaVideo    Vector of InputMediaVideo describing bunch of videos to be sent, must include 2-10 items. Can be empty if photos is present
         * @param disable_notification	      bool	                        Optional. Sends messages silently. Users will receive a notification with no sound.
         * @param reply_to_message_id	      qint32	                    Optional. If the messages are a reply, ID of the original message
         * @param allow_sending_without_reply bool	                        Optional. Pass True, if the message should be sent even if the specified replied-to message is not found */
        std::future<QVector<Message>> sendMediaGroup(const std::variant<qint64, QString>& chat_id, const QVector<InputMediaPhoto>& photos, const QVector<InputMediaVideo>& videos, const std::optional<bool>& disable_notification = std::nullopt, const std::optional<qint32>& reply_to_message_id = std::nullopt, const std::optional<bool>& allow_sending_without_reply = std::nullopt);
        std::future<QVector<Message>> sendMediaGroup(const FunctionArguments::SendMediaGroup_PhotoVideo& arguments);

        /** @brief Use this method to send point on the map. On success, the sent Message is returned
         *
         * @param chat_id	                    qint64 or QString	                                                                Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param latitude	                    float	                                                                            Latitude of the location
         * @param longitude	                    float	                                                                            Longitude of the location
         * @param horizontal_accuracy	        float	                                                                            Optional. The radius of uncertainty for the location, measured in meters; 0-1500
         * @param live_period	                qint32	                                                                            Optional. Period in seconds for which the location will be updated (see Live Locations, should be between 60 and 86400
         * @param heading	                    qint32	                                                                            Optional. For live locations, a direction in which the user is moving, in degrees. Must be between 1 and 360 if specified
         * @param proximity_alert_radius	    qint32	                                                                            Optional. For live locations, a maximum distance for proximity alerts about approaching another chat member, in meters. Must be between 1 and 100000 if specified
         * @param disable_notification	        bool	                                                                            Optional. Sends the message silently. Users will receive a notification with no sound
         * @param reply_to_message_id	        qint32	                                                                            Optional. If the message is a reply, ID of the original message
         * @param allow_sending_without_reply   bool	                                                                            Optional. Pass True, if the message should be sent even if the specified replied-to message is not found
         * @param reply_markup                  InlineKeyboardMarkup or ReplyKeyboardMarkup or ReplyKeyboardRemove or ForceReply	Optional. Additional interface options. An object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user */
        std::future<Message> sendLocation(const std::variant<qint64, QString>& chat_id, const float& latitude, const float& longitude, const std::optional<float>& horizontal_accuracy = std::nullopt, const std::optional<qint32>& live_period = std::nullopt, const std::optional<qint32>& heading = std::nullopt, const std::optional<qint32>& proximity_alert_radius = std::nullopt, const std::optional<bool>& disable_notification = std::nullopt, const std::optional<qint32>& reply_to_message_id = std::nullopt, const std::optional<bool>& allow_sending_without_reply = std::nullopt, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup = std::nullopt);
        std::future<Message> sendLocation(const FunctionArguments::SendLocation& arguments);

        /** @brief Use this method to edit live location messages. On success, if the edited message is not an inline message, the edited Message is returned, otherwise empty Message is returned
         *
         * A location can be edited until its live_period expires or editing is explicitly disabled by a call to stopMessageLiveLocation
         * 
         * @param latitude	                float	                Latitude of new location
         * @param longitude	                float	                Longitude of new location
         * @param chat_id	                qint64 or QString       Optional. Required if inline_message_id is not specified. Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param message_id	            qint32	                Optional. Required if inline_message_id is not specified. Identifier of the message to edit
         * @param inline_message_id	        QString	                Optional. Required if chat_id and message_id are not specified. Identifier of the inline message
         * @param horizontal_accuracy	    float	                Optional. The radius of uncertainty for the location, measured in meters; 0-1500
         * @param heading		            qint32	                Optional. Direction in which the user is moving, in degrees. Must be between 1 and 360 if specified
         * @param proximity_alert_radius    qint32	                Optional. Maximum distance for proximity alerts about approaching another chat member, in meters. Must be between 1 and 100000 if specified
         * @param reply_markup              InlineKeyboardMarkup	Optional. An inline keyboard */
        std::future<Message> editMessageLiveLocation(const float& latitude, const float& longitude, const std::optional<std::variant<qint64, QString>>& chat_id = std::nullopt, const std::optional<qint32>& message_id = std::nullopt, const std::optional<QString>& inline_message_id = std::nullopt, const std::optional<float>& horizontal_accuracy = std::nullopt, const std::optional<qint32>& heading = std::nullopt, const std::optional<qint32>& proximity_alert_radius = std::nullopt, const std::optional<InlineKeyboardMarkup>& reply_markup = std::nullopt);
        std::future<Message> editMessageLiveLocation(const FunctionArguments::EditMessageLiveLocation& arguments);

        /** @brief Use this method to stop updating a live location message before live_period expires. On success, if the message is not an inline message, the edited Message is returned, otherwise empty Message is returned.
         *
         * @param chat_id	          qint64 or QString	    Optional. Required if inline_message_id is not specified. Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param message_id	      qint32	            Optional. Required if inline_message_id is not specified. Identifier of the message with live location to stop
         * @param inline_message_id   QString	            Optional. Required if chat_id and message_id are not specified. Identifier of the inline message
         * @param reply_markup        InlineKeyboardMarkup	Optional. An object for a new inline keyboard */
        std::future<Message> stopMessageLiveLocation(const std::optional<std::variant<qint64, QString>>& chat_id = std::nullopt, const std::optional<qint32>& message_id = std::nullopt, const std::optional<QString>& inline_message_id = std::nullopt, const std::optional<InlineKeyboardMarkup>& reply_markup = std::nullopt);
        std::future<Message> stopMessageLiveLocation(const FunctionArguments::StopMessageLiveLocation& arguments);

        /** @brief Use this method to send information about a venue. On success, the sent Message is returned.
         *
         * @param chat_id	                    qint64 or QString	                                                                Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param latitude	                    float	                                                                            Latitude of the venue
         * @param longitude	                    float	                                                                            Longitude of the venue
         * @param title	                        QString	                                                                            Name of the venue
         * @param address	                    QString	                                                                            Address of the venue
         * @param foursquare_id	                QString	                                                                            Optional. Foursquare identifier of the venue
         * @param foursquare_type	            QString	                                                                            Optional. Foursquare type of the venue, if known. (For example, “arts_entertainment/default”, “arts_entertainment/aquarium” or “food/icecream”.)
         * @param google_place_id	            QString	                                                                            Optional. Google Places identifier of the venue
         * @param google_place_type	            QString	                                                                            Optional. Google Places type of the venue. (See supported types.)
         * @param disable_notification	        bool	                                                                            Optional. Sends the message silently. Users will receive a notification with no sound
         * @param reply_to_message_id	        qint32	                                                                            Optional. If the message is a reply, ID of the original message
         * @param allow_sending_without_reply   bool	                                                                            Optional. Pass True, if the message should be sent even if the specified replied-to message is not found
         * @param reply_markup                  InlineKeyboardMarkup or ReplyKeyboardMarkup or ReplyKeyboardRemove or ForceReply	Optional. Additional interface options. An object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user */
        std::future<Message> sendVenue(const std::variant<qint64, QString>& chat_id, const float& latitude, const float& longitude, const QString& title, const QString& address, const std::optional<QString>& foursquare_id = std::nullopt, const std::optional<QString>& foursquare_type = std::nullopt, const std::optional<QString>& google_place_id = std::nullopt, const std::optional<QString>& google_place_type = std::nullopt, const std::optional<bool>& disable_notification = std::nullopt, const std::optional<qint32>& reply_to_message_id = std::nullopt, const std::optional<bool>& allow_sending_without_reply = std::nullopt, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup = std::nullopt);
        std::future<Message> sendVenue(const FunctionArguments::SendVenue& arguments);

        /** @brief Use this method to send phone contacts. On success, the sent Message is returned.
         *
         * @param chat_id	                    qint64 or QString	                                                                Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param phone_number	                QString	                                                                            Contact's phone number
         * @param first_name	                QString	                                                                            Contact's first name
         * @param last_name	                    QString	                                                                            Optional. Contact's last name
         * @param vcard	                        QString	                                                                            Optional. Additional data about the contact in the form of a vCard, 0-2048 bytes
         * @param disable_notification	        bool	                                                                            Optional. Sends the message silently. Users will receive a notification with no sound
         * @param reply_to_message_id	        qint32	                                                                            Optional. If the message is a reply, ID of the original message
         * @param allow_sending_without_reply   bool	                                                                            Optional. Pass True, if the message should be sent even if the specified replied-to message is not found
         * @param reply_markup                  InlineKeyboardMarkup or ReplyKeyboardMarkup or ReplyKeyboardRemove or ForceReply	Optional. Additional interface options. An object for an inline keyboard, custom reply keyboard, instructions to remove keyboard or to force a reply from the user */
        std::future<Message> sendContact(const std::variant<qint64, QString>& chat_id, const QString& phone_number, const QString& first_name, const std::optional<QString>& last_name = std::nullopt, const std::optional<QString>& vcard = std::nullopt, const std::optional<bool>& disable_notification = std::nullopt, const std::optional<qint32>& reply_to_message_id = std::nullopt, const std::optional<bool>& allow_sending_without_reply = std::nullopt, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup = std::nullopt);
        std::future<Message> sendContact(const FunctionArguments::SendContact& arguments);

        /** @brief Use this method to send a native poll. On success, the sent Message is returned.
         *
         * @param chat_id	                    qint64 or QString	                                                                Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param question	                    QString	                                                                            Poll question, 1-300 characters
         * @param options	                    QVector of QString	                                                                A list of answer options, 2-10 strings 1-100 characters each
         * @param is_anonymous	                bool	                                                                            Optional. True, if the poll needs to be anonymous, defaults to True
         * @param type	                        QString	                                                                            Optional. Poll type, “quiz” or “regular”, defaults to “regular”
         * @param allows_multiple_answers	    bool	                                                                            Optional. True, if the poll allows multiple answers, ignored for polls in quiz mode, defaults to False
         * @param correct_option_id	            qint32	                                                                            Optional. 0-based identifier of the correct answer option, required for polls in quiz mode
         * @param explanation	                QString	                                                                            Optional. Text that is shown when a user chooses an incorrect answer or taps on the lamp icon in a quiz-style poll, 0-200 characters with at most 2 line feeds after entities parsing
         * @param explanation_parse_mode	    QString	                                                                            Optional. Mode for parsing entities in the explanation. See formatting options for more details
         * @param explanation_entities	        QVector of MessageEntity	                                                        Optional. List of special entities that appear in the poll explanation, which can be specified instead of parse_mode
         * @param open_period	                qint32	                                                                            Optional. Amount of time in seconds the poll will be active after creation, 5-600. Can't be used together with close_date
         * @param close_date	                qint32	                                                                            Optional. Point in time (Unix timestamp) when the poll will be automatically closed. Must be at least 5 and no more than 600 seconds in the future. Can't be used together with open_period
         * @param is_closed	                    bool	                                                                            Optional. Pass True, if the poll needs to be immediately closed. This can be useful for poll preview.
         * @param disable_notification	        bool	                                                                            Optional. Sends the message silently. Users will receive a notification with no sound.
         * @param reply_to_message_id	        qint32	                                                                            Optional. If the message is a reply, ID of the original message
         * @param allow_sending_without_reply   Boolean	                                                                            Optional. Pass True, if the message should be sent even if the specified replied-to message is not found
         * @param reply_markup                  InlineKeyboardMarkup or ReplyKeyboardMarkup or ReplyKeyboardRemove or ForceReply	Optional. Additional interface options. An object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user */
        std::future<Message> sendPoll(const std::variant<qint64, QString>& chat_id, const QString& question, const QVector<QString>& options, const std::optional<bool>& is_anonymous = std::nullopt, const std::optional<QString>& type = std::nullopt, const std::optional<bool>& allows_multiple_answers = std::nullopt, const std::optional<qint32>& correct_option_id = std::nullopt, const std::optional<QString>& explanation = std::nullopt, const std::optional<Message::FormattingType>& explanation_parse_mode = std::nullopt, const std::optional<QVector<MessageEntity>>& explanation_entities = std::nullopt, const std::optional<qint32>& open_period = std::nullopt, const std::optional<qint32>& close_date = std::nullopt, const std::optional<bool>& is_closed = std::nullopt, const std::optional<bool>& disable_notification = std::nullopt, const std::optional<qint32>& reply_to_message_id = std::nullopt, const std::optional<bool>& allow_sending_without_reply = std::nullopt, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup = std::nullopt);
        std::future<Message> sendPoll(const FunctionArguments::SendPoll& arguments);

        /** @brief Use this method to send an animated emoji that will display a random value. On success, the sent Message is returned
         * 
         * @param chat_id	                    qint64 or QString	                                                                Unique identifier for the target chat or username of the target channel (in the format @channelusername) 
         * @param emoji	                        QString	                                                                            Optional. Emoji on which the dice throw animation is based. Currently, must be one of “🎲”, “🎯”, “🏀”, “⚽”, “🎳”, or “🎰”. Dice can have values 1-6 for “🎲”, “🎯” and “🎳”, values 1-5 for “🏀” and “⚽”, and values 1-64 for “🎰”. Defaults to “🎲”
         * @param disable_notification	        bool	                                                                            Optional. Sends the message silently. Users will receive a notification with no sound
         * @param reply_to_message_id	        qint32	                                                                            Optional. If the message is a reply, ID of the original message
         * @param allow_sending_without_reply   bool	                                                                            Optional. Pass True, if the message should be sent even if the specified replied-to message is not found
         * @param reply_markup                  InlineKeyboardMarkup or ReplyKeyboardMarkup or ReplyKeyboardRemove or ForceReply	Optional. Additional interface options. A JSON-serialized object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user */
        std::future<Message> sendDice(const std::variant<qint64, QString>& chat_id, const std::optional<QString>& emoji = std::nullopt, const std::optional<bool>& disable_notification = std::nullopt, const std::optional<qint32>& reply_to_message_id = std::nullopt, const std::optional<bool>& allow_sending_without_reply = std::nullopt, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup = std::nullopt);
        std::future<Message> sendDice(const FunctionArguments::SendDice& arguments);

        /** @brief Enum that represents all available types of chat action that is written near bot's nickname */
        enum class ChatActionType
        {
            TYPING,             // ex. For text messages[sendMessage()]
            UPLOAD_PHOTO,       // ex. For photos[sendPhoto()]
            RECORD_VIDEO,       // ex. For videos
            UPLOAD_VIDEO,       // ex. For videos[sendVideo()]
            RECORD_VOICE,       // ex. For voice notes
            UPLOAD_VOICE,       // ex. For voice notes[sendVoice()]
            UPLOAD_DOCUMENT,    // ex. For general files[sendDocument()]
            FIND_LOCATION,      // ex. For location data[sendLocation()]
            RECORD_VIDEO_NOTE,  // ex. For video note
            UPLOAD_VIDEO_NOTE   // ex. For video note[sendVideoNote()]
        };
        Q_ENUM(ChatActionType)
        
        /** @brief Use this method when you need to tell the user that something is happening on the bot's side. The status is set for 5 seconds or less (when a message arrives from your bot, Telegram clients clear its typing status). Returns True on success.
         *
         * > Example: The ImageBot needs some time to process a request and upload the image. Instead of sending a text message along the lines of “Retrieving image, please wait…”, the bot may use
         * > sendChatAction with action = upload_photo. The user will see a “sending photo” status for the bot.
         * 
         *  We only recommend using this method when a response from the bot will take a noticeable amount of time to arrive.
         * 
         * @param chat_id   qint64 or QString   Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param action    ChatActionType	    Type of action to broadcast */
        std::future<bool> sendChatAction(const std::variant<qint64, QString>& chat_id, ChatActionType action);

        /** @brief Use this method to get a list of profile pictures for a user. Returns an empty UserProfilePhotos object if error eccured.
         *
         * @param user_id   qint64    Unique identifier of the target user
         * @param offset	qint32    Optional. Sequential number of the first photo to be returned. By default, all photos are returned.
         * @param limit     qint32    Optional. Limits the number of photos to be retrieved. Values between 1-100 are accepted. Defaults to 100 */
        std::future<UserProfilePhotos> getUserProfilePhotos(const qint64& user_id, const std::optional<qint32>& offset = std::nullopt, const std::optional<qint32>& limit = std::nullopt);

        /** @brief Use this method to get basic info about a file and prepare it for downloading. Returns an empty File object if error eccured.
         *
         * For the moment, bots can download files of up to 20MB in size. The file can then be downloaded via the link https://api.telegram.org/file/bot<token>/<file_path>, where <file_path> is taken
         * from the response. It is guaranteed that the link will be valid for at least 1 hour. When the link expires, a new one can be requested by calling getFile() again.
         * 
         * > Note: This function may not preserve the original file name and MIME type. You should save the file's MIME type and name (if available) when the File object is received.
         * 
         * @param file_id   QString   File identifier to get info about
         */
        std::future<File> getFile(const QString& file_id);

        /** @brief Use this method to ban a user in a group, a supergroup or a channel. In the case of supergroups and channels, the user will not be able to return to the chat on their own using invite links, etc., unless unbanned first.
         *         The bot must be an administrator in the chat for this to work and must have the appropriate admin rights. Returns True on success.
         *
         * @param chat_id	        qint64 or QString	    Unique identifier for the target group or username of the target supergroup or channel (in the format @channelusername)
         * @param user_id	        qint64	                Unique identifier of the target user
         * @param until_date	    qint32	                Optional. Date when the user will be unbanned, unix time. If user is banned for more than 366 days or less than 30 seconds from the current time they are considered to be banned forever. Applied for supergroups and channels only
         * @param revoke_messages   bool	                Optional. Pass True to delete all messages from the chat for the user that is being removed. If False, the user will be able to see messages in the group that were sent before the user was removed. Always True for supergroups and channels */
        std::future<bool> banChatMember(const std::variant<qint64, QString>& chat_id, const qint64& user_id, const std::optional<qint32>& until_date = std::nullopt, const std::optional<bool>& revoke_messages = std::nullopt);

        /** @brief Use this method to unban a previously banned user in a supergroup or channel. Returns True on success.
         *
         *  The user will not return to the group or channel automatically, but will be able to join via link, etc. The bot must be an administrator for this to work. By default, this method
         *  guarantees that after the call the user is not a member of the chat, but will be able to join it. So if the user is a member of the chat they will also be removed from the chat. If you don't want
         *  this, use the parameter only_if_banned
         * 
         * @param chat_id	        qint64 or QString	Unique identifier for the target group or username of the target supergroup or channel (in the format @username)
         * @param user_id	        qint64	            Unique identifier of the target user
         * @param only_if_banned    bool	            Optional. Do nothing if the user is not banned */
        std::future<bool> unbanChatMember(const std::variant<qint64, QString>& chat_id, const qint64& user_id, const std::optional<bool>& only_if_banned = std::nullopt);

        /** @brief Use this method to restrict a user in a supergroup. The bot must be an administrator in the supergroup for this to work and must have the appropriate admin rights.
         *         Pass True for all permissions to lift restrictions from a user. Returns True on success.
         *
         * @param chat_id	    qint64 or QString	    Unique identifier for the target chat or username of the target supergroup (in the format @supergroupusername)
         * @param user_id	    qint64	                Unique identifier of the target user
         * @param permissions   ChatPermissions	        An object for new user permissions
         * @param until_date    qint32	                Optional. Date when restrictions will be lifted for the user, unix time. If user is restricted for more than 366 days or less than 30 seconds from the current time, they are considered to be restricted forever */
        std::future<bool> restrictChatMember(const std::variant<qint64, QString>& chat_id, const qint64& user_id, const ChatPermissions& permissions, const std::optional<qint32>& until_date = std::nullopt);
        
        /* @brief Use this method to promote or demote a user in a supergroup or a channel. The bot must be an administrator in the chat for this to work and must have the appropriate admin rights. 
         *        Pass False for all boolean parameters to demote a user. Returns True on success.
         *
         * @param chat_id	                qint64 or QString	Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param user_id	                qint64	            Unique identifier of the target user
         * @param is_anonymous	            bool	            Optional. Pass True, if the administrator's presence in the chat is hidden
         * @param can_manage_chat	        bool	            Optional. Pass True, if the administrator can access the chat event log, chat statistics, message statistics in channels, see channel members, see anonymous administrators in supergroups and ignore slow mode. Implied by any other administrator privilege
         * @param can_post_messages	        bool	            Optional. Pass True, if the administrator can create channel posts, channels only
         * @param can_edit_messages	        bool	            Optional. Pass True, if the administrator can edit messages of other users and can pin messages, channels only
         * @param can_delete_messages	    bool	            Optional. Pass True, if the administrator can delete messages of other users
         * @param can_manage_voice_chats    bool	            Optional. Pass True, if the administrator can manage voice chats
         * @param can_restrict_members	    bool	            Optional. Pass True, if the administrator can restrict, ban or unban chat members
         * @param can_promote_members	    bool	            Optional. Pass True, if the administrator can add new administrators with a subset of their own privileges or demote administrators that he has promoted, directly or indirectly (promoted by administrators that were appointed by him)
         * @param can_change_info	        bool	            Optional. Pass True, if the administrator can change chat title, photo and other settings
         * @param can_invite_users	        bool	            Optional. Pass True, if the administrator can invite new users to the chat
         * @param can_pin_messages          bool	            Optional. Pass True, if the administrator can pin messages, supergroups only */
        std::future<bool> promoteChatMember(const std::variant<qint64, QString>& chat_id, const qint64& user_id, const std::optional<bool>& is_anonymous = std::nullopt, const std::optional<bool>& can_manage_chat = std::nullopt, const std::optional<bool>& can_post_messages = std::nullopt, const std::optional<bool>& can_edit_messages = std::nullopt, const std::optional<bool>& can_delete_messages = std::nullopt, const std::optional<bool>& can_manage_voice_chats = std::nullopt, const std::optional<bool>& can_restrict_members = std::nullopt, const std::optional<bool>& can_promote_members = std::nullopt, const std::optional<bool>& can_change_info = std::nullopt, const std::optional<bool>& can_invite_users = std::nullopt, const std::optional<bool>& can_pin_messages = std::nullopt);
        std::future<bool> promoteChatMember(const FunctionArguments::PromoteChatMember& arguments);
        
        /* @brief Use this method to set a custom title for an administrator in a supergroup promoted by the bot. Returns True on success.
         *
         * @param chat_id	     qint64 or QString      Unique identifier for the target chat or username of the target supergroup (in the format @supergroupusername)
         * @param user_id	     qint64	                Unique identifier of the target user
         * @param custom_title   QString	            New custom title for the administrator; 0-16 characters, emoji are not allowed */
        std::future<bool> setChatAdministratorCustomTitle(const std::variant<qint64, QString>& chat_id, const qint64& user_id, const QString& custom_title);
        
        /* @brief Use this method to set default chat permissions for all members. The bot must be an administrator in the group or a supergroup for this to work and must have the can_restrict_members admin rights. Returns True on success.
         *
         * @param chat_id       qint64 or QString   Unique identifier for the target chat or username of the target supergroup (in the format @supergroupusername)
         * @param permissions   ChatPermission      New default chat permissions */
        std::future<bool> setChatPermissions(const std::variant<qint64, QString>& chat_id, const ChatPermissions& permissions);
        
        /** @brief Use this method to generate a new primary invite link for a chat; any previously generated primary link is revoked. Returns the new invite link as String on success.
         * 
         * The bot must be an administrator in the chat for this to work and must have the appropriate admin rights.
         * 
         * > Note: Each administrator in a chat generates their own invite links. Bots can't use invite links generated by other administrators. If you want your bot to work with invite links, it will need to generate
         * > its own link using exportChatInviteLink or by calling the getChat method. If your bot needs to generate a new primary invite link replacing its previous one, use exportChatInviteLink again. 
         * 
         * @param chat_id   qint64 or String     Unique identifier for the target chat or username of the target channel (in the format @channelusername) */
        std::future<QString> exportChatInviteLink(const std::variant<qint64, QString>& chat_id);

        /* @brief Use this method to create an additional invite link for a chat. Returns the new invite link as ChatInviteLink object, in case of error returns empty ChatInviteLink object
         *
         * The bot must be an administrator in the chat for this to work and must have the appropriate admin rights. The link can be revoked using the method revokeChatInviteLink.
         * 
         * @param  chat_id	            qint64 or QString	Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param  name	                QString	            Optional. Invite link name; 0-32 characters
         * @param  expire_date	        qint32	            Optional. Point in time (Unix timestamp) when the link will expire
         * @param  member_limit	        qint32	            Optional. Maximum number of users that can be members of the chat simultaneously after joining the chat via this invite link; 1-99999 
         * @param  creates_join_request	bool	            Optional. True, if users joining the chat via the link need to be approved by chat administrators. If True, member_limit can't be specified */
        std::future<ChatInviteLink> createChatInviteLink(const std::variant<qint64, QString>& chat_id, const std::optional<QString>& name = std::nullopt, const std::optional<qint32>& expire_date = std::nullopt, const std::optional<qint32>& member_limit = std::nullopt, const std::optional<bool>& creates_join_request = std::nullopt);
        std::future<ChatInviteLink> createChatInviteLink(const FunctionArguments::CreateChatInviteLink& arguments);

        /* @brief Use this method to edit a non-primary invite link created by the bot. Returns the edited invite link as a ChatInviteLink object, in case of error returns empty ChatInviteLink object
         *
         * @param chat_id	            qint64 or QString	Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param invite_link	        QString	            The invite link to edit
         * @param name	                QString	            Optional. Invite link name; 0-32 characters
         * @param expire_date	        qint32	            Optional. Point in time (Unix timestamp) when the link will expire
         * @param member_limit	        qint32	            Optional. Maximum number of users that can be members of the chat simultaneously after joining the chat via this invite link; 1-99999
         * @param creates_join_request	bool	            Optional. True, if users joining the chat via the link need to be approved by chat administrators. If True, member_limit can't be specified */
        std::future<ChatInviteLink> editChatInviteLink(const std::variant<qint64, QString>& chat_id, const QString& invite_link, const std::optional<QString>& name = std::nullopt, const std::optional<qint32>& expire_date = std::nullopt, const std::optional<qint32>& member_limit = std::nullopt, const std::optional<bool>& creates_join_request = std::nullopt);
        std::future<ChatInviteLink> editChatInviteLink(const FunctionArguments::EditChatInviteLink& arguments);

        /* @brief Use this method to revoke an invite link created by the bot. If the primary link is revoked, a new link is automatically generated. Returns the revoked invite link as ChatInviteLink object, in case of error returns an empty ChatInviteLink object
         *
         * The bot must be an administrator in the chat for this to work and must have the appropriate admin rights
         * 
         * @param chat_id	    qint64 or QString       Unique identifier of the target chat or username of the target channel (in the format @channelusername)
         * @param invite_link   QString	                The invite link to revoke */
        std::future<ChatInviteLink> revokeChatInviteLink(const std::variant<qint64, QString>& chat_id, const QString& invite_link);

        /* @brief Use this method to approve a chat join request. Returns True on success
         *
         * The bot must be an administrator in the chat for this to work and must have the can_invite_users administrator right
         *
         * @param chat_id	    qint64 or QString       Unique identifier of the target chat or username of the target channel (in the format @channelusername)
         * @param invite_link   QString	                The invite link to revoke */
        std::future<bool> approveChatJoinRequest(const std::variant<qint64, QString>& chat_id, const qint32& user_id);

        /* @brief Use this method to decline a chat join request. Returns True on success
         *
         * The bot must be an administrator in the chat for this to work and must have the can_invite_users administrator right
         *
         * @param chat_id	    qint64 or QString       Unique identifier of the target chat or username of the target channel (in the format @channelusername)
         * @param invite_link   QString	                The invite link to revoke */
        std::future<bool> declineChatJoinRequest(const std::variant<qint64, QString>& chat_id, const qint32& user_id);
        
        /* @brief Use this method to set a new profile photo for the chat. Returns True on success
         *
         * Photos can't be changed for private chats. The bot must be an administrator in the chat for this to work and must have the appropriate admin rights.
         * 
         * @param chat_id   qint64 or QString	    Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param photo     QFile*	                New chat photo, uploaded using QFile*(should be opened) */
        std::future<bool> setChatPhoto(const std::variant<qint64, QString>& chat_id, QFile* photo);

        /* @brief Use this method to delete a chat photo. Returns True on success
         *
         * Photos can't be changed for private chats. The bot must be an administrator in the chat for this to work and must have the appropriate admin rights
         *
         * @param chat_id   qint64 or QString	    Unique identifier for the target chat or username of the target channel (in the format @channelusername) */
        std::future<bool> deleteChatPhoto(const std::variant<qint64, QString>& chat_id);

        /* @brief Use this method to change the title of a chat. Returns True on success.
         *
         * Titles can't be changed for private chats. The bot must be an administrator in the chat for this to work and must have the appropriate admin rights
         *
         * @param chat_id   qint64 or QString	    Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param title     QString	                New chat title, 1-255 characters */
        std::future<bool> setChatTitle(const std::variant<qint64, QString>& chat_id, const QString& title);

        /* @brief Use this method to change the description of a group, a supergroup or a channel. Returns True on success
         *
         * The bot must be an administrator in the chat for this to work and must have the appropriate admin rights
         *
         * @param chat_id       qint64 or QString	    Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param description   QString	                Optional. New chat description, 0-255 characters */
        std::future<bool> setChatDescription(const std::variant<qint64, QString>& chat_id, const std::optional<QString>& description = std::nullopt);

        /* @brief Use this method to add a message to the list of pinned messages in a chat. Returns True on success
         *
         * If the chat is not a private chat, the bot must be an administrator in the chat for this to work and must have the 'can_pin_messages' admin right in a supergroup or 'can_edit_messages' admin right in a channel
         *
         * @param chat_id               qint64 or QString	    Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param message_id            qint32	                Identifier of a message to pin
         * @param disable_notification  bool                    Optional. Pass True, if it is not necessary to send a notification to all chat members about the new pinned message. Notifications are always disabled in channels and private chats */
        std::future<bool> pinChatMessage(const std::variant<qint64, QString>& chat_id, const qint32& message_id, const std::optional<bool>& disable_notification = std::nullopt);

        /* @brief Use this method to remove a message from the list of pinned messages in a chat. Returns True on success
         *
         * If the chat is not a private chat, the bot must be an administrator in the chat for this to work and must have the 'can_pin_messages' admin right in a supergroup or 'can_edit_messages' admin right in a channel
         *
         * @param chat_id       qint64 or QString	    Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param message_id    qint32	                Identifier of a message to unpin. If not specified, the most recent pinned message (by sending date) will be unpinned */
        std::future<bool> unpinChatMessage(const std::variant<qint64, QString>& chat_id, const std::optional<qint32>& message_id = std::nullopt);

        /* @brief Use this method to clear the list of pinned messages in a chat. Returns True on success
         *
         * If the chat is not a private chat, the bot must be an administrator in the chat for this to work and must have the 'can_pin_messages' admin right in a supergroup or 'can_edit_messages' admin right in a channel
         *
         * @param chat_id   qint64 or QString	    Unique identifier for the target chat or username of the target channel (in the format @channelusername) */
        std::future<bool> unpinAllChatMessages(const std::variant<qint64, QString>& chat_id);

        /* @brief Use this method for your bot to leave a group, supergroup or channel. Returns True on success
         *
         * @param chat_id   qint64 or QString	    Unique identifier for the target chat or username of the target channel (in the format @channelusername) */
        std::future<bool> leaveChat(const std::variant<qint64, QString>& chat_id);

        /* @brief Use this method to get up to date information about the chat (current name of the user for one-on-one conversations, current username of a user, group or channel, etc.). Returns a Chat object on success, in case of error returns an empty Chat object
         *
         * @param chat_id   qint64 or QString	    Unique identifier for the target chat or username of the target channel (in the format @channelusername) */
        std::future<Chat> getChat(const std::variant<qint64, QString>& chat_id);

        /* @brief Use this method to get a list of administrators in a chat. On success, returns a vector of pointers to ChatMember objects(can be converted to derived classes with dynamic_cast()) that contains information about all chat administrators except other bots. Returns nullptr in case of error
         *        
         * If the chat is a group or a supergroup and no administrators were appointed, only the creator will be returned
         *
         * @param chat_id   qint64 or QString	    Unique identifier for the target chat or username of the target channel (in the format @channelusername) */
        std::future<QVector<std::shared_ptr<ChatMember>>> getChatAdministrators(const std::variant<qint64, QString>& chat_id);

        /* @brief Use this method to get the number of members in a chat. Returns -1 in case of error.
         *
         * @param chat_id   qint64 or QString	    Unique identifier for the target chat or username of the target channel (in the format @channelusername) */
        std::future<qint32> getChatMemberCount(const std::variant<qint64, QString>& chat_id);

        /* @brief Use this method to get information about a member of a chat. Returns a pointer ChatMember(can be converted to derived classes with dynamic_cast()) object on success, in case of error returns nullptr
         *
         * @param chat_id   qint64 or QString	    Unique identifier for the target chat or username of the target channel (in the format @channelusername) 
         * @param user_id   qint64                  Unique identifier of the target user */
        std::future<std::shared_ptr<ChatMember>> getChatMember(const std::variant<qint64, QString>& chat_id, const qint64& user_id);

        /* @brief Use this method to set a new group sticker set for a supergroup. Returns True on success
         *
         * The bot must be an administrator in the chat for this to work and must have the appropriate admin rights. Use the field can_set_sticker_set optionally returned in getChat() requests to check if the bot can use this method
         * 
         * @param chat_id               qint64 or QString	    Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param sticker_set_name      QString                 Name of the sticker set to be set as the group sticker set */
        std::future<bool> setChatStickerSet(const std::variant<qint64, QString>& chat_id, const QString& sticker_set_name);
        
        /* @brief Use this method to delete a group sticker set from a supergroup. Returns True on success
         *
         * The bot must be an administrator in the chat for this to work and must have the appropriate admin rights. Use the field can_set_sticker_set optionally returned in getChat() requests to check if the bot can use this method
         *
         * @param chat_id   qint64 or QString	    Unique identifier for the target chat or username of the target channel (in the format @channelusername) */
        std::future<bool> deleteChatStickerSet(const std::variant<qint64, QString>& chat_id);

        /* @brief Use this method to send answers to callback queries sent from inline keyboards. The answer will be displayed to the user as a notification at the top of the chat screen or as an alert. On success, True is returned
         *
         * > Alternatively, the user can be redirected to the specified Game URL. For this option to work, you must first create a game for your bot via @Botfather and accept the terms.
         * > Otherwise, you may use links like t.me/your_bot?start=XXXX that open your bot with a parameter
         * 
         * @param callback_query_id QString	    Unique identifier for the query to be answered
         * @param text              QString	    Optional. Text of the notification. If not specified, nothing will be shown to the user, 0-200 characters
         * @param show_alert        bool 	    Optional. If true, an alert will be shown by the client instead of a notification at the top of the chat screen. Defaults to false
         * @param url               QString	    Optional. URL that will be opened by the user's client. If you have created a Game and accepted the conditions via @Botfather, specify the URL that opens your game — note that this will only work if the query comes from a callback_game button. Otherwise, you may use links like t.me/your_bot?start=XXXX that open your bot with a parameter
         * @param cache_time        qint32	    Optional. The maximum amount of time in seconds that the result of the callback query may be cached client-side. Telegram apps will support caching starting in version 3.14. Defaults to 0 */
        std::future<bool> answerCallbackQuery(const QString& callback_query_id, const std::optional<QString>& text = std::nullopt, const std::optional<bool>& show_alert = std::nullopt, const std::optional<QString>& url = std::nullopt, const std::optional<qint32>& cache_time = std::nullopt);
        std::future<bool> answerCallbackQuery(const FunctionArguments::AnswerCallbackQuery& arguments);

        /* @brief Use this method to change the list of the bot's commands. See https://core.telegram.org/bots#commands for more details about bot commands. Returns True on success.
         *
         * @param commands          QVector of BotCommand     A list of bot commands to be set as the list of the bot's commands. At most 100 commands can be specified.
         * @param scope             BotCommandScope           Optional. Object, describing scope of users for which the commands are relevant. Defaults to BotCommandScopeDefault.
         * @param language_code     QString	                  Optional. A two-letter ISO 639-1 language code. If empty, commands will be applied to all users from the given scope, for whose language there are no dedicated commands */
        std::future<bool> setMyCommands(const QVector<BotCommand>& commands, const std::optional<BotCommandScope*>& scope = std::nullopt, const std::optional<QString>& language_code = std::nullopt);
        
        /* @brief Use this method to delete the list of the bot's commands for the given scope and user language. After deletion, higher level commands will be shown to affected users. Returns True on success
         *
         * @param scope         BotCommandScope	Optional. Object, describing scope of users for which the commands are relevant. Defaults to BotCommandScopeDefault.
         * @param language_code QString	        Optional. A two-letter ISO 639-1 language code. If empty, commands will be applied to all users from the given scope, for whose language there are no dedicated commands */
        std::future<bool> deleteMyCommands(const std::optional<BotCommandScope*>& scope = std::nullopt, const std::optional<QString>& language_code = std::nullopt);
        
        /* @brief Use this method to get the current list of the bot's commands for the given scope and user language. Returns Array of BotCommand on success. If commands aren't set, an empty list is returned
         *
         * @param scope             BotCommandScope	Optional. Object, describing scope of users for which the commands are relevant. Defaults to BotCommandScopeDefault.
         * @param language_code     QString	        Optional. A two-letter ISO 639-1 language code. If empty, commands will be applied to all users from the given scope, for whose language there are no dedicated commands */
        std::future<QVector<BotCommand>> getMyCommands(const std::optional<BotCommandScope*>& scope = std::nullopt, const std::optional<QString>& language_code = std::nullopt);

//**  Updating messages methods  **//

        /* @brief Use this method to edit text and game messages. On success True is returned
         *
         * @param text	                    QString	                    New text of the message, 1-4096 characters after entities parsing
         * @param chat_id	                qint64 or QString	        Optional. Required if inline_message_id is not specified. Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param message_id	            qint32	                    Optional. Required if inline_message_id is not specified. Identifier of the message to edit
         * @param inline_message_id	        QString	                    Optional. Required if chat_id and message_id are not specified. Identifier of the inline message
         * @param parse_mode	            QString	                    Optional. Mode for parsing entities in the message text
         * @param entities	                QVector of MessageEntity	Optional. List of special entities that appear in message text, which can be specified instead of parse_mode
         * @param disable_web_page_preview  bool	                    Optional. Disables link previews for links in this message
         * @param reply_markup              InlineKeyboardMarkup	    Optional. Object for an inline keyboard */
        std::future<bool> editMessageText(const QString& text, const std::optional<std::variant<qint64, QString>>& chat_id = std::nullopt, const std::optional<qint32>& message_id = std::nullopt, const std::optional<QString>& inline_message_id = std::nullopt, const std::optional<Message::FormattingType>& parse_mode = std::nullopt, const std::optional<QVector<MessageEntity>>& entities = std::nullopt, const std::optional<bool>& disable_web_page_preview = std::nullopt, const std::optional<InlineKeyboardMarkup>& reply_markup = std::nullopt);
        std::future<bool> editMessageText(const FunctionArguments::EditMessageText& arguments);

        /* @brief Use this method to edit captions of messages. On success True is returned
         *
         * @param chat_id	            qint64 or QString	        Optional. Required if inline_message_id is not specified. Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param message_id	        qint32	                    Optional. Required if inline_message_id is not specified. Identifier of the message to edit
         * @param inline_message_id     QString	                    Optional. Required if chat_id and message_id are not specified. Identifier of the inline message
         * @param caption	            QString	                    Optional. New caption of the message, 0-1024 characters after entities parsing
         * @param parse_mode	        QString	                    Optional. Mode for parsing entities in the message caption
         * @param caption_entities      QVector of MessageEntity	Optional. List of special entities that appear in the caption, which can be specified instead of parse_mode
         * @param reply_markup          InlineKeyboardMarkup	    Optional. Object for an inline keyboard */
        std::future<bool> editMessageCaption(const std::optional<std::variant<qint64, QString>>& chat_id = std::nullopt, const std::optional<qint32>& message_id = std::nullopt, const std::optional<QString>& inline_message_id = std::nullopt, const std::optional<QString>& caption = std::nullopt, const std::optional<Message::FormattingType>& parse_mode = std::nullopt, const std::optional<QVector<MessageEntity>>& caption_entities = std::nullopt, const std::optional<InlineKeyboardMarkup>& reply_markup = std::nullopt);
        std::future<bool> editMessageCaption(const FunctionArguments::EditMessageCaption& arguments);

        /* @brief Use this method to edit animation, audio, document, photo, or video messages. On success True is returned
         *
         * If a message is part of a message album, then it can be edited only to an audio for audio albums, only to a document for document albums and to a photo or a video otherwise. 
         * When an inline message is edited, a new file can't be uploaded; use a previously uploaded file via its file_id or specify a URL
         * 
         * @param media	             InputMedia	            An object for a new media content of the message
         * @param chat_id	         qint64 or QString	    Optional. Required if inline_message_id is not specified. Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param message_id         qint32	                Optional. Required if inline_message_id is not specified. Identifier of the message to edit
         * @param inline_message_id	 QString	            Optional. Required if chat_id and message_id are not specified. Identifier of the inline message
         * @param reply_markup       InlineKeyboardMarkup	Optional. Object for an inline keyboard */
        std::future<bool> editMessageMedia(const InputMedia& media, const std::optional<std::variant<qint64, QString>>& chat_id = std::nullopt, const std::optional<qint32>& message_id = std::nullopt, const std::optional<QString>& inline_message_id = std::nullopt, const std::optional<InlineKeyboardMarkup>& reply_markup = std::nullopt);
        std::future<bool> editMessageMedia(const FunctionArguments::EditMessageMedia& arguments);

        /* @brief Use this method to edit only the reply markup of messages. On success True is returned
         *
         * @param chat_id	            qint64 or QString	    Optional. Required if inline_message_id is not specified. Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param message_id	        qint32	                Optional. Required if inline_message_id is not specified. Identifier of the message to edit
         * @param inline_message_id     QString	                Optional. Required if chat_id and message_id are not specified. Identifier of the inline message
         * @param reply_markup          InlineKeyboardMarkup	Optional. Object for an inline keyboard */
        std::future<bool> editMessageReplyMarkup(const std::optional<std::variant<qint64, QString>>& chat_id = std::nullopt, const std::optional<qint32>& message_id = std::nullopt, const std::optional<QString>& inline_message_id = std::nullopt, const std::optional<InlineKeyboardMarkup>& reply_markup = std::nullopt);
        std::future<bool> editMessageReplyMarkup(const FunctionArguments::EditMessageReplyMarkup& arguments);

        /* @brief Use this method to stop a poll which was sent by the bot. On success, the stopped Poll is returned
         *
         * @param chat_id       qint64 or QString	    Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param message_id    qint32	                Identifier of the original message with the poll
         * @param reply_markup  InlineKeyboardMarkup	Optional. An object for a new message inline keyboard */
        std::future<Poll> stopPoll(const std::variant<qint64, QString>& chat_id, const qint32& message_id, const std::optional<InlineKeyboardMarkup>& reply_markup = std::nullopt);

        /* @brief Use this method to delete a message, including service messages, with the limitations listed below. Returns True on success
        * 
        *   Limitations:
        *   • A message can only be deleted if it was sent less than 48 hours ago
        *   • A dice message in a private chat can only be deleted if it was sent more than 24 hours ago
        *   • Bots can delete outgoing messages in private chats, groups, and supergroups
        *   • Bots can delete incoming messages in private chats
        *   • Bots granted can_post_messages permissions can delete outgoing messages in channels
        *   • If the bot is an administrator of a group, it can delete any message there
        *   • If the bot has can_delete_messages permission in a supergroup or a channel, it can delete any message there
        * 
        * @param chat_id      qint64 or QString	    Unique identifier for the target chat or username of the target channel (in the format @channelusername)
        * @param message_id   qint32	            Identifier of the message to delete */
        std::future<bool> deleteMessage(const std::variant<qint64, QString>& chat_id, const qint32& message_id);


//**  Stickers related methods  **//


        /** @brief Use this method to send static .WEBP or animated .TGS stickers. On success, the sent Message is returned
         * 
         * @param chat_id	                    qint64 or QString	                                                                Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param sticker	                    QFile* or QString	                                                                Sticker to send. Pass a file_id as QString to send a sticker that exists on the Telegram servers (recommended), pass an HTTP URL as a QString for Telegram to get an .WEBP file from the Internet, or upload a new photo using QFile(should be opened)
         * @param disable_notification	        bool	                                                                            Optional. Sends the message silently. Users will receive a notification with no sound
         * @param reply_to_message_id	        qint32	                                                                            Optional. If the message is a reply, ID of the original message
         * @param allow_sending_without_reply   bool	                                                                            Optional. Pass True, if the message should be sent even if the specified replied-to message is not found
         * @param reply_markup                  InlineKeyboardMarkup or ReplyKeyboardMarkup or ReplyKeyboardRemove or ForceReply	Optional. Additional interface options. An object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user */
        std::future<Message> sendSticker(const std::variant<qint64, QString>& chat_id, const std::variant<QFile*, QString>& sticker, const std::optional<bool>& disable_notification = std::nullopt, const std::optional<qint32>& reply_to_message_id = std::nullopt, const std::optional<bool>& allow_sending_without_reply = std::nullopt, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup = std::nullopt);
        std::future<Message> sendSticker(const FunctionArguments::SendSticker& arguments);

        /** @brief Use this method to get a sticker set. On success, a StickerSet object is returned
         *
         * @param name  QString  Name of the sticker set */
        std::future<StickerSet> getStickerSet(const QString& name);

        /** @brief Use this method to upload a .PNG file with a sticker for later use in createNewStickerSet and addStickerToSet methods (can be used multiple times). Returns the uploaded *File* on success
         *
         * @param user_id       qint64  User identifier of sticker file owner
         * @param png_sticker   QFile*  PNG image with the sticker, must be up to 512 kilobytes in size, dimensions must not exceed 512px, and either width or height must be exactly 512px */
        std::future<File> uploadStickerFile(const qint64& user_id, QFile* png_sticker);

        /** @brief Use this method to create a new sticker set owned by a user. The bot will be able to edit the sticker set thus created. You must use exactly one of the fields png_sticker or tgs_sticker. Returns True on success
         *
         * @param user_id	        qint64	            User identifier of created sticker set owner
         * @param name	            QString	            Short name of sticker set, to be used in t.me/addstickers/ URLs (e.g., animals). Can contain only english letters, digits and underscores. Must begin with a letter, can't contain consecutive underscores and must end in “_by_<bot username>”. <bot_username> is case insensitive. 1-64 characters.
         * @param title	            QString	            Sticker set title, 1-64 characters
         * @param png_sticker	    QString	            One or more emoji corresponding to the sticker
         * @param tgs_sticker	    QFile* or QString	Optional. PNG image with the sticker, must be up to 512 kilobytes in size, dimensions must not exceed 512px, and either width or height must be exactly 512px. Pass a file_id as QString to send a sticker that exists on the Telegram servers (recommended), pass an HTTP URL as a QString for Telegram to get file from the Internet, or upload a new photo using QFile(should be opened)
         * @param emojis	        QFile*	            Optional. TGS animation with the sticker. See https://core.telegram.org/animated_stickers#technical-requirements for technical requirements
         * @param contains_masks    bool	            Optional. Pass True, if a set of mask stickers should be created
         * @param mask_position     MaskPosition	    Optional. An object for position where the mask should be placed on faces */
        std::future<bool> createNewStickerSet(const qint64& user_id, const QString& name, const QString& title, const QString& emojis, const std::optional<std::variant<QFile*, QString>>& png_sticker = std::nullopt, QFile* tgs_sticker = nullptr, const std::optional<bool>& contains_masks = std::nullopt, const std::optional<MaskPosition>& mask_position = std::nullopt);

        /** @brief Use this method to add a new sticker to a set created by the bot. Returns True on success
         *
         * @param user_id	        qint64	                User identifier of sticker set owner
         * @param name	            QString	                Sticker set name
         * @param png_sticker	    QString	                One or more emoji corresponding to the sticker
         * @param tgs_sticker	    QFile* or QString	    Optional. PNG image with the sticker, must be up to 512 kilobytes in size, dimensions must not exceed 512px, and either width or height must be exactly 512px. Pass a file_id as QString to send a sticker that exists on the Telegram servers (recommended), pass an HTTP URL as a QString for Telegram to get file from the Internet, or upload a new photo using QFile(should be opened)
         * @param emojis	        QFile*	                Optional. TGS animation with the sticker. See https://core.telegram.org/animated_stickers#technical-requirements for technical requirements
         * @param mask_position     MaskPosition	        Optional. An object for position where the mask should be placed on faces */
        std::future<bool> addStickerToSet(const qint64& user_id, const QString& name, const QString& emojis, const std::optional<std::variant<QFile*, QString>>& png_sticker = std::nullopt, QFile* tgs_sticker = nullptr, const std::optional<MaskPosition>& mask_position = std::nullopt);

        /** @brief Use this method to move a sticker in a set created by the bot to a specific position. Returns True on success
         *
         * @param sticker   QString	    File identifier of the sticker
         * @param position  qint32	    New sticker position in the set, zero - based */
        std::future<bool> setStickerPositionInSet(const QString& sticker, const qint32& position);

        /** @brief Use this method to delete a sticker from a set created by the bot. Returns True on success
         *
         * @param sticker   QString	    File identifier of the sticker */
        std::future<bool> deleteStickerFromSet(const QString& sticker);

        /** @brief Use this method to set the thumbnail of a sticker set. Animated thumbnails can be set for animated sticker sets only. Returns True on success
         *
         * @param name      QString	            Sticker set name
         * @param user_id   qint64	            User identifier of the sticker set owner
         * @param thumb     QFile* or QString	Optional. A PNG image with the thumbnail, must be up to 128 kilobytes in size and have width and height exactly 100px, or a TGS animation with the thumbnail up to 32 kilobytes in size; see https://core.telegram.org/animated_stickers#technical-requirements for animated sticker technical requirements. Pass a file_id as QString to send a sticker that exists on the Telegram servers (recommended), pass an HTTP URL as a QString for Telegram to get file from the Internet, or upload a new photo using QFile(should be opened). Animated sticker set thumbnail can't be uploaded via HTTP URL */
        std::future<bool> setStickerSetThumbnail(const QString& name, const qint64& user_id, const std::optional<std::variant<QFile*, QString>>& thumb = std::nullopt);

//**  Inline mode related methods  **//

        /** @brief Use this method to send answers to an inline query. On success, True is returned.
         * 
         * No more than 50 results per query are allowed
         * 
         * @param inline_query_id	    QString	                        Unique identifier for the answered query
         * @param results	            QVector of InlineQueryResult*	An array of results for the inline query
         * @param cache_time	        qint32	                        Optional. The maximum amount of time in seconds that the result of the inline query may be cached on the server. Defaults to 300
         * @param is_personal	        Boolean	                        Optional. Pass True, if results may be cached on the server side only for the user that sent the query. By default, results may be returned to any user who sends the same query
         * @param next_offset	        QString	                        Optional. Pass the offset that a client should send in the next query with the same text to receive more results. Pass an empty string if there are no more results or if you don't support pagination. Offset length can't exceed 64 bytes
         * @param switch_pm_text	    QString	                        Optional. If passed, clients will display a button with specified text that switches the user to a private chat with the bot and sends the bot a start message with the parameter switch_pm_parameter
         * @param switch_pm_parameter   QString	                        Optional. Deep-linking parameter for the /start message sent to the bot when user presses the switch button. 1-64 characters, only A-Z, a-z, 0-9, _ and - are allowed */
        std::future<bool> answerInlineQuery(const QString& inline_query_id, const QVector<InlineQueryResult*> results, const std::optional<qint32>& cache_time = std::nullopt, const std::optional<bool>& is_personal = std::nullopt, const std::optional<QString>& next_offset = std::nullopt, const std::optional<QString>& switch_pm_text = std::nullopt,	const std::optional<QString>& switch_pm_parameter = std::nullopt);

    private:
        std::shared_ptr<BotSettings> bot_settings;

        std::optional<Internal::TelegramListener> telegram_listener;
    };
}

#endif // TELEGRAM_BOT_H


   

   

   


   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

   

