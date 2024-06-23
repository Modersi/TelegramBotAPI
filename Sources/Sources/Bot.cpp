#include "Bot.h"

#include "Internal/Utility/QHttpMultiPartInserter.h"
#include "Internal/Utility/QJsonObjectInserter.h"
#include "Internal/Utility/QVectorInserter.h"
#include "Types/ChatMemberAdministrator.h"
#include "Types/ChatMemberBanned.h"
#include "Types/ChatMemberLeft.h"
#include "Types/ChatMemberMember.h"
#include "Types/ChatMemberOwner.h"
#include "Types/ChatMemberRestricted.h"
#include "Types/User.h"

#include "qfile.h"
#include "qjsondocument.h"
#include "qjsonarray.h"
#include "qjsonobject.h"
#include "qjsonvalue.h"
#include "qurlquery.h"

#define MAKE_LINK_TO_TG_API(bot_token, method)  QStringLiteral("https://api.telegram.org/bot%1/%2").arg(bot_token).arg(method)

Telegram::Bot::Bot(const std::shared_ptr<BotSettings>& bot_settings) :
    QObject(),
    bot_settings(bot_settings),
    telegram_listener() 
{
    /* If webhook URL and SSL configuration specified - create webhook server */
    if (bot_settings->webhook_url.has_value() and bot_settings->ssl_configuration.has_value()) {

        telegram_listener.emplace(this->bot_settings);

        setWebhook(*bot_settings->webhook_url, bot_settings->public_key.value_or(nullptr).get(), bot_settings->webhook_ip_addres, bot_settings->max_connections, bot_settings->allowed_updates, bot_settings->drop_pending_updates);

        QObject::connect(&telegram_listener.value(), &Telegram::Internal::TelegramListener::updateReceived, [this](const Update& update) {
            if      (update.message.has_value())			    emit messageReceived(update.update_id, *update.message);
            else if (update.edited_message.has_value())		    emit messageWasUpdated(update.update_id, *update.edited_message);
            else if (update.channel_post.has_value())			emit channelPostReceived(update.update_id, *update.channel_post);
            else if (update.edited_channel_post.has_value())	emit channelPostWasUpdated(update.update_id, *update.edited_channel_post);
            else if (update.inline_query.has_value())			emit inlineQueryReceived(update.update_id, *update.inline_query);
            else if (update.chosen_inline_result.has_value())	emit chosenInlineResult(update.update_id, *update.chosen_inline_result);
            else if (update.callback_query.has_value())		    emit callbackQueryReceived(update.update_id, *update.callback_query);
            else if (update.poll.has_value())					emit pollReceived(update.update_id, *update.poll);
            else if (update.poll_answer.has_value())			emit pollAnswerReceived(update.update_id, *update.poll_answer);
            else if (update.my_chat_member.has_value())		    emit myChatMemberStatusUpdated(update.update_id, *update.my_chat_member);
            else if (update.chat_member.has_value())			emit chatMemberStatusUpdated(update.update_id, *update.chat_member);
        });

        QObject::connect(&telegram_listener.value(), &Telegram::Internal::TelegramListener::errorOccured,
                         this, &Telegram::Bot::networkErrorOccured);
    }
}

std::future<QVector<Telegram::Update>> Telegram::Bot::getUpdates(const std::optional<qint32>& offset, const std::optional<qint32>& limit, const std::optional<qint32>& timeout, const std::optional<QVector<QString>>& allowed_updates) {
    
    static std::array<QString, 4> keys = {
        "offset",
        "limit",
        "timeout",
        "allowed_updates"
    };

    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        offset,
        limit,
        timeout,
        allowed_updates
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> QVector<Update> {

        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "getUpdates"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return {};
        }
        else return Utility::QVectorInserter<Update>::make(response["result"].toArray());
    });
}

std::future<bool> Telegram::Bot::setWebhook(const QString& url, QFile* certificate, const std::optional<QString>& ip_address, const std::optional<qint32>& max_connections, const std::optional<QVector<QString>>& allowed_updates, const std::optional<bool>& drop_pending_updates) {
    
    static std::array<QString, 6> keys = {
        "url",
        "certificate",
        "ip_address",
        "max_connections",
        "allowed_updates",
        "drop_pending_updates"
    };

    auto&& request_body = Utility::QHttpMultiPartInserter::make(keys,
        url,
        certificate,
        ip_address,
        max_connections,
        allowed_updates,
        drop_pending_updates
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> bool {

        if (auto response = QJsonDocument::fromJson(Utility::Network::post(request_body.get(), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "setWebhook"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return false;
        }
        else return true;
    });
}

std::future<bool> Telegram::Bot::deleteWebhook(const std::optional<bool>& drop_pending_updates) {
    
    static std::array<QString, 1> keys = {
        "drop_pending_updates"
    };

    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        drop_pending_updates
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> bool {

        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "deleteWebhook"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return false;
        }
        else return true;
    });
}

std::future<Telegram::WebhookInfo> Telegram::Bot::getWebhookInfo() {

    return std::async(std::launch::async, [this]() -> WebhookInfo {

        if (auto response = QJsonDocument::fromJson(Utility::Network::get(MAKE_LINK_TO_TG_API(bot_settings->bot_token, "getWebhookInfo"), {})).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return {};
        }
        else return response["result"].toObject();
    });
}

std::future<Telegram::User> Telegram::Bot::getMe() {

    return std::async(std::launch::async, [this]() -> User {

        if (auto response = QJsonDocument::fromJson(Utility::Network::get(MAKE_LINK_TO_TG_API(bot_settings->bot_token, "getMe"), {})).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return {};
        }
        else return response["result"].toObject();
    });
}

std::future<bool> Telegram::Bot::logOut() {

    return std::async(std::launch::async, [this]() -> bool {

        if (auto response = QJsonDocument::fromJson(Utility::Network::get(MAKE_LINK_TO_TG_API(bot_settings->bot_token, "logOut"), {})).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return false;
        }
        else return true;
    });
}

std::future<bool> Telegram::Bot::close() {

    return std::async(std::launch::async, [this]() -> bool {

        if (auto response = QJsonDocument::fromJson(Utility::Network::get(MAKE_LINK_TO_TG_API(bot_settings->bot_token, "close"), {})).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return false;
        }
        else return true;
    });
}

std::future<Telegram::Message> Telegram::Bot::sendMessage(const std::variant<qint64, QString>& chat_id, const QString& text, const std::optional<Message::FormattingType>& parse_mode, const std::optional<QVector<MessageEntity>>& entities, const std::optional<bool>& disable_web_page_preview, const std::optional<bool>& disable_notification, const std::optional<qint32>& reply_to_message_id, const std::optional<bool>& allow_sending_without_reply, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup) { 
    
    static std::array<QString, 9> keys = { 
        "chat_id",
        "text",
        "parse_mode",
        "entities",
        "disable_web_page_preview",
        "disable_notification",
        "reply_to_message_id",
        "allow_sending_without_reply",
        "reply_markup" 
    };

    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        chat_id,
        text,
        parse_mode,
        entities,
        disable_web_page_preview,
        disable_notification,
        reply_to_message_id,
        allow_sending_without_reply,
        reply_markup
    );
    
    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> Message {
    
        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "sendMessage"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return {};
        }
        else return response["result"].toObject();
    });
}

std::future<Telegram::Message> Telegram::Bot::sendMessage(const FunctionArguments::SendMessage& arguments) {
    
    return sendMessage(
        arguments.chat_id,
        arguments.text,
        arguments.parse_mode,
        arguments.entities,
        arguments.disable_web_page_preview,
        arguments.disable_notification,
        arguments.reply_to_message_id,
        arguments.allow_sending_without_reply,
        arguments.reply_markup
    );
}

std::future<Telegram::Message> Telegram::Bot::forwardMessage(const std::variant<qint64, QString>& chat_id, const std::variant<qint64, QString>& from_chat_id, const qint32& message_id, const std::optional<bool>& disable_notification) {
   
    static std::array<QString, 4> keys = {
        "chat_id",
        "from_chat_id",
        "message_id",
        "disable_notification"
    };

    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        chat_id,
        from_chat_id,
        message_id,
        disable_notification
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> Message {

        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "forwardMessage"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return {};
        }
        else return response["result"].toObject();
    });
}

std::future<Telegram::Message> Telegram::Bot::forwardMessage(const FunctionArguments::ForwardMessage& arguments) {

    return forwardMessage(
        arguments.chat_id,
        arguments.from_chat_id,
        arguments.message_id,
        arguments.disable_notification
    );
}

std::future<Telegram::MessageId> Telegram::Bot::copyMessage(const std::variant<qint64, QString>& chat_id, const std::variant<qint64, QString>& from_chat_id, const qint32& message_id, const std::optional<QString>& caption, const std::optional<Message::FormattingType>& parse_mode, const std::optional<QVector<MessageEntity>>& caption_entities, const std::optional<bool>& disable_notification, const std::optional<qint32>& reply_to_message_id, const std::optional<bool>& allow_sending_without_reply, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup) {
    
    static std::array<QString, 10> keys = {
        "chat_id",
        "from_chat_id",
        "message_id",
        "caption",
        "parse_mode",
        "caption_entities",
        "disable_notification",
        "reply_to_message_id",
        "allow_sending_without_reply",
        "reply_markup"
    };

    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        chat_id,
        from_chat_id,
        message_id,
        caption,
        parse_mode,
        caption_entities,
        disable_notification,
        reply_to_message_id,
        allow_sending_without_reply,
        reply_markup
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> MessageId {

        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "copyMessage"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return {};
        }
        else return response["result"].toObject();
    });
}

std::future<Telegram::MessageId> Telegram::Bot::copyMessage(const FunctionArguments::CopyMessage& arguments) {
    
    return copyMessage(
        arguments.chat_id,
        arguments.from_chat_id,
        arguments.message_id,
        arguments.caption,
        arguments.parse_mode,
        arguments.caption_entities,
        arguments.disable_notification,
        arguments.reply_to_message_id,
        arguments.allow_sending_without_reply,
        arguments.reply_markup
    );
}

std::future<Telegram::Message> Telegram::Bot::sendPhoto(const std::variant<qint64, QString>& chat_id, const std::variant<QFile*, QString>& photo, const std::optional<QString>& caption, const std::optional<Message::FormattingType>& parse_mode, const std::optional<QVector<MessageEntity>>& caption_entities, const std::optional<bool>& disable_notification, const std::optional<qint32>& reply_to_message_id, const std::optional<bool>& allow_sending_without_reply, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup) {

    static std::array<QString, 9> keys = {
        "chat_id",
        "photo",
        "caption",
        "parse_mode",
        "caption_entities",
        "disable_notification",
        "reply_to_message_id",
        "allow_sending_without_reply",
        "reply_markup"
    };

    auto&& request_body = Utility::QHttpMultiPartInserter::make(keys,
        chat_id,
        photo,
        caption,
        parse_mode,
        caption_entities,
        disable_notification,
        reply_to_message_id,
        allow_sending_without_reply,
        reply_markup
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> Message {

        if (auto response = QJsonDocument::fromJson(Utility::Network::post(request_body.get(), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "sendPhoto"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return {};
        }
        else return response["result"].toObject();
    });
}

std::future<Telegram::Message> Telegram::Bot::sendPhoto(const FunctionArguments::SendPhoto& arguments) {
    
    return sendPhoto(
        arguments.chat_id,
        arguments.photo,
        arguments.caption,
        arguments.parse_mode,
        arguments.caption_entities,
        arguments.disable_notification,
        arguments.reply_to_message_id,
        arguments.allow_sending_without_reply,
        arguments.reply_markup
    );
}

std::future<Telegram::Message> Telegram::Bot::sendAudio(const std::variant<qint64, QString>& chat_id, const std::variant<QFile*, QString>& audio, const std::optional<QString>& caption, const std::optional<Message::FormattingType>& parse_mode, const std::optional<QVector<MessageEntity>>& caption_entities, const std::optional<qint32>& duration, const std::optional<QString>& performer, const std::optional<QString>& title, const std::optional<std::variant<QFile*, QString>>& thumb, const std::optional<bool>& disable_notification, const std::optional<qint32>& reply_to_message_id, const std::optional<bool>& allow_sending_without_reply, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup) {

    static std::array<QString, 13> keys = {
        "chat_id",
        "audio",
        "caption",
        "parse_mode",
        "caption_entities",
        "duration",
        "performer",
        "title",
        "thumb",
        "disable_notification",
        "reply_to_message_id",
        "allow_sending_without_reply",
        "reply_markup"
    };

    auto&& request_body = Utility::QHttpMultiPartInserter::make(keys,
        chat_id,
        audio,
        caption,
        parse_mode,
        caption_entities,
        duration,
        performer,
        title,
        thumb,
        disable_notification,
        reply_to_message_id,
        allow_sending_without_reply,
        reply_markup
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> Message {

        if (auto response = QJsonDocument::fromJson(Utility::Network::post(request_body.get(), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "sendAudio"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return {};
        }
        else return response["result"].toObject();
    });
}

std::future<Telegram::Message> Telegram::Bot::sendAudio(const FunctionArguments::SendAudio& arguments) {
    
    return sendAudio(
        arguments.chat_id,
        arguments.audio,
        arguments.caption,
        arguments.parse_mode,
        arguments.caption_entities,
        arguments.duration,
        arguments.performer,
        arguments.title,
        arguments.thumbnail,
        arguments.disable_notification,
        arguments.reply_to_message_id,
        arguments.allow_sending_without_reply,
        arguments.reply_markup
    );
}

std::future<Telegram::Message> Telegram::Bot::sendDocument(const std::variant<qint64, QString>& chat_id, const std::variant<QFile*, QString>& document, const std::optional<std::variant<QFile*, QString>>& thumb, const std::optional<QString>& caption, const std::optional<Message::FormattingType>& parse_mode, const std::optional<QVector<MessageEntity>>& caption_entities, const std::optional<bool>& disable_content_type_detection, const std::optional<bool>& disable_notification, const std::optional<qint32>& reply_to_message_id, const std::optional<bool>& allow_sending_without_reply, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup) {
    
    static std::array<QString, 11> keys = { 
        "chat_id", 
        "document", 
        "thumb", 
        "caption", 
        "parse_mode", 
        "caption_entities", 
        "disable_content_type_detection", 
        "disable_notification", 
        "reply_to_message_id", 
        "allow_sending_without_reply", 
        "reply_markup" 
    };

    auto&& request_body = Utility::QHttpMultiPartInserter::make(keys,
        chat_id,
        document,
        thumb,
        caption,
        parse_mode,
        caption_entities,
        disable_content_type_detection,
        disable_notification,
        reply_to_message_id,
        allow_sending_without_reply,
        reply_markup
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> Message {

        if (auto response = QJsonDocument::fromJson(Utility::Network::post(request_body.get(), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "sendDocument"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return {};
        }
        else return response["result"].toObject();
    });
}

std::future<Telegram::Message> Telegram::Bot::sendDocument(const FunctionArguments::SendDocument& arguments) {
    
    return sendDocument(
        arguments.chat_id,
        arguments.document,
        arguments.thumbnail,
        arguments.caption,
        arguments.parse_mode,
        arguments.caption_entities,
        arguments.disable_content_type_detection,
        arguments.disable_notification,
        arguments.reply_to_message_id,
        arguments.allow_sending_without_reply,
        arguments.reply_markup
    );
}

std::future<Telegram::Message> Telegram::Bot::sendVideo(const std::variant<qint64, QString>& chat_id, const std::variant<QFile*, QString>& video, const std::optional<qint32>& duration, const std::optional<qint32>& width, const std::optional<qint32>& height, const std::optional<std::variant<QFile*, QString>>& thumb, const std::optional<QString>& caption, const std::optional<Message::FormattingType>& parse_mode, const std::optional<QVector<MessageEntity>>& caption_entities, const std::optional<bool>& supports_streaming, const std::optional<bool>& disable_notification, const std::optional<qint32>& reply_to_message_id, const std::optional<bool>& allow_sending_without_reply, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup) {

    static std::array<QString, 14> keys = {
        "chat_id",
        "video",
        "duration",
        "width",
        "height",
        "thumb",
        "caption",
        "parse_mode",
        "caption_entities",
        "supports_streaming",
        "disable_notification",
        "reply_to_message_id",
        "allow_sending_without_reply",
        "reply_markup"
    };

    auto&& request_body = Utility::QHttpMultiPartInserter::make(keys,
        chat_id,
        video,
        duration,
        width,
        height,
        thumb,
        caption,
        parse_mode,
        caption_entities,
        supports_streaming,
        disable_notification,
        reply_to_message_id,
        allow_sending_without_reply,
        reply_markup
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> Message {

        if (auto response = QJsonDocument::fromJson(Utility::Network::post(request_body.get(), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "sendVideo"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return {};
        }
        else return response["result"].toObject();
    });
}

std::future<Telegram::Message> Telegram::Bot::sendVideo(const FunctionArguments::SendVideo& arguments) {
    
    return sendVideo(
        arguments.chat_id,
        arguments.video,
        arguments.duration,
        arguments.width,
        arguments.height,
        arguments.thumbnail,
        arguments.caption,
        arguments.parse_mode,
        arguments.caption_entities,
        arguments.supports_streaming,
        arguments.disable_notification,
        arguments.reply_to_message_id,
        arguments.allow_sending_without_reply,
        arguments.reply_markup
    );
}

std::future<Telegram::Message> Telegram::Bot::sendAnimation(const std::variant<qint64, QString>& chat_id, const std::variant<QFile*, QString>& animation, const std::optional<qint32>& duration, const std::optional<qint32>& width, const std::optional<qint32>& height, const std::optional<std::variant<QFile*, QString>>& thumb, const std::optional<QString>& caption, const std::optional<Message::FormattingType>& parse_mode, const std::optional<QVector<MessageEntity>>& caption_entities, const std::optional<bool>& disable_notification, const std::optional<qint32>& reply_to_message_id, const std::optional<bool>& allow_sending_without_reply, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup) {
    
    static std::array<QString, 13> keys = { 
        "chat_id", 
        "animation", 
        "duration", 
        "width", 
        "height", 
        "thumb", 
        "caption", 
        "parse_mode", 
        "caption_entities", 
        "disable_notification", 
        "reply_to_message_id", 
        "allow_sending_without_reply", 
        "reply_markup" 
    };

    auto&& request_body = Utility::QHttpMultiPartInserter::make(keys,
        chat_id,
        animation,
        duration,
        width,
        height,
        thumb,
        caption,
        parse_mode,
        caption_entities,
        disable_notification,
        reply_to_message_id,
        allow_sending_without_reply,
        reply_markup
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> Message {

        if (auto response = QJsonDocument::fromJson(Utility::Network::post(request_body.get(), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "sendAnimation"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return {};
        }
        else return response["result"].toObject();
    });
}

std::future<Telegram::Message> Telegram::Bot::sendAnimation(const FunctionArguments::SendAnimation& arguments) {
    
    return sendAnimation(
        arguments.chat_id,
        arguments.animation,
        arguments.duration,
        arguments.width,
        arguments.height,
        arguments.thumbnail,
        arguments.caption,
        arguments.parse_mode,
        arguments.caption_entities,
        arguments.disable_notification,
        arguments.reply_to_message_id,
        arguments.allow_sending_without_reply,
        arguments.reply_markup
    );
}

std::future<Telegram::Message> Telegram::Bot::sendVoice(const std::variant<qint64, QString>& chat_id, const std::variant<QFile*, QString>& voice, const std::optional<QString>& caption, const std::optional<Message::FormattingType>& parse_mode, const std::optional<QVector<MessageEntity>>& caption_entities, const std::optional<qint32>& duration, const std::optional<bool>& disable_notification, const std::optional<qint32>& reply_to_message_id, const std::optional<bool>& allow_sending_without_reply, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup) {

    static std::array<QString, 10> keys = { 
        "chat_id",
        "voice",
        "caption",
        "parse_mode",
        "caption_entities",
        "duration",
        "disable_notification",
        "reply_to_message_id",
        "allow_sending_without_reply",
        "reply_markup"
    };

    auto&& request_body = Utility::QHttpMultiPartInserter::make(keys,
        chat_id,
        voice,
        caption,
        parse_mode,
        caption_entities,
        duration,
        disable_notification,
        reply_to_message_id,
        allow_sending_without_reply,
        reply_markup
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> Message {

        if (auto response = QJsonDocument::fromJson(Utility::Network::post(request_body.get(), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "sendVoice"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return {};
        }
        else return response["result"].toObject();
    });
}

std::future<Telegram::Message> Telegram::Bot::sendVoice(const FunctionArguments::SendVoice& arguments) {

    return sendVoice(
        arguments.chat_id,
        arguments.voice,
        arguments.caption,
        arguments.parse_mode,
        arguments.caption_entities,
        arguments.duration,
        arguments.disable_notification,
        arguments.reply_to_message_id,
        arguments.allow_sending_without_reply,
        arguments.reply_markup
    );
}

std::future<Telegram::Message> Telegram::Bot::sendVideoNote(const std::variant<qint64, QString>& chat_id, const std::variant<QFile*, QString>& video_note, const std::optional<qint32>& duration, const std::optional<qint32>& length, const std::optional<std::variant<QFile*, QString>>& thumb, const std::optional<bool>& disable_notification, const std::optional<qint32>& reply_to_message_id, const std::optional<bool>& allow_sending_without_reply, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup) {
    
    static std::array<QString, 9> keys = { 
        "chat_id",
        "video_note",
        "duration",
        "length",
        "thumb",
        "disable_notification",
        "reply_to_message_id",
        "allow_sending_without_reply",
        "reply_markup"
    };

    auto&& request_body = Utility::QHttpMultiPartInserter::make(keys,
        chat_id,
        video_note,
        duration,
        length,
        thumb,
        disable_notification,
        reply_to_message_id,
        allow_sending_without_reply,
        reply_markup
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> Message {

        if (auto response = QJsonDocument::fromJson(Utility::Network::post(request_body.get(), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "sendVideoNote"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return {};
        }
        else return response["result"].toObject();
    });
}

std::future<Telegram::Message> Telegram::Bot::sendVideoNote(const FunctionArguments::SendVideoNote& arguments) {
    
    return sendVideoNote(
        arguments.chat_id,
        arguments.video_note,
        arguments.duration,
        arguments.length,
        arguments.thumbnail,
        arguments.disable_notification,
        arguments.reply_to_message_id,
        arguments.allow_sending_without_reply,
        arguments.reply_markup
    );
}

std::future<QVector<Telegram::Message>> Telegram::Bot::sendMediaGroup(const std::variant<qint64, QString>& chat_id, const QVector<InputMediaAudio>& media, const std::optional<bool>& disable_notification, const std::optional<qint32>& reply_to_message_id, const std::optional<bool>& allow_sending_without_reply) {

    static std::array<QString, 5> keys = {
        "chat_id",
        "media",
        "disable_notification",
        "reply_to_message_id",
        "allow_sending_without_reply"
    };

    auto&& request_body = Utility::QHttpMultiPartInserter::make(keys,
        chat_id,
        media,
        disable_notification,
        reply_to_message_id,
        allow_sending_without_reply
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> QVector<Message> {

        if (auto response = QJsonDocument::fromJson(Utility::Network::post(request_body.get(), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "sendMediaGroup"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return {};
        }
        else return Utility::QVectorInserter<Message>::make(response["result"].toArray());
    });
}

std::future<QVector<Telegram::Message>> Telegram::Bot::sendMediaGroup(const FunctionArguments::SendMediaGroup_Audio& arguments) {
    
    return sendMediaGroup(
        arguments.chat_id,
        arguments.media,
        arguments.disable_notification,
        arguments.reply_to_message_id,
        arguments.allow_sending_without_reply
    );
}

std::future<QVector<Telegram::Message>> Telegram::Bot::sendMediaGroup(const std::variant<qint64, QString>& chat_id, const QVector<InputMediaDocument>& media, const std::optional<bool>& disable_notification, const std::optional<qint32>& reply_to_message_id, const std::optional<bool>& allow_sending_without_reply) {

    static std::array<QString, 5> keys = {
        "chat_id",
        "media",
        "disable_notification",
        "reply_to_message_id",
        "allow_sending_without_reply"
    };

    auto&& request_body = Utility::QHttpMultiPartInserter::make(keys,
        chat_id,
        media,
        disable_notification,
        reply_to_message_id,
        allow_sending_without_reply
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> QVector<Message> {

        if (auto response = QJsonDocument::fromJson(Utility::Network::post(request_body.get(), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "sendMediaGroup"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return {};
        }
        else return Utility::QVectorInserter<Message>::make(response["result"].toArray());
    });
}

std::future<QVector<Telegram::Message>> Telegram::Bot::sendMediaGroup(const FunctionArguments::SendMediaGroup_Document& arguments) {
    
    return sendMediaGroup(
        arguments.chat_id,
        arguments.media,
        arguments.disable_notification,
        arguments.reply_to_message_id,
        arguments.allow_sending_without_reply
    );
}

std::future<QVector<Telegram::Message>> Telegram::Bot::sendMediaGroup(const std::variant<qint64, QString>& chat_id, const QVector<InputMediaPhoto>& photos, const QVector<InputMediaVideo>& videos, const std::optional<bool>& disable_notification, const std::optional<qint32>& reply_to_message_id, const std::optional<bool>& allow_sending_without_reply) {

    static std::array<QString, 6> keys = {
        "chat_id",
        "media",
        "media",
        "disable_notification",
        "reply_to_message_id",
        "allow_sending_without_reply"
    };

    auto&& request_body = Utility::QHttpMultiPartInserter::make(keys,
        chat_id,
        photos,
        videos,
        disable_notification,
        reply_to_message_id,
        allow_sending_without_reply
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> QVector<Message> {

        if (auto response = QJsonDocument::fromJson(Utility::Network::post(request_body.get(), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "sendMediaGroup"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return {};
        }
        else return Utility::QVectorInserter<Message>::make(response["result"].toArray());
    });
}

std::future<QVector<Telegram::Message>> Telegram::Bot::sendMediaGroup(const FunctionArguments::SendMediaGroup_PhotoVideo& arguments) {
    
    return sendMediaGroup(
        arguments.chat_id,
        arguments.photos,
        arguments.videos,
        arguments.disable_notification,
        arguments.reply_to_message_id,
        arguments.allow_sending_without_reply
    );
}

std::future<Telegram::Message> Telegram::Bot::sendLocation(const std::variant<qint64, QString>& chat_id, const float& latitude, const float& longitude, const std::optional<float>& horizontal_accuracy, const std::optional<qint32>& live_period, const std::optional<qint32>& heading, const std::optional<qint32>& proximity_alert_radius, const std::optional<bool>& disable_notification, const std::optional<qint32>& reply_to_message_id, const std::optional<bool>& allow_sending_without_reply, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup) {
    
    static std::array<QString, 11> keys = {
        "chat_id",
        "latitude",
        "longitude",
        "horizontal_accuracy",
        "live_period",
        "heading",
        "proximity_alert_radius",
        "disable_notification",
        "reply_to_message_id",
        "allow_sending_without_reply",
        "reply_markup"
    };

    auto&& request_body = Utility::QHttpMultiPartInserter::make(keys,
        chat_id,
        latitude,
        longitude,
        horizontal_accuracy,
        live_period,
        heading,
        proximity_alert_radius,
        disable_notification,
        reply_to_message_id,
        allow_sending_without_reply,
        reply_markup
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> Message {

        if (auto response = QJsonDocument::fromJson(Utility::Network::post(request_body.get(), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "sendLocation"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return {};
        }
        else return response["result"].toObject();
    });
}

std::future<Telegram::Message> Telegram::Bot::sendLocation(const FunctionArguments::SendLocation& arguments) {
    
    return sendLocation(
        arguments.chat_id,
        arguments.latitude,
        arguments.longitude,
        arguments.horizontal_accuracy,
        arguments.live_period,
        arguments.heading,
        arguments.proximity_alert_radius,
        arguments.disable_notification,
        arguments.reply_to_message_id,
        arguments.allow_sending_without_reply,
        arguments.reply_markup
    );
}

std::future<Telegram::Message> Telegram::Bot::editMessageLiveLocation(const float& latitude, const float& longitude, const std::optional<std::variant<qint64, QString>>& chat_id, const std::optional<qint32>& message_id, const std::optional<QString>& inline_message_id, const std::optional<float>& horizontal_accuracy, const std::optional<qint32>& heading, const std::optional<qint32>& proximity_alert_radius, const std::optional<InlineKeyboardMarkup>& reply_markup) {

    static std::array<QString, 9> keys = {
        "latitude",
        "longitude",
        "chat_id",
        "message_id",
        "inline_message_id",
        "horizontal_accuracy",
        "heading",
        "proximity_alert_radius",
        "reply_markup",
    };

    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        latitude,
        longitude,
        chat_id,
        message_id,
        inline_message_id,
        horizontal_accuracy,
        heading,
        proximity_alert_radius,
        reply_markup
    );

    return std::async(std::launch::async, [this, latitude, longitude, request_body = std::move(request_body)]() -> Message {

        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "editMessageLiveLocation"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return {};
        }
        else return response["result"].toObject();
    });
}

std::future<Telegram::Message> Telegram::Bot::editMessageLiveLocation(const FunctionArguments::EditMessageLiveLocation& arguments) {

    return editMessageLiveLocation(
        arguments.latitude,
        arguments.longitude,
        arguments.chat_id,
        arguments.message_id,
        arguments.inline_message_id,
        arguments.horizontal_accuracy,
        arguments.heading,
        arguments.proximity_alert_radius,
        arguments.reply_markup
    );
}

std::future<Telegram::Message> Telegram::Bot::stopMessageLiveLocation(const std::optional<std::variant<qint64, QString>>& chat_id, const std::optional<qint32>& message_id, const std::optional<QString>& inline_message_id, const std::optional<InlineKeyboardMarkup>& reply_markup) {

    static std::array<QString, 4> keys = {
        "chat_id",
        "message_id",
        "inline_message_id",
        "reply_markup"
    };
    
    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        chat_id,
        message_id,
        inline_message_id,
        reply_markup
    );
    
    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> Message {
    
        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "stopMessageLiveLocation"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return {};
        }
        else return response["result"].toObject();
    });
}

std::future<Telegram::Message> Telegram::Bot::stopMessageLiveLocation(const FunctionArguments::StopMessageLiveLocation& arguments) {
    
    return stopMessageLiveLocation(
        arguments.chat_id,
        arguments.message_id,
        arguments.inline_message_id,
        arguments.reply_markup
    );
}

std::future<Telegram::Message> Telegram::Bot::sendVenue(const std::variant<qint64, QString>& chat_id, const float& latitude, const float& longitude, const QString& title, const QString& address, const std::optional<QString>& foursquare_id, const std::optional<QString>& foursquare_type, const std::optional<QString>& google_place_id, const std::optional<QString>& google_place_type, const std::optional<bool>& disable_notification, const std::optional<qint32>& reply_to_message_id, const std::optional<bool>& allow_sending_without_reply, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup) {

    static std::array<QString, 13> keys = {
        "chat_id",
        "latitude",
        "longitude",
        "title",
        "address",
        "foursquare_id",
        "foursquare_type",
        "google_place_id",
        "google_place_type",
        "disable_notification",
        "reply_to_message_id",
        "allow_sending_without_reply",
        "reply_markup"
    };

    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        chat_id,
        latitude,
        longitude,
        title,
        address,
        foursquare_id,
        foursquare_type,
        google_place_id,
        google_place_type,
        disable_notification,
        reply_to_message_id,
        allow_sending_without_reply,
        reply_markup
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> Message {

        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "sendVenue"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return {};
        }
        else return response["result"].toObject();
    });
}

std::future<Telegram::Message> Telegram::Bot::sendVenue(const FunctionArguments::SendVenue& arguments) {
    
    return sendVenue(
        arguments.chat_id,
        arguments.latitude,
        arguments.longitude,
        arguments.title,
        arguments.address,
        arguments.foursquare_id,
        arguments.foursquare_type,
        arguments.google_place_id,
        arguments.google_place_type,
        arguments.disable_notification,
        arguments.reply_to_message_id,
        arguments.allow_sending_without_reply,
        arguments.reply_markup
    );
}

std::future<Telegram::Message> Telegram::Bot::sendContact(const std::variant<qint64, QString>& chat_id, const QString& phone_number, const QString& first_name, const std::optional<QString>& last_name, const std::optional<QString>& vcard, const std::optional<bool>& disable_notification, const std::optional<qint32>& reply_to_message_id, const std::optional<bool>& allow_sending_without_reply, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup) {

    static std::array<QString, 9> keys = {
        "chat_id",
        "phone_number",
        "first_name",
        "last_name",
        "vcard",
        "disable_notification",
        "reply_to_message_id",
        "allow_sending_without_reply",
        "reply_markup"
    };
    
    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        chat_id,
        phone_number,
        first_name,
        last_name,
        vcard,
        disable_notification,
        reply_to_message_id,
        allow_sending_without_reply,
        reply_markup
    );
    
    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> Message {
    
        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "sendContact"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return {};
        }
        else return response["result"].toObject();
    });
}

std::future<Telegram::Message> Telegram::Bot::sendContact(const FunctionArguments::SendContact& arguments) {
    
    return sendContact(
        arguments.chat_id,
        arguments.phone_number,
        arguments.first_name,
        arguments.last_name,
        arguments.vcard,
        arguments.disable_notification,
        arguments.reply_to_message_id,
        arguments.allow_sending_without_reply,
        arguments.reply_markup
    );
}

std::future<Telegram::Message> Telegram::Bot::sendPoll(const std::variant<qint64, QString>& chat_id, const QString& question, const QVector<QString>& options, const std::optional<bool>& is_anonymous, const std::optional<QString>& type, const std::optional<bool>& allows_multiple_answers, const std::optional<qint32>& correct_option_id, const std::optional<QString>& explanation, const std::optional<Message::FormattingType>& explanation_parse_mode, const std::optional<QVector<MessageEntity>>& explanation_entities, const std::optional<qint32>& open_period, const std::optional<qint32>& close_date, const std::optional<bool>& is_closed, const std::optional<bool>& disable_notification, const std::optional<qint32>& reply_to_message_id, const std::optional<bool>& allow_sending_without_reply, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup) {

    static std::array<QString, 17> keys = {
        "chat_id",
        "question",
        "options",
        "is_anonymous",
        "type",
        "allows_multiple_answers",
        "correct_option_id",
        "explanation",
        "explanation_parse_mode",
        "explanation_entities",
        "open_period",
        "close_date",
        "is_closed",
        "disable_notification",
        "reply_to_message_id",
        "allow_sending_without_reply",
        "reply_markup"
    };

    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        chat_id,
        question,
        options,
        is_anonymous,
        type,
        allows_multiple_answers,
        correct_option_id,
        explanation,
        explanation_parse_mode,
        explanation_entities,
        open_period,
        close_date,
        is_closed,
        disable_notification,
        reply_to_message_id,
        allow_sending_without_reply,
        reply_markup
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> Message {

        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "sendPoll"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return {};
        }
        else return response["result"].toObject();
    });
}

std::future<Telegram::Message> Telegram::Bot::sendPoll(const FunctionArguments::SendPoll& arguments) {
    
    return sendPoll(
        arguments.chat_id,
        arguments.question,
        arguments.options,
        arguments.is_anonymous,
        arguments.type,
        arguments.allows_multiple_answers,
        arguments.correct_option_id,
        arguments.explanation,
        arguments.explanation_parse_mode,
        arguments.explanation_entities,
        arguments.open_period,
        arguments.close_date,
        arguments.is_closed,
        arguments.disable_notification,
        arguments.reply_to_message_id,
        arguments.allow_sending_without_reply,
        arguments.reply_markup
    );
}

std::future<Telegram::Message> Telegram::Bot::sendDice(const std::variant<qint64, QString>& chat_id, const std::optional<QString>& emoji, const std::optional<bool>& disable_notification, const std::optional<qint32>& reply_to_message_id, const std::optional<bool>& allow_sending_without_reply, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup) {
    
    static std::array<QString, 6> keys = { 
        "chat_id", 
        "emoji", 
        "disable_notification", 
        "reply_to_message_id", 
        "allow_sending_without_reply", 
        "reply_markup" 
    };

    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        chat_id,
        emoji,
        disable_notification,
        reply_to_message_id,
        allow_sending_without_reply,
        reply_markup
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> Message {

        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "sendDice"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return {};
        }
        else return response["result"].toObject();
    });
}

std::future<Telegram::Message> Telegram::Bot::sendDice(const FunctionArguments::SendDice& arguments) {

    return sendDice(
        arguments.chat_id,
        arguments.emoji,
        arguments.disable_notification,
        arguments.reply_to_message_id,
        arguments.allow_sending_without_reply,
        arguments.reply_markup
    );
}

std::future<bool> Telegram::Bot::sendChatAction(const std::variant<qint64, QString>& chat_id, ChatActionType action) {

    static std::array<QString, 2> keys = { 
        "chat_id",
        "action"
    };

    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        chat_id,
        action
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> bool {

        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "sendChatAction"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return false;
        }
        else return true;
    });
}

std::future<Telegram::UserProfilePhotos> Telegram::Bot::getUserProfilePhotos(const qint64& user_id, const std::optional<qint32>& offset, const std::optional<qint32>& limit) {

    static std::array<QString, 3> keys = {
        "user_id",
        "offset",
        "limit"
    };
    
    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        user_id,
        offset,
        limit
    );
    
    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> UserProfilePhotos {
    
        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "getUserProfilePhotos"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return {};
        }
        else return response["result"].toObject();
    });
}

std::future<Telegram::File> Telegram::Bot::getFile(const QString& file_id) {

    auto&& request_body = QJsonObject({ {"file_id", file_id} });
    
    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> File {
    
        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "getFile"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return {};
        }
        else return response["result"].toObject();
    });
}

std::future<bool> Telegram::Bot::banChatMember(const std::variant<qint64, QString>& chat_id, const qint64& user_id, const std::optional<qint32>& until_date, const std::optional<bool>& revoke_messages) {

    static std::array<QString, 4> keys = {
        "chat_id",
        "user_id",
        "until_date",
        "revoke_messages"
    };

    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        chat_id,
        user_id,
        until_date,
        revoke_messages
    );
    
    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> bool {
    
        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "banChatMember"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return false;
        }
        else return true;
    });
}

std::future<bool> Telegram::Bot::unbanChatMember(const std::variant<qint64, QString>& chat_id, const qint64& user_id, const std::optional<bool>& only_if_banned) {

    static std::array<QString, 3> keys = {
        "chat_id",
        "user_id",
        "only_if_banned"
    };

    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        chat_id,
        user_id,
        only_if_banned
    );
    
    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> bool {
    
        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "unbanChatMember"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return false;
        }
        else return true;
    });
}

std::future<bool> Telegram::Bot::restrictChatMember(const std::variant<qint64, QString>& chat_id, const qint64& user_id, const ChatPermissions& permissions, const std::optional<qint32>& until_date) {

    static std::array<QString, 4> keys = {
        "chat_id",
        "user_id",
        "permissions",
        "until_date"
    };

    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        chat_id,
        user_id,
        permissions,
        until_date
    );
    
    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> bool {
    
        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "restrictChatMember"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return false;
        }
        else return true;
    });
}

std::future<bool> Telegram::Bot::promoteChatMember(const std::variant<qint64, QString>& chat_id, const qint64& user_id, const std::optional<bool>& is_anonymous, const std::optional<bool>& can_manage_chat, const std::optional<bool>& can_post_messages, const std::optional<bool>& can_edit_messages, const std::optional<bool>& can_delete_messages, const std::optional<bool>& can_manage_voice_chats, const std::optional<bool>& can_restrict_members, const std::optional<bool>& can_promote_members, const std::optional<bool>& can_change_info, const std::optional<bool>& can_invite_users, const std::optional<bool>& can_pin_messages) {

    static std::array<QString, 13> keys = {
        "chat_id",
        "user_id",
        "is_anonymous",
        "can_manage_chat",
        "can_post_messages",
        "can_edit_messages",
        "can_delete_messages",
        "can_manage_voice_chats",
        "can_restrict_members",
        "can_promote_members",
        "can_change_info",
        "can_invite_users",
        "can_pin_messages"
    };

    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        chat_id,
        user_id,
        is_anonymous,
        can_manage_chat,
        can_post_messages,
        can_edit_messages,
        can_delete_messages,
        can_manage_voice_chats,
        can_restrict_members,
        can_promote_members,
        can_change_info,
        can_invite_users,
        can_pin_messages
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> bool {
    
        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "promoteChatMember"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return false;
        }
        else return true;
    });
}

std::future<bool> Telegram::Bot::promoteChatMember(const FunctionArguments::PromoteChatMember& arguments) {

    return promoteChatMember(
        arguments.chat_id,
        arguments.user_id,
        arguments.is_anonymous,
        arguments.can_manage_chat,
        arguments.can_post_messages,
        arguments.can_edit_messages,
        arguments.can_delete_messages,
        arguments.can_manage_video_chats,
        arguments.can_restrict_members,
        arguments.can_promote_members,
        arguments.can_change_info,
        arguments.can_invite_users,
        arguments.can_pin_messages
    );
}

std::future<bool> Telegram::Bot::setChatAdministratorCustomTitle(const std::variant<qint64, QString>& chat_id, const qint64& user_id, const QString& custom_title) {

    static std::array<QString, 3> keys = {
        "chat_id",
        "user_id",
        "custom_title"
    };

    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        chat_id,
        user_id,
        custom_title
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> bool {
    
        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "setChatAdministratorCustomTitle"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return false;
        }
        else return true;
    });
}

std::future<bool> Telegram::Bot::setChatPermissions(const std::variant<qint64, QString>& chat_id, const ChatPermissions& permissions) {
    
    static std::array<QString, 2> keys = {
        "chat_id",
        "permissions"
    };

    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        chat_id,
        permissions
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> bool {
    
        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "setChatPermissions"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return false;
        }
        else return true;
    });
}

std::future<QString> Telegram::Bot::exportChatInviteLink(const std::variant<qint64, QString>& chat_id) {

    static std::array<QString, 1> keys = {
        "chat_id"
    };

    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        chat_id
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> QString {
    
        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "setChatPermissions"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return {};
        }
        else return response["result"].toString();
    });
}

std::future<Telegram::ChatInviteLink> Telegram::Bot::createChatInviteLink(const std::variant<qint64, QString>& chat_id, const std::optional<QString>& name, const std::optional<qint32>& expire_date, const std::optional<qint32>& member_limit, const std::optional<bool>& creates_join_request) {

    static std::array<QString, 5> keys = {
        "chat_id",
        "name",
        "expire_date",
        "member_limit",
        "creates_join_request"
    };

    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        chat_id,
        name,
        expire_date,
        member_limit,
        creates_join_request
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> ChatInviteLink {

        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "createChatInviteLink"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return {};
        }
        else return response["result"].toObject();
    });
}

std::future<Telegram::ChatInviteLink> Telegram::Bot::createChatInviteLink(const FunctionArguments::CreateChatInviteLink& arguments) {

    return createChatInviteLink(
        arguments.chat_id,
        arguments.name,
        arguments.expire_date,
        arguments.member_limit,
        arguments.creates_join_request
    );
}

std::future<Telegram::ChatInviteLink> Telegram::Bot::editChatInviteLink(const std::variant<qint64, QString>& chat_id, const QString& invite_link, const std::optional<QString>& name, const std::optional<qint32>& expire_date, const std::optional<qint32>& member_limit, const std::optional<bool>& creates_join_request) {

    static std::array<QString, 6> keys = {
        "chat_id",
        "invite_link",
        "name",
        "expire_date",
        "member_limit",
        "creates_join_request"
    };
    
    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        chat_id,
        invite_link,
        name,
        expire_date,
        member_limit,
        creates_join_request
    );
    
    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> ChatInviteLink {
    
        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "editChatInviteLink"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return {};
        }
        else return response["result"].toObject();
    });
}

std::future<Telegram::ChatInviteLink> Telegram::Bot::editChatInviteLink(const FunctionArguments::EditChatInviteLink& arguments) {
    
    return editChatInviteLink(
        arguments.chat_id,
        arguments.invite_link,
        arguments.name,
        arguments.expire_date,
        arguments.member_limit,
        arguments.creates_join_request
    );
}

std::future<Telegram::ChatInviteLink> Telegram::Bot::revokeChatInviteLink(const std::variant<qint64, QString>& chat_id, const QString& invite_link) {

    static std::array<QString, 2> keys = {
        "chat_id",
        "invite_link"
    };

    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        chat_id,
        invite_link
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> ChatInviteLink {

        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "revokeChatInviteLink"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return {};
        }
        else return response["result"].toObject();
    });
}

std::future<bool> Telegram::Bot::approveChatJoinRequest(const std::variant<qint64, QString>& chat_id, const qint32& user_id) {

    static std::array<QString, 2> keys = {
        "chat_id",
        "user_id"
    };
    
    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        chat_id,
        user_id
    );
    
    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> bool {
    
        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "approveChatJoinRequest"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return false;
        }
        else return true;
    });
}

std::future<bool> Telegram::Bot::declineChatJoinRequest(const std::variant<qint64, QString>& chat_id, const qint32& user_id) {

    static std::array<QString, 2> keys = {
        "chat_id",
        "user_id"
    };

    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        chat_id,
        user_id
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> bool {

        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "declineChatJoinRequest"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return false;
        }
        else return true;
    });
}

std::future<bool> Telegram::Bot::setChatPhoto(const std::variant<qint64, QString>& chat_id, QFile* photo) {

    static std::array<QString, 2> keys = {
        "chat_id",
        "photo"
    };
    
    auto&& request_body = Utility::QHttpMultiPartInserter::make(keys,
        chat_id,
        photo
    );
    
    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> bool {
    
        if (auto response = QJsonDocument::fromJson(Utility::Network::post(request_body.get(), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "setChatPhoto"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return false;
        }
        else return true;
    });
}

std::future<bool> Telegram::Bot::deleteChatPhoto(const std::variant<qint64, QString>& chat_id) {

    static std::array<QString, 1> keys = {
        "chat_id"
    };
    
    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        chat_id
    );
    
    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> bool {
    
        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "deleteChatPhoto"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return false;
        }
        else return true;
    });
}

std::future<bool> Telegram::Bot::setChatTitle(const std::variant<qint64, QString>& chat_id, const QString& title) {

    static std::array<QString, 2> keys = {
        "chat_id",
        "title"
    };

    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        chat_id,
        title
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> bool {

        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "setChatTitle"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return false;
        }
        else return true;
    });
}

std::future<bool> Telegram::Bot::setChatDescription(const std::variant<qint64, QString>& chat_id, const std::optional<QString>& description) {

    static std::array<QString, 2> keys = {
        "chat_id",
        "description"
    };

    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        chat_id,
        description
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> bool {

        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "setChatDescription"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return false;
        }
        else return true;
    });
}

std::future<bool> Telegram::Bot::pinChatMessage(const std::variant<qint64, QString>& chat_id, const qint32& message_id, const std::optional<bool>& disable_notification) {

    static std::array<QString, 3> keys = {
        "chat_id",
        "message_id",
        "disable_notification"
    };

    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        chat_id,
        message_id,
        disable_notification
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> bool {

        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "pinChatMessage"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return false;
        }
        else return true;
    });
}

std::future<bool> Telegram::Bot::unpinChatMessage(const std::variant<qint64, QString>& chat_id, const std::optional<qint32>& message_id) {

    static std::array<QString, 2> keys = {
        "chat_id",
        "message_id"
    };
    
    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        chat_id,
        message_id
    );
    
    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> bool {
    
        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "unpinChatMessage"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return false;
        }
        else return true;
    });
}

std::future<bool> Telegram::Bot::unpinAllChatMessages(const std::variant<qint64, QString>& chat_id) {

    static std::array<QString, 1> keys = {
        "chat_id"
    };
    
    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        chat_id
    );
    
    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> bool {
    
        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "unpinAllChatMessages"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return false;
        }
        else return true;
    });
}

std::future<bool> Telegram::Bot::leaveChat(const std::variant<qint64, QString>& chat_id) {

    static std::array<QString, 1> keys = {
        "chat_id"
    };

    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        chat_id
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> bool {

        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "leaveChat"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return false;
        }
        else return true;
    });
}

std::future<Telegram::Chat> Telegram::Bot::getChat(const std::variant<qint64, QString>& chat_id) {

    static std::array<QString, 1> keys = {
        "chat_id"
    };

    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        chat_id
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> Chat {

        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "getChat"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return {};
        }
        else return response["result"].toObject();
    });
}

std::future<QVector<std::shared_ptr<Telegram::ChatMember>>> Telegram::Bot::getChatAdministrators(const std::variant<qint64, QString>& chat_id) {

    static std::array<QString, 1> keys = {
        "chat_id"
    };

    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        chat_id
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> QVector<std::shared_ptr<Telegram::ChatMember>> {

        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "getChatAdministrators"))).object();
            response["ok"].toBool() == true)
        {
            QVector<std::shared_ptr<ChatMember>> result;

            for (auto&& member : response["result"].toArray()) {

                auto&& status = member.toObject()["status"];
                if (status == "administrator")   result.push_back(std::make_shared<ChatMemberAdministrator>(member.toObject()));
                else if (status == "creator")	 result.push_back(std::make_shared<ChatMemberOwner>(member.toObject()));
                else if (status == "kicked")	 result.push_back(std::make_shared<ChatMemberBanned>(member.toObject()));
                else if (status == "left")	     result.push_back(std::make_shared<ChatMemberLeft>(member.toObject()));
                else if (status == "member")	 result.push_back(std::make_shared<ChatMemberMember>(member.toObject()));
                else if (status == "restricted") result.push_back(std::make_shared<ChatMemberRestricted>(member.toObject()));
            }

            return result;
        }
        else {
            emit errorOccured(response);
            return {};
        }
    });
}

std::future<qint32> Telegram::Bot::getChatMemberCount(const std::variant<qint64, QString>& chat_id) {

    static std::array<QString, 1> keys = {
        "chat_id"
    };

    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        chat_id
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> qint32 {

        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "getChatMemberCount"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return -1;
        }
        else return response["result"].toInt();
    });
}

std::future<std::shared_ptr<Telegram::ChatMember>> Telegram::Bot::getChatMember(const std::variant<qint64, QString>& chat_id, const qint64& user_id) {
    
    static std::array<QString, 2> keys = {
        "chat_id",
        "user_id"
    };

    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        chat_id,
        user_id
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> std::shared_ptr<Telegram::ChatMember> {

        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "getChatMember"))).object();
            response["ok"].toBool() == true)
        {
            auto&& status = response["result"].toObject()["status"];

            if (status == "administrator")   return std::make_shared<ChatMemberAdministrator>(response["result"].toObject());
            else if (status == "creator")	 return std::make_shared<ChatMemberOwner>(response["result"].toObject());
            else if (status == "kicked")	 return std::make_shared<ChatMemberBanned>(response["result"].toObject());
            else if (status == "left")	     return std::make_shared<ChatMemberLeft>(response["result"].toObject());
            else if (status == "member")	 return std::make_shared<ChatMemberMember>(response["result"].toObject());
            else if (status == "restricted") return std::make_shared<ChatMemberRestricted>(response["result"].toObject());
            else return {};

        }
        else {
            emit errorOccured(response);
            return {};
        }
    });
}

std::future<bool> Telegram::Bot::setChatStickerSet(const std::variant<qint64, QString>& chat_id, const QString& sticker_set_name) {

    static std::array<QString, 2> keys = {
        "chat_id",
        "sticker_set_name"
    };
    
    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        chat_id,
        sticker_set_name
    );
    
    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> bool {
    
        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "setChatStickerSet"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return false;
        }
        else return true;
    });
}

std::future<bool> Telegram::Bot::deleteChatStickerSet(const std::variant<qint64, QString>& chat_id) {

    static std::array<QString, 1> keys = {
        "chat_id"
    };
    
    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        chat_id
    );
    
    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> bool {
    
        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "deleteChatStickerSet"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return false;
        }
        else return true;
    });
}

std::future<bool> Telegram::Bot::answerCallbackQuery(const QString& callback_query_id, const std::optional<QString>& text, const std::optional<bool>& show_alert, const std::optional<QString>& url, const std::optional<qint32>& cache_time) {

    static std::array<QString, 5> keys = {
        "callback_query_id",
        "text",
        "show_alert",
        "url",
        "cache_time"
    };
    
    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        callback_query_id,
        text,
        show_alert,
        url,
        cache_time
    );
    
    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> bool {
    
        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "answerCallbackQuery"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return false;
        }
        else return true;
    });
}

std::future<bool> Telegram::Bot::answerCallbackQuery(const FunctionArguments::AnswerCallbackQuery& arguments) {

    return answerCallbackQuery(
        arguments.callback_query_id,
        arguments.text,
        arguments.show_alert,
        arguments.url,
        arguments.cache_time
    );
}

std::future<bool> Telegram::Bot::setMyCommands(const QVector<BotCommand>& commands, const std::optional<BotCommandScope*>& scope, const std::optional<QString>& language_code) {

    static std::array<QString, 3> keys = {
        "commands",
        "scope",
        "language_code"
    };
    
    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        commands,
        scope,
        language_code
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> bool {
    
        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "setMyCommands"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return false;
        }
        else return true;
    });
}

std::future<bool> Telegram::Bot::deleteMyCommands(const std::optional<BotCommandScope*>& scope, const std::optional<QString>& language_code) {

    static std::array<QString, 2> keys = {
        "scope",
        "language_code"
    };

    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        scope,
        language_code
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> bool {

        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "deleteMyCommands"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return false;
        }
        else return true;
    });
}

std::future<QVector<Telegram::BotCommand>> Telegram::Bot::getMyCommands(const std::optional<BotCommandScope*>& scope, const std::optional<QString>& language_code) {

    static std::array<QString, 2> keys = {
        "scope",
        "language_code"
    };

    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        scope,
        language_code
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> QVector<BotCommand> {

        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "getMyCommands"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return {};
        }
        else return Utility::QVectorInserter<Telegram::BotCommand>::make(response["result"].toArray());
    });
}

std::future<bool> Telegram::Bot::editMessageText(const QString& text, const std::optional<std::variant<qint64, QString>>& chat_id, const std::optional<qint32>& message_id, const std::optional<QString>& inline_message_id, const std::optional<Message::FormattingType>& parse_mode, const std::optional<QVector<MessageEntity>>& entities, const std::optional<bool>& disable_web_page_preview, const std::optional<InlineKeyboardMarkup>& reply_markup) {

    static std::array<QString, 8> keys = {
        "text",
        "chat_id",
        "message_id",
        "inline_message_id",
        "parse_mode",
        "entities",
        "disable_web_page_preview",
        "reply_markup"
    };

    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        text,
        chat_id,
        message_id,
        inline_message_id,
        parse_mode,
        entities,
        disable_web_page_preview,
        reply_markup
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> bool {

        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "editMessageText"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return false;
        }
        else return true;
    });
}

std::future<bool> Telegram::Bot::editMessageText(const FunctionArguments::EditMessageText& arguments) {
    
    return editMessageText(
        arguments.text,
        arguments.chat_id,
        arguments.message_id,
        arguments.inline_message_id,
        arguments.parse_mode,
        arguments.entities,
        arguments.disable_web_page_preview,
        arguments.reply_markup
    );
}

std::future<bool> Telegram::Bot::editMessageCaption(const std::optional<std::variant<qint64, QString>>& chat_id, const std::optional<qint32>& message_id, const std::optional<QString>& inline_message_id, const std::optional<QString>& caption, const std::optional<Message::FormattingType>& parse_mode, const std::optional<QVector<MessageEntity>>& caption_entities, const std::optional<InlineKeyboardMarkup>& reply_markup) {

    static std::array<QString, 7> keys = {
        "chat_id",
        "message_id",
        "inline_message_id",
        "caption",
        "parse_mode",
        "caption_entities",
        "reply_markup"
    };
    
    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        chat_id,
        message_id,
        inline_message_id,
        caption,
        parse_mode,
        caption_entities,
        reply_markup
    );
    
    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> bool {
    
        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "editMessageCaption"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return false;
        }
        else return true;
    });
}

std::future<bool> Telegram::Bot::editMessageCaption(const FunctionArguments::EditMessageCaption& arguments) {

    return editMessageCaption(
        arguments.chat_id,
        arguments.message_id,
        arguments.inline_message_id,
        arguments.caption,
        arguments.parse_mode,
        arguments.caption_entities,
        arguments.reply_markup
    );
}

std::future<bool> Telegram::Bot::editMessageMedia(const InputMedia& media, const std::optional<std::variant<qint64, QString>>& chat_id, const std::optional<qint32>& message_id, const std::optional<QString>& inline_message_id, const std::optional<InlineKeyboardMarkup>& reply_markup) {

    static std::array<QString, 5> keys = {
        "media",
        "chat_id",
        "message_id",
        "inline_message_id",
        "reply_markup"
    };

    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        media,
        chat_id,
        message_id,
        inline_message_id,
        reply_markup
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> bool {

        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "editMessageMedia"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return false;
        }
        else return true;
    });
}

std::future<bool> Telegram::Bot::editMessageMedia(const FunctionArguments::EditMessageMedia& arguments) {

    return editMessageMedia(
        arguments.media,
        arguments.chat_id,
        arguments.message_id,
        arguments.inline_message_id,
        arguments.reply_markup
    );
}

std::future<bool> Telegram::Bot::editMessageReplyMarkup(const std::optional<std::variant<qint64, QString>>& chat_id, const std::optional<qint32>& message_id, const std::optional<QString>& inline_message_id, const std::optional<InlineKeyboardMarkup>& reply_markup) {

    static std::array<QString, 4> keys = {
        "chat_id",
        "message_id",
        "inline_message_id",
        "reply_markup"
    };

    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        chat_id,
        message_id,
        inline_message_id,
        reply_markup
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> bool {

        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "editMessageReplyMarkup"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return false;
        }
        else return true;
     });
}

std::future<bool> Telegram::Bot::editMessageReplyMarkup(const FunctionArguments::EditMessageReplyMarkup& arguments) {
    
    return editMessageReplyMarkup(
        arguments.chat_id,
        arguments.message_id,
        arguments.inline_message_id,
        arguments.reply_markup
    );
}

std::future<Telegram::Poll> Telegram::Bot::stopPoll(const std::variant<qint64, QString>& chat_id, const qint32& message_id, const std::optional<InlineKeyboardMarkup>& reply_markup) {

    static std::array<QString, 3> keys = {
        "chat_id",
        "message_id",
        "reply_markup"
    };

    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        chat_id,
        message_id,
        reply_markup
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> Poll {

        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "stopPoll"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return {};
        }
        else return response["result"].toObject();
    });
}

std::future<bool> Telegram::Bot::deleteMessage(const std::variant<qint64, QString>& chat_id, const qint32& message_id) {

    static std::array<QString, 2> keys = {
        "chat_id",
        "message_id"
    };

    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        chat_id,
        message_id
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> bool {

        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "deleteMessage"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return false;
        }
        else return true;
    });
}

std::future<Telegram::Message> Telegram::Bot::sendSticker(const std::variant<qint64, QString>& chat_id, const std::variant<QFile*, QString>& sticker, const std::optional<bool>& disable_notification, const std::optional<qint32>& reply_to_message_id, const std::optional<bool>& allow_sending_without_reply, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup) {

    static std::array<QString, 6> keys = {
        "chat_id",
        "sticker",
        "disable_notification",
        "reply_to_message_id",
        "allow_sending_without_reply",
        "reply_markup"
    };

    auto&& request_body = Utility::QHttpMultiPartInserter::make(keys,
        chat_id,
        sticker,
        disable_notification,
        reply_to_message_id,
        allow_sending_without_reply,
        reply_markup
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> Message {

        if (auto response = QJsonDocument::fromJson(Utility::Network::post(request_body.get(), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "sendSticker"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return {};
        }
        else return response["result"].toObject();
    });
}

std::future<Telegram::Message> Telegram::Bot::sendSticker(const FunctionArguments::SendSticker& arguments) {
    
    return sendSticker(
        arguments.chat_id,
        arguments.sticker,
        arguments.disable_notification,
        std::nullopt,
        std::nullopt,
        arguments.reply_markup
    );
}

std::future<Telegram::StickerSet> Telegram::Bot::getStickerSet(const QString& name) {

    static std::array<QString, 1> keys = {
        "name"
    };

    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        name
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> StickerSet {

        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "getStickerSet"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return {};
        }
        else return response["result"].toObject();
    });
}

std::future<Telegram::File> Telegram::Bot::uploadStickerFile(const qint64& user_id, QFile* png_sticker) {

    static std::array<QString, 2> keys = {
        "user_id",
        "png_sticker"
    };

    auto&& request_body = Utility::QHttpMultiPartInserter::make(keys,
        user_id,
        png_sticker
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> File {

        if (auto response = QJsonDocument::fromJson(Utility::Network::post(request_body.get(), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "uploadStickerFile"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return {};
        }
        else return response["result"].toObject();
    });
}

std::future<bool> Telegram::Bot::createNewStickerSet(const qint64& user_id, const QString& name, const QString& title, const QString& emojis, const std::optional<std::variant<QFile*, QString>>& png_sticker, QFile* tgs_sticker, const std::optional<bool>& contains_masks, const std::optional<MaskPosition>& mask_position) {

    static std::array<QString, 8> keys = {
        "user_id",
        "name",
        "title",
        "png_sticker",
        "tgs_sticker",
        "emojis",
        "contains_masks",
        "mask_position"
    };

    auto&& request_body = Utility::QHttpMultiPartInserter::make(keys,
        user_id,
        name,
        title,
        png_sticker,
        tgs_sticker,
        emojis,
        contains_masks,
        mask_position
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> bool {

        if (auto response = QJsonDocument::fromJson(Utility::Network::post(request_body.get(), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "createNewStickerSet"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return false;
        }
        else return true;
    });
}

std::future<bool> Telegram::Bot::addStickerToSet(const qint64& user_id, const QString& name, const QString& emojis, const std::optional<std::variant<QFile*, QString>>& png_sticker, QFile* tgs_sticker, const std::optional<MaskPosition>& mask_position) {

    static std::array<QString, 6> keys = {
        "user_id",
        "name",
        "png_sticker",
        "tgs_sticker",
        "emojis",
        "mask_position"
    };

    auto&& request_body = Utility::QHttpMultiPartInserter::make(keys,
        user_id,
        name,
        png_sticker,
        tgs_sticker,
        emojis,
        mask_position
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> bool {

        if (auto response = QJsonDocument::fromJson(Utility::Network::post(request_body.get(), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "addStickerToSet"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return false;
        }
        else return true;
    });
}

std::future<bool> Telegram::Bot::setStickerPositionInSet(const QString& sticker, const qint32& position) {

    static std::array<QString, 2> keys = {
        "sticker",
        "position"
    };

    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        sticker,
        position
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> bool {

        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "setStickerPositionInSet"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return false;
        }
        else return true;
    });
}

std::future<bool> Telegram::Bot::deleteStickerFromSet(const QString& sticker) {

    static std::array<QString, 1> keys = {
        "sticker"
    };

    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        sticker
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> bool {

        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "deleteStickerFromSet"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return false;
        }
        else return true;
    });
}

std::future<bool> Telegram::Bot::setStickerSetThumbnail(const QString& name, const qint64& user_id, const std::optional<std::variant<QFile*, QString>>& thumb) {

    static std::array<QString, 3> keys = {
        "name",
        "user_id",
        "thumb"
    };

    auto&& request_body = Utility::QHttpMultiPartInserter::make(keys,
        name,
        user_id,
        thumb
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> bool {

        if (auto response = QJsonDocument::fromJson(Utility::Network::post(request_body.get(), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "setStickerSetThumbnail"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return false;
        }
        else return true;
    });
}

std::future<bool> Telegram::Bot::answerInlineQuery(const QString& inline_query_id, const QVector<InlineQueryResult*> results, const std::optional<qint32>& cache_time, const std::optional<bool>& is_personal, const std::optional<QString>& next_offset, const std::optional<QString>& switch_pm_text, const std::optional<QString>& switch_pm_parameter) {

    static std::array<QString, 7> keys = {
        "inline_query_id",
        "results",
        "cache_time",
        "is_personal",
        "next_offset",
        "switch_pm_text",
        "switch_pm_parameter"
    };

    auto&& request_body = Utility::QJsonObjectInserter::make(keys,
        inline_query_id,
        results,
        cache_time,
        is_personal,
        next_offset,
        switch_pm_text,
        switch_pm_parameter
    );

    return std::async(std::launch::async, [this, request_body = std::move(request_body)]() -> bool {

        if (auto response = QJsonDocument::fromJson(Utility::Network::post(QJsonDocument(request_body), MAKE_LINK_TO_TG_API(bot_settings->bot_token, "answerInlineQuery"))).object();
            response["ok"].toBool() == false)
        {
            emit errorOccured(response);
            return false;
        }
        else return true;
    });
}


