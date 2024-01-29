#ifndef TELEGRAM_FUNCTIONARGUMENTS_H
#define TELEGRAM_FUNCTIONARGUMENTS_H

#include "Types/Message.h"
#include "Types/InlineKeyboardMarkup.h"
#include "Types/ReplyKeyboardMarkup.h"
#include "Types/ReplyKeyboardRemove.h"
#include "Types/ForceReply.h"
#include "Types/InputMediaAudio.h"
#include "Types/InputMediaDocument.h"
#include "Types/InputMediaPhoto.h"
#include "Types/InputMediaVideo.h"

#include <variant>
#include <optional>

#include "qstring.h"
#include "qfile.h"
#include "qvector.h"
#include "qchar.h"

namespace Telegram { namespace FunctionArguments {

    struct SendMessage { 

        /** @brief Unique identifier for the target chat or username of the target channel (in the format @channelusername) */ 
        const std::variant<qint64, QString>& chat_id;

        /** @brief Text of the message to be sent, 1-4096 characters after entities parsing */
        const QString& text;

        /** @brief Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only */
        const std::optional<qint32>& message_thread_id = std::nullopt;

        /** @brief Optional. Mode for parsing entities in the message text. See formatting options for more details. */
        const std::optional<Message::FormattingType>& parse_mode = std::nullopt;

        /** @brief Optional. A JSON-serialized list of special entities that appear in message text, which can be specified instead of parse_mode */
        const std::optional<QVector<MessageEntity>>& entities = std::nullopt;

        /** @brief Optional. Disables link previews for links in this message */
        const std::optional<bool>& disable_web_page_preview = std::nullopt;

        /** @brief Optional. Sends the message silently. Users will receive a notification with no sound. */
        const std::optional<bool>& disable_notification = std::nullopt;

        /** @brief Optional. Protects the contents of the sent message from forwarding and saving */
        const std::optional<bool>& protect_content = std::nullopt;

        /** @brief Optional. If the message is a reply, ID of the original message */
        const std::optional<qint32>& reply_to_message_id = std::nullopt;

        /** @brief Optional. Pass True if the message should be sent even if the specified replied-to message is not found */
        const std::optional<bool>& allow_sending_without_reply = std::nullopt;

        /** @brief Optional. Additional interface options.
         * 
         * An inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user. */
        const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup = std::nullopt;
    };

    struct ForwardMessage { 
        
        /** @brief Unique identifier for the target chat or username of the target channel (in the format @channelusername) */ 
        const std::variant<qint64, QString>& chat_id;

        /** @brief Unique identifier for the chat where the original message was sent (or channel username in the format @channelusername) */
        const std::variant<qint64, QString>& from_chat_id;

        /** @brief Message identifier in the chat specified in from_chat_id */
        const qint32& message_id;

        /** @brief Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only */
        const std::optional<qint32>& message_thread_id = std::nullopt;

        /** @brief Optional. Sends the message silently. Users will receive a notification with no sound. */
        const std::optional<bool>& disable_notification = std::nullopt;

        /** @brief Optional. Protects the contents of the forwarded message from forwarding and saving */
        const std::optional<bool>& protect_content = std::nullopt;
    };

    struct CopyMessage { 
        
        /** @brief Unique identifier for the target chat or username of the target channel (in the format @channelusername) */ 
        const std::variant<qint64, QString>& chat_id;

        /** @brief Unique identifier for the chat where the original message was sent (or channel username in the format @channelusername) */
        const std::variant<qint64, QString>& from_chat_id;

        /** @brief Message identifier in the chat specified in from_chat_id */
        const qint32& message_id;

        /** @brief Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only */
        const std::optional<qint32>& message_thread_id = std::nullopt;

        /** @brief Optional. New caption for media, 0-1024 characters after entities parsing. If not specified, the original caption is kept */
        const std::optional<QString>& caption = std::nullopt;

        /** @brief Optional. Mode for parsing entities in the new caption. See formatting options for more details. */
        const std::optional<Message::FormattingType>& parse_mode = std::nullopt;

        /** @brief Optional. A JSON-serialized list of special entities that appear in the new caption, which can be specified instead of parse_mode */
        const std::optional<QVector<MessageEntity>>& caption_entities = std::nullopt;

        /** @brief Optional. Sends the message silently. Users will receive a notification with no sound. */
        const std::optional<bool>& disable_notification = std::nullopt;

        /** @brief Optional. Protects the contents of the sent message from forwarding and saving */
        const std::optional<bool>& protect_content = std::nullopt;

        /** @brief Optional. If the message is a reply, ID of the original message */
        const std::optional<qint32>& reply_to_message_id = std::nullopt;

        /** @brief Optional. Pass True if the message should be sent even if the specified replied-to message is not found */
        const std::optional<bool>& allow_sending_without_reply = std::nullopt;

        /** @brief Optional. Additional interface options.
         * 
         * A JSON-serialized object for an inline keyboard, custom reply keyboard,instructions to remove reply keyboard or to force a reply from the user. */
        const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup = std::nullopt;
    };

    struct SendPhoto { 
        
        /** @brief Unique identifier for the target chat or username of the target channel (in the format @channelusername) */ 
        const std::variant<qint64, QString>& chat_id;

        /** @brief Photo to send.
         * Pass a file_id as String to send a photo that exists on the Telegram servers (recommended),
         * pass an HTTP URL as a String for Telegram to get a photo from the Internet,
         * or upload a new photo using multipart/form-data.
         * The photo must be at most 10 MB in size.
         * The photo's width and height must not exceed 10000 in total.
         * Width and height ratio must be at most 20. */
        const std::variant<QFile*, QString>& photo;

        /** @brief Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only */
        const std::optional<qint32>& message_thread_id = std::nullopt;

        /** @brief Optional. Photo caption (may also be used when resending photos by file_id), 0-1024 characters after entities parsing */
        const std::optional<QString>& caption = std::nullopt;

        /** @brief Optional. Mode for parsing entities in the photo caption. */
        const std::optional<Message::FormattingType>& parse_mode = std::nullopt;

        /** @brief Optional. A JSON-serialized list of special entities that appear in the caption, which can be specified instead of parse_mode */
        const std::optional<QVector<MessageEntity>>& caption_entities = std::nullopt;

        /** @brief Optional. Pass True if the photo needs to be covered with a spoiler animation */
        const std::optional<bool>& has_spoiler = std::nullopt;

        /** @brief Optional. Sends the message silently. Users will receive a notification with no sound. */
        const std::optional<bool>& disable_notification = std::nullopt;

        /** @brief Optional. Protects the contents of the sent message from forwarding and saving */
        const std::optional<bool>& protect_content = std::nullopt;

        /** @brief Optional. If the message is a reply, ID of the original message */
        const std::optional<qint32>& reply_to_message_id = std::nullopt;

        /** @brief Optional. Pass True if the message should be sent even if the specified replied-to message is not found */
        const std::optional<bool>& allow_sending_without_reply = std::nullopt;

        /** @brief Optional. Additional interface options.
         * 
         * An inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user. */
        const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup = std::nullopt;
    };

    struct SendAudio { 

        /** @brief Unique identifier for the target chat or username of the target channel (in the format @channelusername) */ 
        const std::variant<qint64, QString>& chat_id;

        /** @brief Audio file to send.
         * Pass a file_id as String to send an audio file that exists on the Telegram servers (recommended),
         * pass an HTTP URL as a String for Telegram to get an audio file from the Internet,
         * or upload a new one using multipart/form-data. */
        const std::variant<QFile*, QString>& audio;

        /** @brief Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only */
        const std::optional<qint32>& message_thread_id = std::nullopt;

        /** @brief Optional. Audio caption, 0-1024 characters after entities parsing */
        const std::optional<QString>& caption = std::nullopt;

        /** @brief Optional. Mode for parsing entities in the audio caption. */
        const std::optional<Message::FormattingType>& parse_mode = std::nullopt;

        /** @brief Optional. A JSON-serialized list of special entities that appear in the caption, which can be specified instead of parse_mode */
        const std::optional<QVector<MessageEntity>>& caption_entities = std::nullopt;

        /** @brief Optional. Duration of the audio in seconds */
        const std::optional<qint32>& duration = std::nullopt;

        /** @brief Optional. Performer */
        const std::optional<QString>& performer = std::nullopt;

        /** @brief Optional. Track name */
        const std::optional<QString>& title = std::nullopt;

        /** @brief 	Optional. Thumbnail of the file sent; can be ignored if thumbnail generation for the file is supported server-side.
         * The thumbnail should be in JPEG format and less than 200 kB in size.
         * A thumbnail's width and height should not exceed 320.
         * Ignored if the file is not uploaded using multipart/form-data.
         * Thumbnails can't be reused and can be only uploaded as a new file, so you can pass “attach://<file_attach_name>” if the thumbnail was uploaded using multipart/form-data under <file_attach_name>. */
        const std::optional<std::variant<QFile*, QString>>& thumbnail = std::nullopt;

        /** @brief Optional. Sends the message silently. Users will receive a notification with no sound. */
        const std::optional<bool>& disable_notification = std::nullopt;

        /** @brief Optional. Protects the contents of the sent message from forwarding and saving */
        const std::optional<bool>& protect_content = std::nullopt;

        /** @brief Optional. If the message is a reply, ID of the original message */
        const std::optional<qint32>& reply_to_message_id = std::nullopt;

        /** @brief Optional. Pass True if the message should be sent even if the specified replied-to message is not found */
        const std::optional<bool>& allow_sending_without_reply = std::nullopt;

        /** @brief Optional. Additional interface options.
         * 
         * An inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user. */
        const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup = std::nullopt;
    };

    struct SendDocument { 
        
        /** @brief Unique identifier for the target chat or username of the target channel (in the format @channelusername) */ 
        const std::variant<qint64, QString>& chat_id;

        /** @brief File to send.
         * Pass a file_id as String to send a file that exists on the Telegram servers (recommended),
         * pass an HTTP URL as a String for Telegram to get a file from the Internet,
         * or upload a new one using multipart/form-data.  */
        const std::variant<QFile*, QString>& document;

        /** @brief Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only */
        const std::optional<qint32>& message_thread_id = std::nullopt;

        /** @brief Optional. Thumbnail of the file sent; can be ignored if thumbnail generation for the file is supported server-side.
         * The thumbnail should be in JPEG format and less than 200 kB in size.
         * A thumbnail's width and height should not exceed 320.
         * Ignored if the file is not uploaded using multipart/form-data.
         * Thumbnails can't be reused and can be only uploaded as a new file, so you can pass “attach://<file_attach_name>” if the thumbnail was uploaded using multipart/form-data under <file_attach_name>. */
        const std::optional<std::variant<QFile*, QString>>& thumbnail = std::nullopt;

        /** @brief Optional. Document caption (may also be used when resending documents by file_id), 0-1024 characters after entities parsing */
        const std::optional<QString>& caption = std::nullopt;

        /** @brief Optional. Mode for parsing entities in the document caption. */
        const std::optional<Message::FormattingType>& parse_mode = std::nullopt;

        /** @brief Optional. A JSON-serialized list of special entities that appear in the caption, which can be specified instead of parse_mode */
        const std::optional<QVector<MessageEntity>>& caption_entities = std::nullopt;

        /** @brief Optional. Disables automatic server-side content type detection for files uploaded using multipart/form-data */
        const std::optional<bool>& disable_content_type_detection = std::nullopt;

        /** @brief Optional. Sends the message silently. Users will receive a notification with no sound. */
        const std::optional<bool>& disable_notification = std::nullopt;

        /** @brief Optional. Protects the contents of the sent message from forwarding and saving */
        const std::optional<bool>& protect_content = std::nullopt;

        /** @brief Optional. If the message is a reply, ID of the original message */
        const std::optional<qint32>& reply_to_message_id = std::nullopt;

        /** @brief Optional. Pass True if the message should be sent even if the specified replied-to message is not found */
        const std::optional<bool>& allow_sending_without_reply = std::nullopt;

        /** @brief Optional. Additional interface options.
         * 
         * An inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user. */
        const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup = std::nullopt;
    };

    struct SendVideo { 
        
        /** @brief Unique identifier for the target chat or username of the target channel (in the format @channelusername) */ 
        const std::variant<qint64, QString>& chat_id;

        /** @brief Video to send.
         * Pass a file_id as String to send a video that exists on the Telegram servers (recommended),
         * pass an HTTP URL as a String for Telegram to get a video from the Internet,
         * or upload a new video using multipart/form-data. */
        const std::variant<QFile*, QString>& video;

        /** @brief Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only */
        const std::optional<qint32>& message_thread_id = std::nullopt;

        /** @brief Optional. Duration of sent video in seconds */
        const std::optional<qint32>& duration = std::nullopt;

        /** @brief Optional. Video width */
        const std::optional<qint32>& width = std::nullopt;

        /** @brief Optional. Video height */
        const std::optional<qint32>& height = std::nullopt;

        /** @brief Optional. Thumbnail of the file sent; can be ignored if thumbnail generation for the file is supported server-side.
         * The thumbnail should be in JPEG format and less than 200 kB in size.
         * A thumbnail's width and height should not exceed 320.
         * Ignored if the file is not uploaded using multipart/form-data.
         * Thumbnails can't be reused and can be only uploaded as a new file, so you can pass “attach://<file_attach_name>” if the thumbnail was uploaded using multipart/form-data under <file_attach_name>. */
        const std::optional<std::variant<QFile*, QString>>& thumbnail = std::nullopt;

        /** @brief Optional. Video caption (may also be used when resending videos by file_id), 0-1024 characters after entities parsing */
        const std::optional<QString>& caption = std::nullopt;

        /** @brief Optional. Mode for parsing entities in the video caption. See formatting options for more details. */
        const std::optional<Message::FormattingType>& parse_mode = std::nullopt;

        /** @brief Optional. A JSON-serialized list of special entities that appear in the caption, which can be specified instead of parse_mode */
        const std::optional<QVector<MessageEntity>>& caption_entities = std::nullopt;

        /** @brief Optional. Pass True if the video needs to be covered with a spoiler animation */
        const std::optional<bool>& has_spoiler = std::nullopt;

        /** @brief Optional. Pass True if the uploaded video is suitable for streaming */
        const std::optional<bool>& supports_streaming = std::nullopt;

        /** @brief Optional. Sends the message silently. Users will receive a notification with no sound. */
        const std::optional<bool>& disable_notification = std::nullopt;

        /** @brief Optional. Protects the contents of the sent message from forwarding and saving */
        const std::optional<bool>& protect_content = std::nullopt;

        /** @brief Optional. If the message is a reply, ID of the original message */
        const std::optional<qint32>& reply_to_message_id = std::nullopt;

        /** @brief Optional. Pass True if the message should be sent even if the specified replied-to message is not found */
        const std::optional<bool>& allow_sending_without_reply = std::nullopt;

        /** @brief Optional. Additional interface options.
         * 
         * An inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user. */
        const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup = std::nullopt;
    };

    struct SendAnimation { 
        
        /** @brief Unique identifier for the target chat or username of the target channel (in the format @channelusername) */ 
        const std::variant<qint64, QString>& chat_id;

        /** @brief Animation to send.
         * Pass a file_id as String to send an animation that exists on the Telegram servers (recommended),
         * pass an HTTP URL as a String for Telegram to get an animation from the Internet,
         * or upload a new animation using multipart/form-data. */
        const std::variant<QFile*, QString>& animation;

        /** @brief Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only */
        const std::optional<qint32>& message_thread_id = std::nullopt;

        /** @brief Optional. Duration of sent animation in seconds */
        const std::optional<qint32>& duration = std::nullopt;

        /** @brief Optional. Animation width */
        const std::optional<qint32>& width = std::nullopt;

        /** @brief Optional. Animation height */
        const std::optional<qint32>& height = std::nullopt;

        /** @brief Optional. Thumbnail of the file sent; can be ignored if thumbnail generation for the file is supported server-side.
         * The thumbnail should be in JPEG format and less than 200 kB in size.
         * A thumbnail's width and height should not exceed 320.
         * Ignored if the file is not uploaded using multipart/form-data.
         * Thumbnails can't be reused and can be only uploaded as a new file, so you can pass “attach://<file_attach_name>” if the thumbnail was uploaded using multipart/form-data under <file_attach_name>.*/
        const std::optional<std::variant<QFile*, QString>>& thumbnail = std::nullopt;

        /** @brief Optional. Animation caption (may also be used when resending animation by file_id), 0-1024 characters after entities parsing */
        const std::optional<QString>& caption = std::nullopt;

        /** @brief Optional. Mode for parsing entities in the animation caption. See formatting options for more details. */
        const std::optional<Message::FormattingType>& parse_mode = std::nullopt;

        /** @brief Optional. A JSON-serialized list of special entities that appear in the caption, which can be specified instead of parse_mode */
        const std::optional<QVector<MessageEntity>>& caption_entities = std::nullopt;

        /** @brief Optional. Pass True if the animation needs to be covered with a spoiler animation */
        const std::optional<bool>& has_spoiler = std::nullopt;

        /** @brief Optional. Sends the message silently. Users will receive a notification with no sound. */
        const std::optional<bool>& disable_notification = std::nullopt;

        /** @brief Optional. Protects the contents of the sent message from forwarding and saving */
        const std::optional<bool>& protect_content = std::nullopt;

        /** @brief Optional. If the message is a reply, ID of the original message */
        const std::optional<qint32>& reply_to_message_id = std::nullopt;

        /** @brief Optional. Pass True if the message should be sent even if the specified replied-to message is not found */
        const std::optional<bool>& allow_sending_without_reply = std::nullopt;

        /** @brief Optional. Additional interface options.
         * 
         * An inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user. */
        const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup = std::nullopt;
    };

    struct SendVoice { 
        
        /** @brief Unique identifier for the target chat or username of the target channel (in the format @channelusername) */ 
        const std::variant<qint64, QString>& chat_id;

        /** @brief Audio file to send.
         * Pass a file_id as String to send a file that exists on the Telegram servers (recommended),
         * pass an HTTP URL as a String for Telegram to get a file from the Internet,
         * or upload a new one using multipart/form-data. */
        const std::variant<QFile*, QString>& voice;

        /** @brief Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only */
        const std::optional<qint32>& message_thread_id = std::nullopt;
        
        /** @brief Optional. Voice message caption, 0-1024 characters after entities parsing */
        const std::optional<QString>& caption = std::nullopt;
        
        /** @brief Optional. Mode for parsing entities in the voice message caption. */
        const std::optional<Message::FormattingType>& parse_mode = std::nullopt;
        
        /** @brief Optional. A JSON-serialized list of special entities that appear in the caption, which can be specified instead of parse_mode */
        const std::optional<QVector<MessageEntity>>& caption_entities = std::nullopt;
        
        /** @brief Optional.Duration of the voice message in seconds */
        const std::optional<qint32>& duration = std::nullopt;
        
        /** @brief Optional. Sends the message silently. Users will receive a notification with no sound. */
        const std::optional<bool>& disable_notification = std::nullopt;
        
        /** @brief Optional. Protects the contents of the sent message from forwarding and saving */
        const std::optional<bool>& protect_content = std::nullopt;
        
        /** @brief Optional. If the message is a reply, ID of the original message */
        const std::optional<qint32>& reply_to_message_id = std::nullopt;
        
        /** @brief Optional. Pass True if the message should be sent even if the specified replied-to message is not found */
        const std::optional<bool>& allow_sending_without_reply = std::nullopt;
        
        /** @brief Optional. Additional interface options.
         * 
         * An inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user. */
        const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup = std::nullopt;
    };

    struct SendVideoNote { 
        
        /** @brief Unique identifier for the target chat or username of the target channel (in the format @channelusername) */ 
        const std::variant<qint64, QString>& chat_id;

        /** @brief Video note to send.
         * Pass a file_id as String to send a video note that exists on the Telegram servers (recommended)
         * or upload a new video using multipart/form-data. */
        const std::variant<QFile*, QString>& video_note;

        /** @brief Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only */
        const std::optional<qint32>& message_thread_id = std::nullopt;

        /** @brief Optional. Duration of sent video in seconds */
        const std::optional<qint32>& duration = std::nullopt;

        /** @brief Optional. Video width and height, i.e. diameter of the video message */
        const std::optional<qint32>& length = std::nullopt;

        /** @brief Optional. Thumbnail of the file sent; can be ignored if thumbnail generation for the file is supported server-side.
         * The thumbnail should be in JPEG format and less than 200 kB in size.
         * A thumbnail's width and height should not exceed 320.
         * Ignored if the file is not uploaded using multipart/form-data.
         * Thumbnails can't be reused and can be only uploaded as a new file, so you can pass “attach://<file_attach_name>” if the thumbnail was uploaded using multipart/form-data under <file_attach_name>. */
        const std::optional<std::variant<QFile*, QString>>& thumbnail = std::nullopt;

        /** @brief Optional. Sends the message silently. Users will receive a notification with no sound. */
        const std::optional<bool>& disable_notification = std::nullopt;

        /** @brief Optional. Protects the contents of the sent message from forwarding and saving */
        const std::optional<bool>& protect_content = std::nullopt;

        /** @brief Optional. If the message is a reply, ID of the original message */
        const std::optional<qint32>& reply_to_message_id = std::nullopt;

        /** @brief Optional. Pass True if the message should be sent even if the specified replied-to message is not found */
        const std::optional<bool>& allow_sending_without_reply = std::nullopt;

        /** @brief Optional. Additional interface options.
         * 
         * An inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user. */
        const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup = std::nullopt;
    };

    struct SendMediaGroup_Audio { 
        
        /** @brief Unique identifier for the target chat or username of the target channel (in the format @channelusername) */ 
        const std::variant<qint64, QString>& chat_id;

        /** @brief Vector of InputMediaAudio describing bunch of audios to be sent, must include 2-10 items */
        const QVector<InputMediaAudio>& media;

        /** @brief Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only */
        const std::optional<qint32>& message_thread_id = std::nullopt;

        /** @brief Optional. Sends messages silently. Users will receive a notification with no sound. */
        const std::optional<bool>& disable_notification = std::nullopt;

        /** @brief Optional. Protects the contents of the sent messages from forwarding and saving */
        const std::optional<bool>& protect_content = std::nullopt;

        /** @brief Optional. If the messages are a reply, ID of the original message */
        const std::optional<qint32>& reply_to_message_id = std::nullopt;

        /** @brief Optional. Pass True if the message should be sent even if the specified replied-to message is not found */
        const std::optional<bool>& allow_sending_without_reply = std::nullopt;
    };

    struct SendMediaGroup_Document { 
        
        /** @brief Unique identifier for the target chat or username of the target channel (in the format @channelusername) */ 
        const std::variant<qint64, QString>& chat_id;

        /** @brief Vector of InputMediaDocument describing bunch of documents to be sent, must include 2-10 items */
        const QVector<InputMediaDocument>& media;

        /** @brief Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only */
        const std::optional<qint32>& message_thread_id = std::nullopt;

        /** @brief Optional. Sends messages silently. Users will receive a notification with no sound. */
        const std::optional<bool>& disable_notification = std::nullopt;

        /** @brief Optional. Protects the contents of the sent messages from forwarding and saving */
        const std::optional<bool>& protect_content = std::nullopt;

        /** @brief Optional. If the messages are a reply, ID of the original message */
        const std::optional<qint32>& reply_to_message_id = std::nullopt;

        /** @brief Optional. Pass True if the message should be sent even if the specified replied-to message is not found */
        const std::optional<bool>& allow_sending_without_reply = std::nullopt;
    };

    struct SendMediaGroup_PhotoVideo { 
        
        /** @brief Unique identifier for the target chat or username of the target channel (in the format @channelusername) */ 
        const std::variant<qint64, QString>& chat_id;

        /** @brief Vector of InputMediaPhoto describing bunch of photos to be sent, must include 2-10 items. Can be empty if videos is present */
        const QVector<InputMediaPhoto>& photos;

        /** @brief Vector of InputMediaVideo describing bunch of videos to be sent, must include 2-10 items. Can be empty if photos is present */
        const QVector<InputMediaVideo>& videos;

        /** @brief Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only */
        const std::optional<qint32>& message_thread_id = std::nullopt;

        /** @brief Optional. Sends messages silently. Users will receive a notification with no sound. */
        const std::optional<bool>& disable_notification = std::nullopt;

        /** @brief Optional. Protects the contents of the sent messages from forwarding and saving */
        const std::optional<bool>& protect_content = std::nullopt;

        /** @brief Optional. If the messages are a reply, ID of the original message */
        const std::optional<qint32>& reply_to_message_id = std::nullopt;

        /** @brief Optional. Pass True if the message should be sent even if the specified replied-to message is not found */
        const std::optional<bool>& allow_sending_without_reply = std::nullopt;
    };

    struct SendLocation { 
        
        /** @brief Unique identifier for the target chat or username of the target channel (in the format @channelusername) */ 
        const std::variant<qint64, QString>& chat_id;

        /** @brief Latitude of the location */
        const float& latitude;

        /** @brief Longitude of the location */
        const float& longitude;

        /** @brief Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only */
        const std::optional<qint32>& message_thread_id = std::nullopt;

        /** @brief Optional. The radius of uncertainty for the location, measured in meters; 0-1500 */
        const std::optional<float>& horizontal_accuracy = std::nullopt;

        /** @brief Optional. Period in seconds for which the location will be updated, should be between 60 and 86400 */
        const std::optional<qint32>& live_period = std::nullopt;

        /** @brief Optional. For live locations, a direction in which the user is moving, in degrees. Must be between 1 and 360 if specified. */
        const std::optional<qint32>& heading = std::nullopt;

        /** @brief Optional. For live locations, a maximum distance for proximity alerts about approaching another chat member, in meters. Must be between 1 and 100000 if specified. */
        const std::optional<qint32>& proximity_alert_radius = std::nullopt;

        /** @brief Optional. Sends the message silently. Users will receive a notification with no sound. */
        const std::optional<bool>& disable_notification = std::nullopt;

        /** @brief Optional. Protects the contents of the sent message from forwarding and saving */
        const std::optional<bool>& protect_content = std::nullopt;

        /** @brief Optional. If the message is a reply, ID of the original message */
        const std::optional<qint32>& reply_to_message_id = std::nullopt;

        /** @brief Optional. Pass True if the message should be sent even if the specified replied-to message is not found */
        const std::optional<bool>& allow_sending_without_reply = std::nullopt;

        /** @brief Optional. Additional interface options.
         * 
         * An inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user. */
        const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup = std::nullopt;
    };

    struct EditMessageLiveLocation {
        
        /** @brief Latitude of new location */
        const float& latitude;

        /** @brief Longitude of new location */
        const float& longitude;

        /** @brief Optional. Unique identifier for the target chat or username of the target channel (in the format @channelusername) 
         *
         * Required if inline_message_id is not specified */ 
        const std::optional<std::variant<qint64, QString>>& chat_id = std::nullopt;

        /** @brief Optional. Identifier of the message to edit
         *    
         * Required if inline_message_id is not specified */ 
        const std::optional<qint32>& message_id = std::nullopt;

        /** @brief Optional. Identifier of the inline message 
         *    
         * Required if chat_id and message_id are not specified. */ 
        const std::optional<QString>& inline_message_id = std::nullopt;

        /** @brief Optional. The radius of uncertainty for the location, measured in meters; 0-1500 */
        const std::optional<float>& horizontal_accuracy = std::nullopt;

        /** @brief Optional. Direction in which the user is moving, in degrees. Must be between 1 and 360 if specified */
        const std::optional<qint32>& heading = std::nullopt;

        /** @brief Optional. The maximum distance for proximity alerts about approaching another chat member, in meters. Must be between 1 and 100000 if specified */
        const std::optional<qint32>& proximity_alert_radius = std::nullopt;

        /** @brief Optional. An object for a new inline keyboard */
        const std::optional<InlineKeyboardMarkup>& reply_markup = std::nullopt;
    };

    struct StopMessageLiveLocation {

        /** @brief Optional. Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         *
         * Required if inline_message_id is not specified */
        const std::optional<std::variant<qint64, QString>>& chat_id = std::nullopt;

        /** @brief Optional. Identifier of the message to edit
         *
         * Required if inline_message_id is not specified */
        const std::optional<qint32>& message_id = std::nullopt;

        /** @brief Optional. Identifier of the inline message
         *
         * Required if chat_id and message_id are not specified. */
        const std::optional<QString>& inline_message_id = std::nullopt;

        /** @brief Optional. An object for a new inline keyboard */
        const std::optional<InlineKeyboardMarkup>& reply_markup = std::nullopt;
    };

    struct SendVenue { 
        
        /** @brief Unique identifier for the target chat or username of the target channel (in the format @channelusername) */ 
        const std::variant<qint64, QString>& chat_id;

        /** @brief Latitude of the venue */
        const float& latitude;

        /** @brief Longitude of the venue */
        const float& longitude;

        /** @brief Name of the venue */
        const QString& title;

        /** @brief Address of the venue */
        const QString& address;

        /** @brief Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only */
        const std::optional<qint32>& message_thread_id = std::nullopt;

        /** @brief Optional. Foursquare identifier of the venue */
        const std::optional<QString>& foursquare_id = std::nullopt;

        /** @brief Optional. Foursquare type of the venue, if known. (For example, “arts_entertainment/default”, “arts_entertainment/aquarium”, or “food/icecream”.) */
        const std::optional<QString>& foursquare_type = std::nullopt;

        /** @brief Optional. Google Places identifier of the venue */
        const std::optional<QString>& google_place_id = std::nullopt;

        /** @brief Optional. Google Places type of the venue. */
        const std::optional<QString>& google_place_type = std::nullopt;

        /** @brief Optional. Sends the message silently. Users will receive a notification with no sound. */
        const std::optional<bool>& disable_notification = std::nullopt;

        /** @brief Optional. Protects the contents of the sent message from forwarding and saving */
        const std::optional<bool>& protect_content = std::nullopt;

        /** @brief Optional. If the message is a reply, ID of the original message */
        const std::optional<qint32>& reply_to_message_id = std::nullopt;

        /** @brief Optional. Pass True if the message should be sent even if the specified replied-to message is not found */
        const std::optional<bool>& allow_sending_without_reply = std::nullopt;

        /** @brief Optional. Additional interface options.
         * 
         * An inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user. */
        const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup = std::nullopt;
    };

    struct SendContact { 
        
        /** @brief Unique identifier for the target chat or username of the target channel (in the format @channelusername) */ 
        const std::variant<qint64, QString>& chat_id;

        /** @brief Contact's phone number */
        const QString& phone_number;

        /** @brief Contact's first name */
        const QString& first_name;

        /** @brief Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only */
        const std::optional<qint32>& message_thread_id = std::nullopt;

        /** @brief Optional. Contact's last name */
        const std::optional<QString>& last_name = std::nullopt;

        /** @brief Optional. Additional data about the contact in the form of a vCard, 0-2048 bytes */
        const std::optional<QString>& vcard = std::nullopt;

        /** @brief Optional. Sends the message silently. Users will receive a notification with no sound. */
        const std::optional<bool>& disable_notification = std::nullopt;

        /** @brief Optional. Protects the contents of the sent message from forwarding and saving */
        const std::optional<bool>& protect_content = std::nullopt;

        /** @brief Optional. If the message is a reply, ID of the original message */
        const std::optional<qint32>& reply_to_message_id = std::nullopt;

        /** @brief Optional. Pass True if the message should be sent even if the specified replied-to message is not found */
        const std::optional<bool>& allow_sending_without_reply = std::nullopt;

        /** @brief Optional. Additional interface options.
         * 
         * An inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user. */
        const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup = std::nullopt;
    };

    struct SendPoll { 
        
        /** @brief Unique identifier for the target chat or username of the target channel (in the format @channelusername) */ 
        const std::variant<qint64, QString>& chat_id;

        /** @brief Poll question, 1-300 characters */
        const QString& question;

        /** @brief A list of answer options, 2-10 strings 1-100 characters each */
        const QVector<QString>& options;

        /** @brief Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only */
        const std::optional<qint32>& message_thread_id = std::nullopt;
        
        /** @brief Optional. True, if the poll needs to be anonymous, defaults to True */
        const std::optional<bool>& is_anonymous = std::nullopt;
        
        /** @brief Optional. Poll type, “quiz” or “regular”, defaults to “regular” */
        const std::optional<QString>& type = std::nullopt;
        
        /** @brief Optional. True, if the poll allows multiple answers, ignored for polls in quiz mode, defaults to False */
        const std::optional<bool>& allows_multiple_answers = std::nullopt;
        
        /** @brief Optional. 0-based identifier of the correct answer option, required for polls in quiz mode */
        const std::optional<qint32>& correct_option_id = std::nullopt;
        
        /** @brief Optional. Text that is shown when a user chooses an incorrect answer or taps on the lamp icon in a quiz-style poll, 0-200 characters with at most 2 line feeds after entities parsing */
        const std::optional<QString>& explanation = std::nullopt;
        
        /** @brief Optional. Mode for parsing entities in the explanation. */
        const std::optional<Message::FormattingType>& explanation_parse_mode = std::nullopt;
        
        /** @brief Optional. A list of special entities that appear in the poll explanation, which can be specified instead of explanation_parse_mode */
        const std::optional<QVector<MessageEntity>>& explanation_entities = std::nullopt;
        
        /** @brief Optional. Amount of time in seconds the poll will be active after creation, 5-600. Can't be used together with close_date. */
        const std::optional<qint32>& open_period = std::nullopt;
        
        /** @brief Optional. Point in time (Unix timestamp) when the poll will be automatically closed. Must be at least 5 and no more than 600 seconds in the future. Can't be used together with open_period. */
        const std::optional<qint32>& close_date = std::nullopt;
        
        /** @brief Optional. Pass True if the poll needs to be immediately closed. This can be useful for poll preview. */
        const std::optional<bool>& is_closed = std::nullopt;
        
        /** @brief Optional. Sends the message silently. Users will receive a notification with no sound. */
        const std::optional<bool>& disable_notification = std::nullopt;
        
        /** @brief Optional. Protects the contents of the sent message from forwarding and saving */
        const std::optional<bool>& protect_content = std::nullopt;
        
        /** @brief Optional. If the message is a reply, ID of the original message */
        const std::optional<qint32>& reply_to_message_id = std::nullopt;
        
        /** @brief Optional. Pass True if the message should be sent even if the specified replied-to message is not found */
        const std::optional<bool>& allow_sending_without_reply = std::nullopt;
        
        /** @brief Optional. Additional interface options.
         * 
         * An inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user. */
        const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup = std::nullopt;
    };

    struct SendDice {

        /** @brief Unique identifier for the target chat or username of the target channel (in the format @channelusername) */
        const std::variant<qint64, QString>& chat_id;

        /** @brief Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only */
        const std::optional<qint32>& message_thread_id = std::nullopt;

        /** @brief Optional. Emoji on which the dice throw animation is based.
           Currently, must be one of “🎲”, “🎯”, “🏀”, “⚽”, “🎳”, or “🎰”.
           Dice can have values 1-6 for “🎲”, “🎯” and “🎳”, values 1-5 for “🏀” and “⚽”,
           and values 1-64 for “🎰”. Defaults to “🎲” */
        const std::optional<QString>& emoji = std::nullopt;

        /** @brief Optional. Sends the message silently. Users will receive a notification with no sound. */
        const std::optional<bool>& disable_notification = std::nullopt;

        /** @brief Optional. Protects the contents of the sent message from forwarding */
        const std::optional<bool>& protect_content = std::nullopt;

        /** @brief Optional. If the message is a reply, ID of the original message */
        const std::optional<qint32>& reply_to_message_id = std::nullopt;

        /** @brief Optional. Pass True if the message should be sent even if the specified replied-to message is not found */
        const std::optional<bool>& allow_sending_without_reply = std::nullopt;

        /** @brief Optional. Additional interface options.
         *
         * An inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user. */
        const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup = std::nullopt;
    };

    struct PromoteChatMember {

        /** @brief Unique identifier for the target chat or username of the target channel (in the format @channelusername) */ 
        const std::variant<qint64, QString>& chat_id;

        /** @brief Unique identifier of the target user */
        const qint64& user_id;

        /** @brief Optional. Pass True if the administrator's presence in the chat is hidden */
        const std::optional<bool>& is_anonymous = std::nullopt;

        /** @brief Optional. Pass True if the administrator can access the chat event log, boost list in channels, see channel members, report spam messages, see anonymous administrators in supergroups and ignore slow mode. Implied by any other administrator privilege */
        const std::optional<bool>& can_manage_chat = std::nullopt;

        /** @brief Optional. Pass True if the administrator can delete messages of other users */
        const std::optional<bool>& can_delete_messages = std::nullopt;

        /** @brief Optional. Pass True if the administrator can manage video chats */
        const std::optional<bool>& can_manage_video_chats = std::nullopt;

        /** @brief Optional. Pass True if the administrator can restrict, ban or unban chat members, or access supergroup statistics */
        const std::optional<bool>& can_restrict_members = std::nullopt;

        /** @brief Optional. Pass True if the administrator can add new administrators with a subset of their own privileges or demote administrators that they have promoted, directly or indirectly (promoted by administrators that were appointed by him) */
        const std::optional<bool>& can_promote_members = std::nullopt;

        /** @brief Optional. Pass True if the administrator can change chat title, photo and other settings */
        const std::optional<bool>& can_change_info = std::nullopt;

        /** @brief Optional. Pass True if the administrator can invite new users to the chat */
        const std::optional<bool>& can_invite_users = std::nullopt;

        /** @brief Optional. Pass True if the administrator can post messages in the channel, or access channel statistics; channels only */
        const std::optional<bool>& can_post_messages = std::nullopt;

        /** @brief Optional. Pass True if the administrator can edit messages of other users and can pin messages; channels only */
        const std::optional<bool>& can_edit_messages = std::nullopt;

        /** @brief Optional. Pass True if the administrator can pin messages, supergroups only */
        const std::optional<bool>& can_pin_messages = std::nullopt;

        /** @brief Optional. Pass True if the administrator can post stories in the channel; channels only */
        const std::optional<bool>& can_post_stories = std::nullopt;

        /** @brief Optional. Pass True if the administrator can edit stories posted by other users; channels only */
        const std::optional<bool>& can_edit_stories = std::nullopt;

        /** @brief Optional. Pass True if the administrator can delete stories posted by other users; channels only */
        const std::optional<bool>& can_delete_stories = std::nullopt;

        /** @brief Optional. Pass True if the user is allowed to create, rename, close, and reopen forum topics, supergroups only */
        const std::optional<bool>& can_manage_topics = std::nullopt;
    };

    struct CreateChatInviteLink {

        /** @brief Unique identifier for the target chat or username of the target channel (in the format @channelusername) */
        const std::variant<qint64, QString>& chat_id;

        /** @brief Optional. Invite link name; 0-32 characters */
        const std::optional<QString>& name = std::nullopt;

        /** @brief Optional. Point in time (Unix timestamp) when the link will expire */
        const std::optional<qint32>& expire_date = std::nullopt;

        /** @brief Optional. The maximum number of users that can be members of the chat simultaneously after joining the chat via this invite link; 1-99999 */
        const std::optional<qint32>& member_limit = std::nullopt;

        /** @brief Optional. True, if users joining the chat via the link need to be approved by chat administrators. If True, member_limit can't be specified */
        const std::optional<bool>& creates_join_request = std::nullopt;
    };

    struct EditChatInviteLink {

        /** @brief Unique identifier for the target chat or username of the target channel (in the format @channelusername) */ 
        const std::variant<qint64, QString>& chat_id;

        /** @brief The invite link to edit */
        const QString& invite_link;

        /** @brief Optional. Invite link name; 0-32 characters */
        const std::optional<QString>& name = std::nullopt;

        /** @brief Optional. Point in time (Unix timestamp) when the link will expire */
        const std::optional<qint32>& expire_date = std::nullopt;

        /** @brief Optional. The maximum number of users that can be members of the chat simultaneously after joining the chat via this invite link; 1-99999 */
        const std::optional<qint32>& member_limit = std::nullopt;

        /** @brief Optional. True, if users joining the chat via the link need to be approved by chat administrators. If True, member_limit can't be specified */
        const std::optional<bool>& creates_join_request = std::nullopt;
    };

    struct AnswerCallbackQuery {
        
        /** @brief Unique identifier for the query to be answered */ 
        const QString& callback_query_id;

        /** @brief Optional. Text of the notification */
        const std::optional<QString>& text = std::nullopt;

        /** @brief Optional. If True, an alert will be shown by the client instead of a notification at the top of the chat screen */
        const std::optional<bool>& show_alert = std::nullopt;

        /** @brief Optional. URL that will be opened by the user's client */
        const std::optional<QString>& url = std::nullopt;

        /** @brief Optional. The maximum amount of time in seconds that the result of the callback query may be cached client-side */
        const std::optional<qint32>& cache_time = std::nullopt;
    };

    struct EditMessageText {

        /** @brief Unique identifier for the target chat or username of the target channel (in the format @channelusername) */
        const std::variant<qint64, QString>& chat_id;

        /** @brief New text of the message, 1-4096 characters after entities parsing */
        const QString& text;

        /** @brief Optional. Identifier of the message to edit */
        const std::optional<qint32>& message_id = std::nullopt;

        /** @brief Optional. Identifier of the inline message */
        const std::optional<QString>& inline_message_id = std::nullopt;

        /** @brief Optional. Mode for parsing entities in the message text */
        const std::optional<Message::FormattingType>& parse_mode = std::nullopt;

        /** @brief Optional. A list of special entities that appear in message text */
        const std::optional<QVector<MessageEntity>>& entities = std::nullopt;

        /** @brief Optional. Disables link previews for links in this message */
        const std::optional<bool>& disable_web_page_preview = std::nullopt;

        /** @brief Optional. Inline keyboard marku */
        const std::optional<InlineKeyboardMarkup>& reply_markup = std::nullopt;
    };

    struct EditMessageCaption { 
        
        /** @brief Optional. Unique identifier for the target chat or username of the target channel */ 
        const std::variant<qint64, QString>& chat_id;

        /** @brief Optional. Identifier of the message to edit */
        const std::optional<qint32>& message_id = std::nullopt;

        /** @brief Optional. Identifier of the inline message */
        const std::optional<QString>& inline_message_id = std::nullopt;

        /** @brief Optional. New caption of the message */
        const std::optional<QString>& caption = std::nullopt;

        /** @brief Optional. Mode for parsing entities in the message caption */
        const std::optional<Message::FormattingType>& parse_mode = std::nullopt;

        /** @brief Optional. List of special entities that appear in the caption */
        const std::optional<QVector<MessageEntity>>& caption_entities = std::nullopt;

        /** @brief Optional. Inline keyboard markup */
        const std::optional<InlineKeyboardMarkup>& reply_markup = std::nullopt;
    };

    struct EditMessageMedia { 
        
        /** @brief New media content of the message */
        const InputMedia& media;

        /** @brief Optional. Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         *
         * Required if inline_message_id is not specified */ 
        const std::optional<std::variant<qint64, QString>>& chat_id = std::nullopt;

        /** @brief Optional. Identifier of the message to edit
         *
         * Required if inline_message_id is not specified */ 
        const std::optional<qint32>& message_id = std::nullopt;

        /** @brief Optional. Identifier of the inline message
         *
         * Required if chat_id and message_id are not specified */ 
        const std::optional<QString>& inline_message_id = std::nullopt;

        /** @brief Optional. New inline keyboard */
        const std::optional<InlineKeyboardMarkup>& reply_markup = std::nullopt;
    };

    struct EditMessageReplyMarkup { 
        
        /** @brief Optional. Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         *
         * Required if inline_message_id is not specified */
        const std::optional<std::variant<qint64, QString>>& chat_id = std::nullopt;

        /** @brief Optional. Identifier of the message to edit
         *
         * Required if inline_message_id is not specified */
        const std::optional<qint32>& message_id = std::nullopt;

        /** @brief Optional. Identifier of the inline message
         *
         * Required if chat_id and message_id are not specified */
        const std::optional<QString>& inline_message_id = std::nullopt;

        /** @brief Optional. A JSON-serialized object for an inline keyboard */
        const std::optional<InlineKeyboardMarkup>& reply_markup = std::nullopt;
    };

    struct SendSticker { 
        
        /** @brief Unique identifier for the target chat or username of the target channel (in the format @channelusername) */ 
        const std::variant<qint64, QString>& chat_id;

        /** @brief Sticker to send */
        const std::variant<QFile*, QString>& sticker;

        /** @brief Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only */
        const std::optional<qint32>& message_thread_id = std::nullopt;

        /** @brief Optional. Emoji associated with the sticker; only for just uploaded stickers */
        const std::optional<QString>& emoji = std::nullopt;

        /** @brief Optional. Sends the message silently */
        const std::optional<bool>& disable_notification = std::nullopt;

        /** @brief Optional. Protects the contents of the sent message from forwarding and saving */
        const std::optional<bool>& protect_content = std::nullopt;

        /** @brief Optional. Additional interface options */
        const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup = std::nullopt;
    };

}}

#endif // TELEGRAM_FUNCTIONARGUMENTS_H