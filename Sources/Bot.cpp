#include "Bot.h"
#include "RequestManager.h"

#include "Internal/ConversionFunctions.h"

#include "Types/User.h"

#include "qfile.h"

#include "qjsondocument.h"
#include "qjsonarray.h"
#include "qjsonobject.h"
#include "qjsonvalue.h"

Telegram::Bot::Bot() :
	webhookManager(),
    requestManager()
{
	/* This function introspect incoming Update from Telegram and emit appropriate signal, depending on what kind of Update 
	 * is received (e.g if new message received - new_message_received signal emitted, etc...) */
	auto parseUpdate = [this](Update* update) -> void
	{
		if (update->message.has_value())				    emit messageReceived(update->update_id, update->message.value());
		else if (update->edited_message.has_value())		emit messageWasUpdated(update->update_id, update->edited_message.value());
		else if (update->channel_post.has_value())			emit channelPostReceived(update->update_id, update->channel_post.value());
		else if (update->edited_channel_post.has_value())	emit channelPostWasUpdated(update->update_id, update->edited_channel_post.value());
		// else if (update->inline_query.has_value())			emit inlineQueryReceived(update->update_id, update->inline_query.value());
		// else if (update->message.chosen_inline_result())	emit chosenInlineResult(update->update_id, update->chosen_inline_result.value());
		else if (update->callback_query.has_value())		emit callbackQueryReceived(update->update_id, update->callback_query.value());
		//else if (update->shipping_query.has_value())		emit shippingQueryReceived(update->update_id, update->shipping_query.value());
		//else if (update->pre_checkout_query.has_value())	emit preCheckoutQueryReceived(update->update_id, update->pre_checkout_query.value());
		else if (update->poll.has_value())					emit pollReceived(update->update_id, update->poll.value());
		else if (update->poll_answer.has_value())			emit pollAnswerReceived(update->update_id, update->poll_answer.value());
		else if (update->my_chat_member.has_value())		emit myChatMemberStatusUpdated(update->update_id, update->my_chat_member.value());
		else if (update->chat_member.has_value())			emit chatMemberStatusUpdated(update->update_id, update->chat_member.value());
        delete update;
	};

	/* If Webhook manager receives Update - analyze it and emit appropriate signal */
	connect(&webhookManager, &Telegram::WebhookManager::UpdateReceived, parseUpdate);
}

Telegram::User Telegram::Bot::getMe()
{
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendGetRequest(QUrlQuery(), QString("https://api.telegram.org/bot%1/getMe").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return empty object and emit errorOccured() signal */
    if (response.object().value("ok").toBool())
        return User(response.object().value("result").toObject());
    else
    {
        emit errorOccured(Error(response.object()));
        return User();
    }
}

bool Telegram::Bot::logOut()
{
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendGetRequest(QUrlQuery(), QString("https://api.telegram.org/bot%1/logOut").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return empty object and emit errorOccured() signal */
    if (response.object().value("ok").toBool())
        return true;
    else
    {
        emit errorOccured(Error(response.object()));
        return false;
    }
}

bool Telegram::Bot::close()
{
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendGetRequest(QUrlQuery(), QString("https://api.telegram.org/bot%1/close").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return empty object and emit errorOccured() signal */
    if (response.object().value("ok").toBool())
        return true;
    else
    {
        emit errorOccured(Error(response.object()));
        return false;
    }
}

Telegram::Message Telegram::Bot::sendMessage(const std::variant<qint32, QString>& chat_id, const QString& text, const std::optional<QString>& parse_mode, const std::optional<QVector<MessageEntity>>& entities, const std::optional<bool>& disable_web_page_preview, const std::optional<bool>& disable_notification, const std::optional<qint32>& reply_to_message_id, const std::optional<bool>& allow_sending_without_reply, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>> reply_markup)
{
    /* Creating request body in JSON and filling it with request parameters */
    QJsonObject requestBody{ {"text", text} };

    if (std::holds_alternative<qint32>(chat_id))       requestBody.insert("chat_id", std::get<qint32>(chat_id));
    else if (std::holds_alternative<QString>(chat_id)) requestBody.insert("chat_id", std::get<QString>(chat_id));

    if (parse_mode.has_value())                  requestBody.insert("parse_mode", *parse_mode);
    if (entities.has_value())                    requestBody.insert("entities", QVectorToQJsonArray(*entities));
    if (disable_web_page_preview.has_value())    requestBody.insert("disable_web_page_preview", *disable_web_page_preview);
    if (disable_notification.has_value())        requestBody.insert("disable_notification", *disable_notification);
    if (reply_to_message_id.has_value())         requestBody.insert("reply_to_message_id", *reply_to_message_id);
    if (allow_sending_without_reply.has_value()) requestBody.insert("allow_sending_without_reply", *allow_sending_without_reply);

    if (reply_markup.has_value())
    {
        if (std::holds_alternative<InlineKeyboardMarkup>(*reply_markup))      requestBody.insert("reply_markup", std::get<InlineKeyboardMarkup>(*reply_markup).toObject());
        else if (std::holds_alternative<ReplyKeyboardMarkup>(*reply_markup))  requestBody.insert("reply_markup", std::get<ReplyKeyboardMarkup>(*reply_markup).toObject());
        else if (std::holds_alternative<ReplyKeyboardRemove>(*reply_markup))  requestBody.insert("reply_markup", std::get<ReplyKeyboardRemove>(*reply_markup).toObject());
        else if (std::holds_alternative<ForceReply>(*reply_markup))           requestBody.insert("reply_markup", std::get<ForceReply>(*reply_markup).toObject());
    }

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(QJsonDocument(requestBody), QString("https://api.telegram.org/bot%1/sendMessage").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return empty object and emit errorOccured() signal */
    if (response.object().value("ok").toBool() == true)
        return Message(response.object().value("result").toObject());
    else
    {
        emit errorOccured(Error(response.object()));
        return Message();
    }
}

Telegram::Message Telegram::Bot::forwardMessage(const std::variant<qint32, QString>& chat_id, const std::variant<qint32, QString>& from_chat_id, const qint32& message_id, const std::optional<bool>& disable_notification)
{
    /* Creating request body in JSON and filling it with request parameters */
    QJsonObject requestBody{ {"message_id", message_id} };

    if (std::holds_alternative<qint32>(chat_id))       requestBody.insert("chat_id", std::get<qint32>(chat_id));
    else if (std::holds_alternative<QString>(chat_id)) requestBody.insert("chat_id", std::get<QString>(chat_id));

    if (std::holds_alternative<qint32>(from_chat_id))       requestBody.insert("from_chat_id", std::get<qint32>(from_chat_id));
    else if (std::holds_alternative<QString>(from_chat_id)) requestBody.insert("from_chat_id", std::get<QString>(from_chat_id));

    if (disable_notification.has_value()) requestBody.insert("disable_notification", *disable_notification);

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(QJsonDocument(requestBody), QString("https://api.telegram.org/bot%1/forwardMessage").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return empty object */
    if (response.object().value("ok").toBool() == true)
        return Message(response.object().value("result").toObject());
    else
    {
        emit errorOccured(Error(response.object()));
        return Message();
    }
}

Telegram::MessageId Telegram::Bot::copyMessage(const std::variant<qint32, QString>& chat_id, const std::variant<qint32, QString>& from_chat_id, const qint32& message_id, const std::optional<QString>& caption, const std::optional<QString>& parse_mode, const std::optional<QVector<MessageEntity>>& caption_entities, const std::optional<bool>& disable_notification, const std::optional<qint32>& reply_to_message_id, const std::optional<bool>& allow_sending_without_reply, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup)
{
    /* Creating request body in JSON and filling it with request parameters */
    QJsonObject requestBody{ {"message_id", message_id} };

    if (std::holds_alternative<qint32>(chat_id))       requestBody.insert("chat_id", std::get<qint32>(chat_id));
    else if (std::holds_alternative<QString>(chat_id)) requestBody.insert("chat_id", std::get<QString>(chat_id));

    if (std::holds_alternative<qint32>(from_chat_id))       requestBody.insert("from_chat_id", std::get<qint32>(from_chat_id));
    else if (std::holds_alternative<QString>(from_chat_id)) requestBody.insert("from_chat_id", std::get<QString>(from_chat_id));

    if (caption.has_value())                     requestBody.insert("caption", *caption);
    if (parse_mode.has_value())                  requestBody.insert("parse_mode", *parse_mode);
    if (caption_entities.has_value())            requestBody.insert("caption_entities", QVectorToQJsonArray(*caption_entities));
    if (disable_notification.has_value())        requestBody.insert("disable_notification", *disable_notification);
    if (reply_to_message_id.has_value())         requestBody.insert("reply_to_message_id", *reply_to_message_id);
    if (allow_sending_without_reply.has_value()) requestBody.insert("allow_sending_without_reply", *allow_sending_without_reply);
    
    if (reply_markup.has_value())
    {
        if (std::holds_alternative<InlineKeyboardMarkup>(*reply_markup))      requestBody.insert("reply_markup", std::get<InlineKeyboardMarkup>(*reply_markup).toObject());
        else if (std::holds_alternative<ReplyKeyboardMarkup>(*reply_markup))  requestBody.insert("reply_markup", std::get<ReplyKeyboardMarkup>(*reply_markup).toObject());
        else if (std::holds_alternative<ReplyKeyboardRemove>(*reply_markup))  requestBody.insert("reply_markup", std::get<ReplyKeyboardRemove>(*reply_markup).toObject());
        else if (std::holds_alternative<ForceReply>(*reply_markup))           requestBody.insert("reply_markup", std::get<ForceReply>(*reply_markup).toObject());
    }

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(QJsonDocument(requestBody), QString("https://api.telegram.org/bot%1/copyMessage").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return empty object */
    if (response.object().value("ok").toBool() == true)
        return MessageId(response.object().value("result").toObject());
    else
    {
        emit errorOccured(Error(response.object()));
        return MessageId();
    }
}

Telegram::Message Telegram::Bot::sendPhoto(const std::variant<qint32, QString>& chat_id, const std::variant<QFile*, QString>& photo, const std::optional<QString>& caption, const std::optional<QString>& parse_mode, const std::optional<QVector<MessageEntity>>& caption_entities, const std::optional<bool>& disable_notification, const std::optional<qint32>& reply_to_message_id, const std::optional<bool>& allow_sending_without_reply, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup)
{
    /* Preparing request body */
    QVector<QPair<QString, QVariant>> requestParameters;
    QVector<QPair<QString, QFile*>> filesToUpload;

    if (std::holds_alternative<qint32>(chat_id))       requestParameters.push_back(QPair<QString, QVariant>("chat_id", std::get<qint32>(chat_id)));
    else if (std::holds_alternative<QString>(chat_id)) requestParameters.push_back(QPair<QString, QVariant>("chat_id", std::get<QString>(chat_id)));

    if (std::holds_alternative<QFile*>(photo))       filesToUpload.push_back(QPair<QString, QFile*>("photo", std::get<QFile*>(photo)));
    else if (std::holds_alternative<QString>(photo)) requestParameters.push_back(QPair<QString, QVariant>("photo", std::get<QString>(photo)));

    if (caption.has_value())                     requestParameters.push_back(QPair<QString, QVariant>("caption", *caption));
    if (parse_mode.has_value())                  requestParameters.push_back(QPair<QString, QVariant>("parse_mode", *parse_mode));
    if (caption_entities.has_value())            requestParameters.push_back(QPair<QString, QVariant>("caption_entities", QVectorToQJsonArray(*caption_entities)));
    if (disable_notification.has_value())        requestParameters.push_back(QPair<QString, QVariant>("disable_notification", *disable_notification));
    if (reply_to_message_id.has_value())         requestParameters.push_back(QPair<QString, QVariant>("reply_to_message_id", *reply_to_message_id));
    if (allow_sending_without_reply.has_value()) requestParameters.push_back(QPair<QString, QVariant>("allow_sending_without_reply", *allow_sending_without_reply));

    if (reply_markup.has_value())
    {
        if (std::holds_alternative<InlineKeyboardMarkup>(*reply_markup))      requestParameters.push_back(QPair<QString, QVariant>("reply_markup", std::get<InlineKeyboardMarkup>(*reply_markup).toObject()));
        else if (std::holds_alternative<ReplyKeyboardMarkup>(*reply_markup))  requestParameters.push_back(QPair<QString, QVariant>("reply_markup", std::get<ReplyKeyboardMarkup>(*reply_markup).toObject()));
        else if (std::holds_alternative<ReplyKeyboardRemove>(*reply_markup))  requestParameters.push_back(QPair<QString, QVariant>("reply_markup", std::get<ReplyKeyboardRemove>(*reply_markup).toObject()));
        else if (std::holds_alternative<ForceReply>(*reply_markup))           requestParameters.push_back(QPair<QString, QVariant>("reply_markup", std::get<ForceReply>(*reply_markup).toObject()));
    }

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(filesToUpload, requestParameters, QString("https://api.telegram.org/bot%1/sendPhoto").arg(BOT_TOKEN)));

    qDebug() << response;

    /* Check if request was successful. In case of error return empty object */
    if (response.object().value("ok").toBool() == true)
        return Message(response.object().value("result").toObject());
    else
    {
        emit errorOccured(Error(response.object()));
        return Message();
    }
}

Telegram::Message Telegram::Bot::sendAudio(const std::variant<qint32, QString>& chat_id, const std::variant<QFile*, QString>& audio, const std::optional<QString>& caption, const std::optional<QString>& parse_mode, const std::optional<QVector<MessageEntity>>& caption_entities, const std::optional<qint32>& duration, const std::optional<QString>& performer, const std::optional<QString>& title, const std::optional<std::variant<QFile*, QString>>& thumb, const std::optional<bool>& disable_notification, const std::optional<qint32>& reply_to_message_id, const std::optional<bool>& allow_sending_without_reply, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup)
{
    /* Preparing request body */
    QVector<QPair<QString, QVariant>> requestParameters;
    QVector<QPair<QString, QFile*>> filesToUpload;

    if (std::holds_alternative<qint32>(chat_id))       requestParameters.push_back(QPair<QString, QVariant>("chat_id", std::get<qint32>(chat_id)));
    else if (std::holds_alternative<QString>(chat_id)) requestParameters.push_back(QPair<QString, QVariant>("chat_id", std::get<QString>(chat_id)));

    if (std::holds_alternative<QFile*>(audio))       filesToUpload.push_back(QPair<QString, QFile*>("audio", std::get<QFile*>(audio)));
    else if (std::holds_alternative<QString>(audio)) requestParameters.push_back(QPair<QString, QVariant>("audio", std::get<QString>(audio)));

    if (caption.has_value())          requestParameters.push_back(QPair<QString, QVariant>("caption", *caption));
    if (parse_mode.has_value())       requestParameters.push_back(QPair<QString, QVariant>("parse_mode", *parse_mode));
    if (caption_entities.has_value()) requestParameters.push_back(QPair<QString, QVariant>("caption_entities", QVectorToQJsonArray(*caption_entities)));
    if (duration.has_value())         requestParameters.push_back(QPair<QString, QVariant>("duration", *duration));
    if (performer.has_value())        requestParameters.push_back(QPair<QString, QVariant>("performer", *performer));
    if (title.has_value())            requestParameters.push_back(QPair<QString, QVariant>("title", *title));

    if (thumb.has_value())
    {
        if (std::holds_alternative<QFile*>(*thumb))       filesToUpload.push_back(QPair<QString, QFile*>("thumb", std::get<QFile*>(*thumb)));
        else if (std::holds_alternative<QString>(*thumb)) requestParameters.push_back(QPair<QString, QVariant>("thumb", std::get<QString>(*thumb)));
    }

    if (disable_notification.has_value())        requestParameters.push_back(QPair<QString, QVariant>("disable_notification", *disable_notification));
    if (reply_to_message_id.has_value())         requestParameters.push_back(QPair<QString, QVariant>("reply_to_message_id", *reply_to_message_id));
    if (allow_sending_without_reply.has_value()) requestParameters.push_back(QPair<QString, QVariant>("allow_sending_without_reply", *allow_sending_without_reply));

    if (reply_markup.has_value())
    {
        if (std::holds_alternative<InlineKeyboardMarkup>(*reply_markup))      requestParameters.push_back(QPair<QString, QVariant>("reply_markup", std::get<InlineKeyboardMarkup>(*reply_markup).toObject()));
        else if (std::holds_alternative<ReplyKeyboardMarkup>(*reply_markup))  requestParameters.push_back(QPair<QString, QVariant>("reply_markup", std::get<ReplyKeyboardMarkup>(*reply_markup).toObject()));
        else if (std::holds_alternative<ReplyKeyboardRemove>(*reply_markup))  requestParameters.push_back(QPair<QString, QVariant>("reply_markup", std::get<ReplyKeyboardRemove>(*reply_markup).toObject()));
        else if (std::holds_alternative<ForceReply>(*reply_markup))           requestParameters.push_back(QPair<QString, QVariant>("reply_markup", std::get<ForceReply>(*reply_markup).toObject()));
    }

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(filesToUpload, requestParameters, QString("https://api.telegram.org/bot%1/sendAudio").arg(BOT_TOKEN)));
    
    /* Check if request was successful. In case of error return empty object */
    if (response.object().value("ok").toBool() == true)
        return Message(response.object().value("result").toObject());
    else
    {
        emit errorOccured(Error(response.object()));
        return Message();
    }
}

Telegram::Message Telegram::Bot::sendDocument(const std::variant<qint32, QString>& chat_id, const std::variant<QFile*, QString>& document, const std::optional<std::variant<QFile*, QString>>& thumb, const std::optional<QString>& caption, const std::optional<QString>& parse_mode, const std::optional<QVector<MessageEntity>>& caption_entities, const std::optional<bool>& disable_content_type_detection, const std::optional<bool>& disable_notification, const std::optional<qint32>& reply_to_message_id, const std::optional<bool>& allow_sending_without_reply, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup)
{
    /* Preparing request body */
    QVector<QPair<QString, QVariant>> requestParameters;
    QVector<QPair<QString, QFile*>> filesToUpload;

    if (std::holds_alternative<qint32>(chat_id))       requestParameters.push_back(QPair<QString, QVariant>("chat_id", std::get<qint32>(chat_id)));
    else if (std::holds_alternative<QString>(chat_id)) requestParameters.push_back(QPair<QString, QVariant>("chat_id", std::get<QString>(chat_id)));

    if (std::holds_alternative<QFile*>(document))       filesToUpload.push_back(QPair<QString, QFile*>("document", std::get<QFile*>(document)));
    else if (std::holds_alternative<QString>(document)) requestParameters.push_back(QPair<QString, QVariant>("document", std::get<QString>(document)));

    if (thumb.has_value())
    {
        if (std::holds_alternative<QFile*>(*thumb))       filesToUpload.push_back(QPair<QString, QFile*>("thumb", std::get<QFile*>(*thumb)));
        else if (std::holds_alternative<QString>(*thumb)) requestParameters.push_back(QPair<QString, QVariant>("thumb", std::get<QString>(*thumb)));
    }

    if (caption.has_value())                        requestParameters.push_back(QPair<QString, QVariant>("caption", *caption));
    if (parse_mode.has_value())                     requestParameters.push_back(QPair<QString, QVariant>("parse_mode", *parse_mode));
    if (caption_entities.has_value())               requestParameters.push_back(QPair<QString, QVariant>("caption_entities", QVectorToQJsonArray(*caption_entities)));
    if (disable_content_type_detection.has_value()) requestParameters.push_back(QPair<QString, QVariant>("disable_content_type_detection", *disable_content_type_detection));
    if (disable_notification.has_value())           requestParameters.push_back(QPair<QString, QVariant>("disable_notification", *disable_notification));
    if (reply_to_message_id.has_value())            requestParameters.push_back(QPair<QString, QVariant>("reply_to_message_id", *reply_to_message_id));
    if (allow_sending_without_reply.has_value())    requestParameters.push_back(QPair<QString, QVariant>("allow_sending_without_reply", *allow_sending_without_reply));

    if (reply_markup.has_value())
    {
        if (std::holds_alternative<InlineKeyboardMarkup>(*reply_markup))      requestParameters.push_back(QPair<QString, QVariant>("reply_markup", std::get<InlineKeyboardMarkup>(*reply_markup).toObject()));
        else if (std::holds_alternative<ReplyKeyboardMarkup>(*reply_markup))  requestParameters.push_back(QPair<QString, QVariant>("reply_markup", std::get<ReplyKeyboardMarkup>(*reply_markup).toObject()));
        else if (std::holds_alternative<ReplyKeyboardRemove>(*reply_markup))  requestParameters.push_back(QPair<QString, QVariant>("reply_markup", std::get<ReplyKeyboardRemove>(*reply_markup).toObject()));
        else if (std::holds_alternative<ForceReply>(*reply_markup))           requestParameters.push_back(QPair<QString, QVariant>("reply_markup", std::get<ForceReply>(*reply_markup).toObject()));
    }

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(filesToUpload, requestParameters, QString("https://api.telegram.org/bot%1/sendDocument").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return empty object */
    if (response.object().value("ok").toBool() == true)
        return Message(response.object().value("result").toObject());
    else
    {
        emit errorOccured(Error(response.object()));
        return Message();
    }
}

Telegram::Message Telegram::Bot::sendVideo(const std::variant<qint32, QString>& chat_id, const std::variant<QFile*, QString>& video, const std::optional<qint32>& duration, const std::optional<qint32>& width, const std::optional<qint32>& height, const std::optional<std::variant<QFile*, QString>>& thumb, const std::optional<QString>& caption, const std::optional<QString>& parse_mode, const std::optional<QVector<MessageEntity>>& caption_entities, const std::optional<bool>& supports_streaming, const std::optional<bool>& disable_notification, const std::optional<qint32>& reply_to_message_id, const std::optional<bool>& allow_sending_without_reply, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup)
{
    /* Preparing request body */
    QVector<QPair<QString, QVariant>> requestParameters;
    QVector<QPair<QString, QFile*>> filesToUpload;

    if (std::holds_alternative<qint32>(chat_id))       requestParameters.push_back(QPair<QString, QVariant>("chat_id", std::get<qint32>(chat_id)));
    else if (std::holds_alternative<QString>(chat_id)) requestParameters.push_back(QPair<QString, QVariant>("chat_id", std::get<QString>(chat_id)));

    if (std::holds_alternative<QFile*>(video))       filesToUpload.push_back(QPair<QString, QFile*>("video", std::get<QFile*>(video)));
    else if (std::holds_alternative<QString>(video)) requestParameters.push_back(QPair<QString, QVariant>("video", std::get<QString>(video)));

    if (duration.has_value()) requestParameters.push_back(QPair<QString, QVariant>("duration", *duration));
    if (width.has_value())    requestParameters.push_back(QPair<QString, QVariant>("width", *width));
    if (height.has_value())   requestParameters.push_back(QPair<QString, QVariant>("height", *height));

    if (thumb.has_value())
    {
        if (std::holds_alternative<QFile*>(*thumb))       filesToUpload.push_back(QPair<QString, QFile*>("thumb", std::get<QFile*>(*thumb)));
        else if (std::holds_alternative<QString>(*thumb)) requestParameters.push_back(QPair<QString, QVariant>("thumb", std::get<QString>(*thumb)));
    }

    if (caption.has_value())                        requestParameters.push_back(QPair<QString, QVariant>("caption", *caption));
    if (parse_mode.has_value())                     requestParameters.push_back(QPair<QString, QVariant>("parse_mode", *parse_mode));
    if (caption_entities.has_value())               requestParameters.push_back(QPair<QString, QVariant>("caption_entities", QVectorToQJsonArray(*caption_entities)));
    if (supports_streaming.has_value())             requestParameters.push_back(QPair<QString, QVariant>("supports_streaming", *supports_streaming));
    if (disable_notification.has_value())           requestParameters.push_back(QPair<QString, QVariant>("disable_notification", *disable_notification));
    if (reply_to_message_id.has_value())            requestParameters.push_back(QPair<QString, QVariant>("reply_to_message_id", *reply_to_message_id));
    if (allow_sending_without_reply.has_value())    requestParameters.push_back(QPair<QString, QVariant>("allow_sending_without_reply", *allow_sending_without_reply));

    if (reply_markup.has_value())
    {
        if (std::holds_alternative<InlineKeyboardMarkup>(*reply_markup))      requestParameters.push_back(QPair<QString, QVariant>("reply_markup", std::get<InlineKeyboardMarkup>(*reply_markup).toObject()));
        else if (std::holds_alternative<ReplyKeyboardMarkup>(*reply_markup))  requestParameters.push_back(QPair<QString, QVariant>("reply_markup", std::get<ReplyKeyboardMarkup>(*reply_markup).toObject()));
        else if (std::holds_alternative<ReplyKeyboardRemove>(*reply_markup))  requestParameters.push_back(QPair<QString, QVariant>("reply_markup", std::get<ReplyKeyboardRemove>(*reply_markup).toObject()));
        else if (std::holds_alternative<ForceReply>(*reply_markup))           requestParameters.push_back(QPair<QString, QVariant>("reply_markup", std::get<ForceReply>(*reply_markup).toObject()));
    }

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(filesToUpload, requestParameters, QString("https://api.telegram.org/bot%1/sendVideo").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return empty object */
    if (response.object().value("ok").toBool() == true)
        return Message(response.object().value("result").toObject());
    else
    {
        emit errorOccured(Error(response.object()));
        return Message();
    }
}

Telegram::Message Telegram::Bot::sendAnimation(const std::variant<qint32, QString>& chat_id, const std::variant<QFile*, QString>& animation, const std::optional<qint32>& duration, const std::optional<qint32>& width, const std::optional<qint32>& height, const std::optional<std::variant<QFile*, QString>>& thumb, const std::optional<QString>& caption, const std::optional<QString>& parse_mode, const std::optional<QVector<MessageEntity>>& caption_entities, const std::optional<bool>& disable_notification, const std::optional<qint32>& reply_to_message_id, const std::optional<bool>& allow_sending_without_reply, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup)
{
    /* Preparing request body */
    QVector<QPair<QString, QVariant>> requestParameters;
    QVector<QPair<QString, QFile*>> filesToUpload;

    if (std::holds_alternative<qint32>(chat_id))       requestParameters.push_back(QPair<QString, QVariant>("chat_id", std::get<qint32>(chat_id)));
    else if (std::holds_alternative<QString>(chat_id)) requestParameters.push_back(QPair<QString, QVariant>("chat_id", std::get<QString>(chat_id)));

    if (std::holds_alternative<QFile*>(animation))       filesToUpload.push_back(QPair<QString, QFile*>("animation", std::get<QFile*>(animation)));
    else if (std::holds_alternative<QString>(animation)) requestParameters.push_back(QPair<QString, QVariant>("animation", std::get<QString>(animation)));

    if (duration.has_value()) requestParameters.push_back(QPair<QString, QVariant>("duration", *duration));
    if (width.has_value())    requestParameters.push_back(QPair<QString, QVariant>("width", *width));
    if (height.has_value())   requestParameters.push_back(QPair<QString, QVariant>("height", *height));

    if (thumb.has_value())
    {
        if (std::holds_alternative<QFile*>(*thumb))  filesToUpload.push_back(QPair<QString, QFile*>("thumb", std::get<QFile*>(*thumb)));
        else if (std::holds_alternative<QString>(*thumb)) requestParameters.push_back(QPair<QString, QVariant>("thumb", std::get<QString>(*thumb)));
    }

    if (caption.has_value())                        requestParameters.push_back(QPair<QString, QVariant>("caption", *caption));
    if (parse_mode.has_value())                     requestParameters.push_back(QPair<QString, QVariant>("parse_mode", *parse_mode));
    if (caption_entities.has_value())               requestParameters.push_back(QPair<QString, QVariant>("caption_entities", QVectorToQJsonArray(*caption_entities)));
    if (disable_notification.has_value())           requestParameters.push_back(QPair<QString, QVariant>("disable_notification", *disable_notification));
    if (reply_to_message_id.has_value())            requestParameters.push_back(QPair<QString, QVariant>("reply_to_message_id", *reply_to_message_id));
    if (allow_sending_without_reply.has_value())    requestParameters.push_back(QPair<QString, QVariant>("allow_sending_without_reply", *allow_sending_without_reply));

    if (reply_markup.has_value())
    {
        if (std::holds_alternative<InlineKeyboardMarkup>(*reply_markup))      requestParameters.push_back(QPair<QString, QVariant>("reply_markup", std::get<InlineKeyboardMarkup>(*reply_markup).toObject()));
        else if (std::holds_alternative<ReplyKeyboardMarkup>(*reply_markup))  requestParameters.push_back(QPair<QString, QVariant>("reply_markup", std::get<ReplyKeyboardMarkup>(*reply_markup).toObject()));
        else if (std::holds_alternative<ReplyKeyboardRemove>(*reply_markup))  requestParameters.push_back(QPair<QString, QVariant>("reply_markup", std::get<ReplyKeyboardRemove>(*reply_markup).toObject()));
        else if (std::holds_alternative<ForceReply>(*reply_markup))           requestParameters.push_back(QPair<QString, QVariant>("reply_markup", std::get<ForceReply>(*reply_markup).toObject()));
    }

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(filesToUpload, requestParameters, QString("https://api.telegram.org/bot%1/sendAnimation").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return empty object */
    if (response.object().value("ok").toBool() == true)
        return Message(response.object().value("result").toObject());
    else
    {
        emit errorOccured(Error(response.object()));
        return Message();
    }
}

Telegram::Message Telegram::Bot::sendVoice(const std::variant<qint32, QString>& chat_id, const std::variant<QFile*, QString>& voice, const std::optional<QString>& caption, const std::optional<QString>& parse_mode, const std::optional<QVector<MessageEntity>>& caption_entities, const std::optional<qint32>& duration, const std::optional<bool>& disable_notification, const std::optional<qint32>& reply_to_message_id, const std::optional<bool>& allow_sending_without_reply, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup)
{
    /* Preparing request body */
    QVector<QPair<QString, QVariant>> requestParameters;
    QVector<QPair<QString, QFile*>> filesToUpload;

    if (std::holds_alternative<qint32>(chat_id))       requestParameters.push_back(QPair<QString, QVariant>("chat_id", std::get<qint32>(chat_id)));
    else if (std::holds_alternative<QString>(chat_id)) requestParameters.push_back(QPair<QString, QVariant>("chat_id", std::get<QString>(chat_id)));

    if (std::holds_alternative<QFile*>(voice))       filesToUpload.push_back(QPair<QString, QFile*>("voice", std::get<QFile*>(voice)));
    else if (std::holds_alternative<QString>(voice)) requestParameters.push_back(QPair<QString, QVariant>("voice", std::get<QString>(voice)));

    if (caption.has_value())                     requestParameters.push_back(QPair<QString, QVariant>("caption", *caption));
    if (parse_mode.has_value())                  requestParameters.push_back(QPair<QString, QVariant>("parse_mode", *parse_mode));
    if (caption_entities.has_value())            requestParameters.push_back(QPair<QString, QVariant>("caption_entities", QVectorToQJsonArray(*caption_entities)));
    if (duration.has_value())                    requestParameters.push_back(QPair<QString, QVariant>("duration", *duration));
    if (disable_notification.has_value())        requestParameters.push_back(QPair<QString, QVariant>("disable_notification", *disable_notification));
    if (reply_to_message_id.has_value())         requestParameters.push_back(QPair<QString, QVariant>("reply_to_message_id", *reply_to_message_id));
    if (allow_sending_without_reply.has_value()) requestParameters.push_back(QPair<QString, QVariant>("allow_sending_without_reply", *allow_sending_without_reply));

    if (reply_markup.has_value())
    {
        if (std::holds_alternative<InlineKeyboardMarkup>(*reply_markup)) requestParameters.push_back(QPair<QString, QVariant>("reply_markup", std::get<InlineKeyboardMarkup>(*reply_markup).toObject()));
        else if (std::holds_alternative<ReplyKeyboardMarkup>(*reply_markup))  requestParameters.push_back(QPair<QString, QVariant>("reply_markup", std::get<ReplyKeyboardMarkup>(*reply_markup).toObject()));
        else if (std::holds_alternative<ReplyKeyboardRemove>(*reply_markup))  requestParameters.push_back(QPair<QString, QVariant>("reply_markup", std::get<ReplyKeyboardRemove>(*reply_markup).toObject()));
        else if (std::holds_alternative<ForceReply>(*reply_markup))           requestParameters.push_back(QPair<QString, QVariant>("reply_markup", std::get<ForceReply>(*reply_markup).toObject()));
    }

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(filesToUpload, requestParameters, QString("https://api.telegram.org/bot%1/sendVoice").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return empty object */
    if (response.object().value("ok").toBool() == true)
        return Message(response.object().value("result").toObject());
    else
    {
        emit errorOccured(Error(response.object()));
        return Message();
    }
}

Telegram::Message Telegram::Bot::sendVideoNote(const std::variant<qint32, QString>& chat_id, const std::variant<QFile*, QString>& video_note, const std::optional<qint32>& duration, const std::optional<qint32>& length, const std::optional<std::variant<QFile*, QString>>& thumb, const std::optional<bool>& disable_notification, const std::optional<qint32>& reply_to_message_id, const std::optional<bool>& allow_sending_without_reply, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup)
{
    /* Preparing request body */
    QVector<QPair<QString, QVariant>> requestParameters;
    QVector<QPair<QString, QFile*>> filesToUpload;

    if (std::holds_alternative<qint32>(chat_id))       requestParameters.push_back(QPair<QString, QVariant>("chat_id", std::get<qint32>(chat_id)));
    else if (std::holds_alternative<QString>(chat_id)) requestParameters.push_back(QPair<QString, QVariant>("chat_id", std::get<QString>(chat_id)));

    if (std::holds_alternative<QFile*>(video_note))       filesToUpload.push_back(QPair<QString, QFile*>("voice", std::get<QFile*>(video_note)));
    else if (std::holds_alternative<QString>(video_note)) requestParameters.push_back(QPair<QString, QVariant>("voice", std::get<QString>(video_note)));

    if (duration.has_value()) requestParameters.push_back(QPair<QString, QVariant>("duration", *duration));
    if (length.has_value())   requestParameters.push_back(QPair<QString, QVariant>("length", *length));

    if (thumb.has_value())
    {
        if (std::holds_alternative<QFile*>(*thumb))       filesToUpload.push_back(QPair<QString, QFile*>("thumb", std::get<QFile*>(*thumb)));
        else if (std::holds_alternative<QString>(*thumb)) requestParameters.push_back(QPair<QString, QVariant>("thumb", std::get<QString>(*thumb)));
    }

    if (disable_notification.has_value())        requestParameters.push_back(QPair<QString, QVariant>("disable_notification", *disable_notification));
    if (reply_to_message_id.has_value())         requestParameters.push_back(QPair<QString, QVariant>("reply_to_message_id", *reply_to_message_id));
    if (allow_sending_without_reply.has_value()) requestParameters.push_back(QPair<QString, QVariant>("allow_sending_without_reply", *allow_sending_without_reply));

    if (reply_markup.has_value())
    {
        if (std::holds_alternative<InlineKeyboardMarkup>(*reply_markup))      requestParameters.push_back(QPair<QString, QVariant>("reply_markup", std::get<InlineKeyboardMarkup>(*reply_markup).toObject()));
        else if (std::holds_alternative<ReplyKeyboardMarkup>(*reply_markup))  requestParameters.push_back(QPair<QString, QVariant>("reply_markup", std::get<ReplyKeyboardMarkup>(*reply_markup).toObject()));
        else if (std::holds_alternative<ReplyKeyboardRemove>(*reply_markup))  requestParameters.push_back(QPair<QString, QVariant>("reply_markup", std::get<ReplyKeyboardRemove>(*reply_markup).toObject()));
        else if (std::holds_alternative<ForceReply>(*reply_markup))           requestParameters.push_back(QPair<QString, QVariant>("reply_markup", std::get<ForceReply>(*reply_markup).toObject()));
    }

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(filesToUpload, requestParameters, QString("https://api.telegram.org/bot%1/sendVideoNote").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return empty object */
    if (response.object().value("ok").toBool() == true)
        return Message(response.object().value("result").toObject());
    else
    {
        emit errorOccured(Error(response.object()));
        return Message();
    }
}

QVector<Telegram::Message> Telegram::Bot::sendMediaGroup(const std::variant<qint32, QString>& chat_id, const QVector<InputMediaAudio>& media, const std::optional<bool>& disable_notification, const std::optional<qint32>& reply_to_message_id, const std::optional<bool>& allow_sending_without_reply)
{
    /* Preparing request body */
    QVector<QPair<QString, QVariant>> requestParameters;
    QVector<QPair<QString, QFile*>> filesToUpload;

    if (std::holds_alternative<qint32>(chat_id))       requestParameters.push_back(QPair<QString, QVariant>("chat_id", std::get<qint32>(chat_id)));
    else if (std::holds_alternative<QString>(chat_id)) requestParameters.push_back(QPair<QString, QVariant>("chat_id", std::get<QString>(chat_id)));

    QJsonArray inputMedia;

    /* Attaching audios to uploading files */
    for (auto& inputMediaAudio : media)
    {
        inputMedia.push_back(inputMediaAudio.toObject());

        /* Check if audio is new audio loaded via QFile* and if there is no same audio attached in filesToUpload, if so - attach audio to upload */
        if (std::holds_alternative<QFile*>(inputMediaAudio.media))
            if (!filesToUpload.contains(QPair<QString, QFile*>(std::get<QFile*>(inputMediaAudio.media)->fileName(), std::get<QFile*>(inputMediaAudio.media))))
                filesToUpload.push_back(QPair<QString, QFile*>(std::get<QFile*>(inputMediaAudio.media)->fileName(), std::get<QFile*>(inputMediaAudio.media)));

    }

    requestParameters.push_back(QPair<QString, QVariant>("media", inputMedia));

    if (disable_notification.has_value())           requestParameters.push_back(QPair<QString, QVariant>("disable_notification", *disable_notification));
    if (reply_to_message_id.has_value())            requestParameters.push_back(QPair<QString, QVariant>("reply_to_message_id", *reply_to_message_id));
    if (allow_sending_without_reply.has_value())    requestParameters.push_back(QPair<QString, QVariant>("allow_sending_without_reply", *allow_sending_without_reply));

    qDebug() << "Request parameters: " << requestParameters;
    qDebug() << "Files to upload: " << filesToUpload;

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(filesToUpload, requestParameters, QString("https://api.telegram.org/bot%1/sendMediaGroup").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return empty object */
    if (response.object().value("ok").toBool() == true)
        return QVector<Message>(QJsonArrayToQVector<Message>(response.object().value("result").toArray()));
    else
    {
        emit errorOccured(Error(response.object()));
        return QVector<Message>();
    }
}

QVector<Telegram::Message> Telegram::Bot::sendMediaGroup(const std::variant<qint32, QString>& chat_id, const QVector<InputMediaDocument>& media, const std::optional<bool>& disable_notification, const std::optional<qint32>& reply_to_message_id, const std::optional<bool>& allow_sending_without_reply)
{
    /* Preparing request body */
    QVector<QPair<QString, QVariant>> requestParameters;
    QVector<QPair<QString, QFile*>> filesToUpload;

    if (std::holds_alternative<qint32>(chat_id))       requestParameters.push_back(QPair<QString, QVariant>("chat_id", std::get<qint32>(chat_id)));
    else if (std::holds_alternative<QString>(chat_id)) requestParameters.push_back(QPair<QString, QVariant>("chat_id", std::get<QString>(chat_id)));

    QJsonArray inputMedia;

    /* Attaching documents to uploading files */
    for (auto& inputMediaDocument : media)
    {
        inputMedia.push_back(inputMediaDocument.toObject());

        /* Check if document is new document loaded via QFile* and if there is no same document attached in filesToUpload, if so - attach photo to upload */
        if (std::holds_alternative<QFile*>(inputMediaDocument.media))
            if (!filesToUpload.contains(QPair<QString, QFile*>(std::get<QFile*>(inputMediaDocument.media)->fileName(), std::get<QFile*>(inputMediaDocument.media))))
                filesToUpload.push_back(QPair<QString, QFile*>(std::get<QFile*>(inputMediaDocument.media)->fileName(), std::get<QFile*>(inputMediaDocument.media)));

    }

    requestParameters.push_back(QPair<QString, QVariant>("media", inputMedia));

    if (disable_notification.has_value())           requestParameters.push_back(QPair<QString, QVariant>("disable_notification", *disable_notification));
    if (reply_to_message_id.has_value())            requestParameters.push_back(QPair<QString, QVariant>("reply_to_message_id", *reply_to_message_id));
    if (allow_sending_without_reply.has_value())    requestParameters.push_back(QPair<QString, QVariant>("allow_sending_without_reply", *allow_sending_without_reply));

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(filesToUpload, requestParameters, QString("https://api.telegram.org/bot%1/sendMediaGroup").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return empty object */
    if (response.object().value("ok").toBool() == true)
        return QVector<Message>(QJsonArrayToQVector<Message>(response.object().value("result").toArray()));
    else
    {
        emit errorOccured(Error(response.object()));
        return QVector<Message>();
    }
}

QVector<Telegram::Message> Telegram::Bot::sendMediaGroup(const std::variant<qint32, QString>& chat_id, const QPair<QVector<InputMediaPhoto>, QVector<InputMediaVideo>> media, const std::optional<bool>& disable_notification, const std::optional<qint32>& reply_to_message_id, const std::optional<bool>& allow_sending_without_reply)
{
    /* Preparing request body */
    QVector<QPair<QString, QVariant>> requestParameters;
    QVector<QPair<QString, QFile*>> filesToUpload;

    if (std::holds_alternative<qint32>(chat_id))       requestParameters.push_back(QPair<QString, QVariant>("chat_id", std::get<qint32>(chat_id)));
    else if (std::holds_alternative<QString>(chat_id)) requestParameters.push_back(QPair<QString, QVariant>("chat_id", std::get<QString>(chat_id)));

    QJsonArray inputMedia;

    /* Attaching photos to uploading files */
    for (auto& inputMediaPhoto : media.first)
    {
        inputMedia.push_back(inputMediaPhoto.toObject());

        //Can i do like that here? 
        //if (std::holds_alternative<QFile*>(inputMediaPhoto.media) and filesToUpload.contains(QPair<QString, QFile*>(std::get<QFile*>(inputMediaPhoto.media)->fileName(), std::get<QFile*>(inputMediaPhoto.media))
        /* Check if photo is new photo loaded via QFile* and if there is no same photo attached in filesToUpload, if so - attach photo to upload */
        if (std::holds_alternative<QFile*>(inputMediaPhoto.media)) 
            if(!filesToUpload.contains(QPair<QString, QFile*>(std::get<QFile*>(inputMediaPhoto.media)->fileName(), std::get<QFile*>(inputMediaPhoto.media))))
                filesToUpload.push_back(QPair<QString, QFile*>(std::get<QFile*>(inputMediaPhoto.media)->fileName(), std::get<QFile*>(inputMediaPhoto.media)));

    }

    /* Attaching videos to uploading files */
    for (auto& inputMediaVideo : media.second)
    {
        inputMedia.push_back(inputMediaVideo.toObject());

        /* Check if video is new video loaded via QFile* and if there is no same video attached in filesToUpload, if so - attach video to upload */
        if (std::holds_alternative<QFile*>(inputMediaVideo.media))
            if(!filesToUpload.contains(QPair<QString, QFile*>(std::get<QFile*>(inputMediaVideo.media)->fileName(), std::get<QFile*>(inputMediaVideo.media))))
                filesToUpload.push_back(QPair<QString, QFile*>(std::get<QFile*>(inputMediaVideo.media)->fileName(), std::get<QFile*>(inputMediaVideo.media)));
        
        /* Check if thumb is new thumb loaded via QFile* and if there is no same thumb attached in filesToUpload, if so - attach thumb to upload */
        if (inputMediaVideo.thumb.has_value())
            if (std::holds_alternative<QFile*>(inputMediaVideo.thumb.value()))
                if (!filesToUpload.contains(QPair<QString, QFile*>(std::get<QFile*>(inputMediaVideo.thumb.value())->fileName(), std::get<QFile*>(inputMediaVideo.thumb.value()))))
                    filesToUpload.push_back(QPair<QString, QFile*>(std::get<QFile*>(inputMediaVideo.thumb.value())->fileName(), std::get<QFile*>(inputMediaVideo.thumb.value())));
    }

    requestParameters.push_back(QPair<QString, QVariant>("media", inputMedia));

    if (disable_notification.has_value())           requestParameters.push_back(QPair<QString, QVariant>("disable_notification", *disable_notification));
    if (reply_to_message_id.has_value())            requestParameters.push_back(QPair<QString, QVariant>("reply_to_message_id", *reply_to_message_id));
    if (allow_sending_without_reply.has_value())    requestParameters.push_back(QPair<QString, QVariant>("allow_sending_without_reply", *allow_sending_without_reply));

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(filesToUpload, requestParameters, QString("https://api.telegram.org/bot%1/sendMediaGroup").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return empty object */
    if (response.object().value("ok").toBool() == true)
        return QVector<Message>(QJsonArrayToQVector<Message>(response.object().value("result").toArray()));
    else
    {
        emit errorOccured(Error(response.object()));
        return QVector<Message>();
    }
}

Telegram::Message Telegram::Bot::sendLocation(const std::variant<qint32, QString>& chat_id, const float& latitude, const float& longitude, const std::optional<float>& horizontal_accuracy, const std::optional<qint32>& live_period, const std::optional<qint32>& heading, const std::optional<qint32>& proximity_alert_radius, const std::optional<bool>& disable_notification, const std::optional<qint32>& reply_to_message_id, const std::optional<bool>& allow_sending_without_reply, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup)
{
    /* Creating request body in JSON and filling it with request parameters */
    QJsonObject requestBody{ {"latitude", latitude}, {"longitude", longitude} };

    if (std::holds_alternative<qint32>(chat_id))       requestBody.insert("chat_id", std::get<qint32>(chat_id));
    else if (std::holds_alternative<QString>(chat_id)) requestBody.insert("chat_id", std::get<QString>(chat_id));

    if (horizontal_accuracy.has_value())         requestBody.insert("horizontal_accuracy", *horizontal_accuracy);
    if (live_period.has_value())                 requestBody.insert("live_period", *live_period);
    if (heading.has_value())                     requestBody.insert("heading", *heading);
    if (proximity_alert_radius.has_value())      requestBody.insert("proximity_alert_radius", *proximity_alert_radius);
    if (disable_notification.has_value())        requestBody.insert("disable_notification", *disable_notification);
    if (reply_to_message_id.has_value())         requestBody.insert("reply_to_message_id", *reply_to_message_id);
    if (allow_sending_without_reply.has_value()) requestBody.insert("allow_sending_without_reply", *allow_sending_without_reply);

    if (reply_markup.has_value())
    {
        if (std::holds_alternative<InlineKeyboardMarkup>(*reply_markup))      requestBody.insert("reply_markup", std::get<InlineKeyboardMarkup>(*reply_markup).toObject());
        else if (std::holds_alternative<ReplyKeyboardMarkup>(*reply_markup))  requestBody.insert("reply_markup", std::get<ReplyKeyboardMarkup>(*reply_markup).toObject());
        else if (std::holds_alternative<ReplyKeyboardRemove>(*reply_markup))  requestBody.insert("reply_markup", std::get<ReplyKeyboardRemove>(*reply_markup).toObject());
        else if (std::holds_alternative<ForceReply>(*reply_markup))           requestBody.insert("reply_markup", std::get<ForceReply>(*reply_markup).toObject());
    }

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(QJsonDocument(requestBody), QString("https://api.telegram.org/bot%1/sendLocation").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return empty object */
    if (response.object().value("ok").toBool() == true)
        return Message(response.object().value("result").toObject());
    else
    {
        emit errorOccured(Error(response.object()));
        return Message();
    }
}

Telegram::Message Telegram::Bot::editMessageLiveLocation(const float& latitude, const float& longitude, const std::optional<std::variant<qint32, QString>>& chat_id, const std::optional<qint32>& message_id, const std::optional<QString>& inline_message_id, const std::optional<float>& horizontal_accuracy, const std::optional<qint32>& heading, const std::optional<qint32>& proximity_alert_radius, const std::optional<InlineKeyboardMarkup>& reply_markup)
{
    /* Creating request body in JSON and filling it with request parameters */
    QJsonObject requestBody{ {"latitude", latitude}, {"longitude", longitude} };

    if (chat_id.has_value())
    {
        if (std::holds_alternative<qint32>(*chat_id))  requestBody.insert("chat_id", std::get<qint32>(*chat_id));
        else if (std::holds_alternative<QString>(*chat_id)) requestBody.insert("chat_id", std::get<QString>(*chat_id));
    }

    if (message_id.has_value())             requestBody.insert("message_id", *message_id);
    if (inline_message_id.has_value())      requestBody.insert("inline_message_id", *inline_message_id);
    if (horizontal_accuracy.has_value())    requestBody.insert("horizontal_accuracy", *horizontal_accuracy);
    if (heading.has_value())                requestBody.insert("heading", *heading);
    if (proximity_alert_radius.has_value()) requestBody.insert("proximity_alert_radius", *proximity_alert_radius);
    if (reply_markup.has_value())           requestBody.insert("reply_markup", reply_markup->toObject());

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(QJsonDocument(requestBody), QString("https://api.telegram.org/bot%1/editMessageLiveLocation").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return empty object */
    if (response.object().value("ok").toBool() == true)
        return Message(response.object().value("result").toObject());
    else
    {
        emit errorOccured(Error(response.object()));
        return Message();
    }
}

Telegram::Message Telegram::Bot::stopMessageLiveLocation(const std::optional<std::variant<qint32, QString>>& chat_id, const std::optional<qint32>& message_id, const std::optional<QString>& inline_message_id, const std::optional<InlineKeyboardMarkup>& reply_markup)
{
    /* Creating request body in JSON and filling it with request parameters */
    QJsonObject requestBody;

    if (std::holds_alternative<qint32>(*chat_id))       requestBody.insert("chat_id", std::get<qint32>(*chat_id));
    else if (std::holds_alternative<QString>(*chat_id)) requestBody.insert("chat_id", std::get<QString>(*chat_id));
    
    if (message_id.has_value())        requestBody.insert("message_id", *message_id);
    if (inline_message_id.has_value()) requestBody.insert("inline_message_id", *inline_message_id);
    if (reply_markup.has_value())      requestBody.insert("reply_markup", reply_markup->toObject());

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(QJsonDocument(requestBody), QString("https://api.telegram.org/bot%1/stopMessageLiveLocation").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return empty object */
    if (response.object().value("ok").toBool() == true)
        return Message(response.object().value("result").toObject());
    else
    {
        emit errorOccured(Error(response.object()));
        return Message();
    }
}

Telegram::Message Telegram::Bot::sendVenue(const std::variant<qint32, QString>& chat_id, const float& latitude, const float& longitude, const QString& title, const QString& address, const std::optional<QString>& foursquare_id, const std::optional<QString>& foursquare_type, const std::optional<QString>& google_place_id, const std::optional<QString>& google_place_type, const std::optional<bool>& disable_notification, const std::optional<qint32>& reply_to_message_id, const std::optional<bool>& allow_sending_without_reply, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup)
{
    /* Creating request body in JSON and filling it with request parameters */
    QJsonObject requestBody{ {"latitude", latitude}, {"longitude", longitude}, {"title", title}, {"address", address} };

    if (std::holds_alternative<qint32>(chat_id))       requestBody.insert("chat_id", std::get<qint32>(chat_id));
    else if (std::holds_alternative<QString>(chat_id)) requestBody.insert("chat_id", std::get<QString>(chat_id));

    if (foursquare_id.has_value())               requestBody.insert("foursquare_id", *foursquare_id);
    if (foursquare_type.has_value())             requestBody.insert("foursquare_type", *foursquare_type);
    if (google_place_id.has_value())             requestBody.insert("google_place_id", *google_place_id);
    if (google_place_type.has_value())           requestBody.insert("google_place_type", *google_place_type);
    if (disable_notification.has_value())        requestBody.insert("disable_notification", *disable_notification);
    if (reply_to_message_id.has_value())         requestBody.insert("reply_to_message_id", *reply_to_message_id);
    if (allow_sending_without_reply.has_value()) requestBody.insert("allow_sending_without_reply", *allow_sending_without_reply);

    if (reply_markup.has_value())
    {
        if (std::holds_alternative<InlineKeyboardMarkup>(*reply_markup))      requestBody.insert("reply_markup", std::get<InlineKeyboardMarkup>(*reply_markup).toObject());
        else if (std::holds_alternative<ReplyKeyboardMarkup>(*reply_markup))  requestBody.insert("reply_markup", std::get<ReplyKeyboardMarkup>(*reply_markup).toObject());
        else if (std::holds_alternative<ReplyKeyboardRemove>(*reply_markup))  requestBody.insert("reply_markup", std::get<ReplyKeyboardRemove>(*reply_markup).toObject());
        else if (std::holds_alternative<ForceReply>(*reply_markup))           requestBody.insert("reply_markup", std::get<ForceReply>(*reply_markup).toObject());
    }

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(QJsonDocument(requestBody), QString("https://api.telegram.org/bot%1/sendVenue").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return empty object */
    if (response.object().value("ok").toBool() == true)
        return Message(response.object().value("result").toObject());
    else
    {
        emit errorOccured(Error(response.object()));
        return Message();
    }
}

Telegram::Message Telegram::Bot::sendContact(const std::variant<qint32, QString>& chat_id, const QString& phone_number, const QString& first_name, const std::optional<QString>& last_name, const std::optional<QString>& vcard, const std::optional<bool>& disable_notification, const std::optional<qint32>& reply_to_message_id, const std::optional<bool>& allow_sending_without_reply, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup)
{
    /* Creating request body in JSON and filling it with request parameters */
    QJsonObject requestBody{ {"phone_number", phone_number}, {"first_name", first_name} };

    if (std::holds_alternative<qint32>(chat_id))       requestBody.insert("chat_id", std::get<qint32>(chat_id));
    else if (std::holds_alternative<QString>(chat_id)) requestBody.insert("chat_id", std::get<QString>(chat_id));

    if (last_name.has_value())                   requestBody.insert("last_name", *last_name);
    if (vcard.has_value())                       requestBody.insert("vcard", *vcard);
    if (disable_notification.has_value())        requestBody.insert("disable_notification", *disable_notification);
    if (reply_to_message_id.has_value())         requestBody.insert("reply_to_message_id", *reply_to_message_id);
    if (allow_sending_without_reply.has_value()) requestBody.insert("allow_sending_without_reply", *allow_sending_without_reply);

    if (reply_markup.has_value())
    {
        if (std::holds_alternative<InlineKeyboardMarkup>(*reply_markup))      requestBody.insert("reply_markup", std::get<InlineKeyboardMarkup>(*reply_markup).toObject());
        else if (std::holds_alternative<ReplyKeyboardMarkup>(*reply_markup))  requestBody.insert("reply_markup", std::get<ReplyKeyboardMarkup>(*reply_markup).toObject());
        else if (std::holds_alternative<ReplyKeyboardRemove>(*reply_markup))  requestBody.insert("reply_markup", std::get<ReplyKeyboardRemove>(*reply_markup).toObject());
        else if (std::holds_alternative<ForceReply>(*reply_markup))           requestBody.insert("reply_markup", std::get<ForceReply>(*reply_markup).toObject());
    }

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(QJsonDocument(requestBody), QString("https://api.telegram.org/bot%1/sendContact").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return empty object */
    if (response.object().value("ok").toBool() == true)
        return Message(response.object().value("result").toObject());
    else
    {
        emit errorOccured(Error(response.object()));
        return Message();
    }
}

Telegram::Message Telegram::Bot::sendPoll(const std::variant<qint32, QString>& chat_id, const QString& question, const QVector<QString>& options, const std::optional<bool>& is_anonymous, const std::optional<QString>& type, const std::optional<bool>& allows_multiple_answers, const std::optional<qint32>& correct_option_id, const std::optional<QString>& explanation, const std::optional<QString>& explanation_parse_mode, const std::optional<QVector<MessageEntity>>& explanation_entities, const std::optional<qint32>& open_period, const std::optional<qint32>& close_date, const std::optional<bool>& is_closed, const std::optional<bool>& disable_notification, const std::optional<qint32>& reply_to_message_id, const std::optional<bool>& allow_sending_without_reply, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup)
{
    /* Creating request body in JSON and filling it with request parameters */
    QJsonObject requestBody{ {"question", question}, {"options", QVectorToQJsonArray(options)} };

    if (std::holds_alternative<qint32>(chat_id))       requestBody.insert("chat_id", std::get<qint32>(chat_id));
    else if (std::holds_alternative<QString>(chat_id)) requestBody.insert("chat_id", std::get<QString>(chat_id));

    if (is_anonymous.has_value())                requestBody.insert("is_anonymous", *is_anonymous);
    if (type.has_value())                        requestBody.insert("type", *type);
    if (allows_multiple_answers.has_value())     requestBody.insert("allows_multiple_answers", *allows_multiple_answers);
    if (correct_option_id.has_value())           requestBody.insert("correct_option_id", *correct_option_id);
    if (explanation.has_value())                 requestBody.insert("explanation", *explanation);
    if (explanation_parse_mode.has_value())      requestBody.insert("explanation_parse_mode", *explanation_parse_mode);
    if (explanation_entities.has_value())        requestBody.insert("explanation_entities", QVectorToQJsonArray(*explanation_entities));
    if (open_period.has_value())                 requestBody.insert("open_period", *open_period);
    if (close_date.has_value())                  requestBody.insert("close_date", *close_date);
    if (is_closed.has_value())                   requestBody.insert("is_closed", *is_closed);
    if (disable_notification.has_value())        requestBody.insert("disable_notification", *disable_notification);
    if (reply_to_message_id.has_value())         requestBody.insert("reply_to_message_id", *reply_to_message_id);
    if (allow_sending_without_reply.has_value()) requestBody.insert("allow_sending_without_reply", *allow_sending_without_reply);

    if (reply_markup.has_value())
    {
        if (std::holds_alternative<InlineKeyboardMarkup>(*reply_markup))      requestBody.insert("reply_markup", std::get<InlineKeyboardMarkup>(*reply_markup).toObject());
        else if (std::holds_alternative<ReplyKeyboardMarkup>(*reply_markup))  requestBody.insert("reply_markup", std::get<ReplyKeyboardMarkup>(*reply_markup).toObject());
        else if (std::holds_alternative<ReplyKeyboardRemove>(*reply_markup))  requestBody.insert("reply_markup", std::get<ReplyKeyboardRemove>(*reply_markup).toObject());
        else if (std::holds_alternative<ForceReply>(*reply_markup))           requestBody.insert("reply_markup", std::get<ForceReply>(*reply_markup).toObject());
    }

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(QJsonDocument(requestBody), QString("https://api.telegram.org/bot%1/sendPoll").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return empty object */
    if (response.object().value("ok").toBool() == true)
        return Message(response.object().value("result").toObject());
    else
    {
        emit errorOccured(Error(response.object()));
        return Message();
    }
}

Telegram::Message Telegram::Bot::sendDice(const std::variant<qint32, QString>& chat_id, const std::optional<QString>& emoji, const std::optional<bool>& disable_notification, const std::optional<qint32>& reply_to_message_id, const std::optional<bool>& allow_sending_without_reply, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup)
{
    /* Creating request body in JSON and filling it with request parameters */
    QJsonObject requestBody;

    if (std::holds_alternative<qint32>(chat_id))       requestBody.insert("chat_id", std::get<qint32>(chat_id));
    else if (std::holds_alternative<QString>(chat_id)) requestBody.insert("chat_id", std::get<QString>(chat_id));

    if (emoji.has_value())                       requestBody.insert("emoji", *emoji);
    if (disable_notification.has_value())        requestBody.insert("disable_notification", *disable_notification);
    if (reply_to_message_id.has_value())         requestBody.insert("reply_to_message_id", *reply_to_message_id);
    if (allow_sending_without_reply.has_value()) requestBody.insert("allow_sending_without_reply", *allow_sending_without_reply);

    if (reply_markup.has_value())
    {
        if (std::holds_alternative<InlineKeyboardMarkup>(*reply_markup))      requestBody.insert("reply_markup", std::get<InlineKeyboardMarkup>(*reply_markup).toObject());
        else if (std::holds_alternative<ReplyKeyboardMarkup>(*reply_markup))  requestBody.insert("reply_markup", std::get<ReplyKeyboardMarkup>(*reply_markup).toObject());
        else if (std::holds_alternative<ReplyKeyboardRemove>(*reply_markup))  requestBody.insert("reply_markup", std::get<ReplyKeyboardRemove>(*reply_markup).toObject());
        else if (std::holds_alternative<ForceReply>(*reply_markup))           requestBody.insert("reply_markup", std::get<ForceReply>(*reply_markup).toObject());
    }

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(QJsonDocument(requestBody), QString("https://api.telegram.org/bot%1/sendDice").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return empty object */
    if (response.object().value("ok").toBool() == true)
        return Message(response.object().value("result").toObject());
    else
    {
        emit errorOccured(Error(response.object()));
        return Message();
    }
}

bool Telegram::Bot::sendChatAction(const std::variant<qint32, QString>& chat_id, const ChatActionType& action)
{
    auto ChatActionTypeToString = [](const ChatActionType& action) -> QString
                                    {
                                        if (action == ChatActionType::TYPING)            return "typing";
                                        if (action == ChatActionType::UPLOAD_PHOTO)      return "upload_photo";
                                        if (action == ChatActionType::RECORD_VIDEO)      return "record_video";
                                        if (action == ChatActionType::UPLOAD_VIDEO)      return "upload_video";
                                        if (action == ChatActionType::RECORD_VOICE)      return "record_voice";
                                        if (action == ChatActionType::UPLOAD_VOICE)      return "upload_voice";
                                        if (action == ChatActionType::UPLOAD_DOCUMENT)   return "upload_document";
                                        if (action == ChatActionType::FIND_LOCATION)     return "find_location";
                                        if (action == ChatActionType::RECORD_VIDEO_NOTE) return "record_video_note";
                                        if (action == ChatActionType::UPLOAD_VIDEO_NOTE) return "upload_video_note";
                                        else return "";
                                    };

    /* Creating request body in JSON and filling it with request parameters */
    QJsonObject requestBody{ {"action", ChatActionTypeToString(action)} };

    if (std::holds_alternative<qint32>(chat_id))       requestBody.insert("chat_id", std::get<qint32>(chat_id));
    else if (std::holds_alternative<QString>(chat_id)) requestBody.insert("chat_id", std::get<QString>(chat_id));

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(QJsonDocument(requestBody), QString("https://api.telegram.org/bot%1/sendChatAction").arg(BOT_TOKEN)));

    if (response.object().value("ok").toBool())
        return true;
    else
    {
        emit errorOccured(Error(response.object()));
        return false;
    }
}

Telegram::UserProfilePhotos Telegram::Bot::getUserProfilePhotos(const qint32& user_id, const std::optional<qint32>& offset, const std::optional<qint32>& limit)
{
    /* Creating request body in JSON and filling it with request parameters */
    QJsonObject requestBody{ {"user_id", user_id} };

    if (offset.has_value()) requestBody.insert("offset", *offset);
    if (limit.has_value())  requestBody.insert("limit", *limit);

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(QJsonDocument(requestBody), QString("https://api.telegram.org/bot%1/getUserProfilePhotos").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return empty object */
    if (response.object().value("ok").toBool() == true)
        return UserProfilePhotos(response.object().value("result").toObject());
    else
    {
        emit errorOccured(Error(response.object()));
        return UserProfilePhotos();
    }
}

Telegram::File Telegram::Bot::getFile(const QString& file_id)
{
    /* Creating request body in JSON and filling it with request parameters */
    QJsonObject requestBody{ {"file_id", file_id} };

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(QJsonDocument(requestBody), QString("https://api.telegram.org/bot%1/getFile").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return empty object */
    if (response.object().value("ok").toBool() == true)
        return File(response.object().value("result").toObject());
    else
    {
        emit errorOccured(Error(response.object()));
        return File();
    }
}

bool Telegram::Bot::banChatMember(const std::variant<qint32, QString>& chat_id, const qint32& user_id, const std::optional<qint32>& until_date, const std::optional<bool>& revoke_messages)
{
    /* Creating request body in JSON and filling it with request parameters */
    QJsonObject requestBody{ {"user_id", user_id} };

    if (std::holds_alternative<qint32>(chat_id))       requestBody.insert("chat_id", std::get<qint32>(chat_id));
    else if (std::holds_alternative<QString>(chat_id)) requestBody.insert("chat_id", std::get<QString>(chat_id));

    if (until_date.has_value())      requestBody.insert("until_date", *until_date);
    if (revoke_messages.has_value()) requestBody.insert("revoke_messages", *revoke_messages);

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(QJsonDocument(requestBody), QString("https://api.telegram.org/bot%1/banChatMember").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return false */
    if (response.object().value("ok").toBool())
        return true;
    else
    {
        emit errorOccured(Error(response.object()));
        return false;
    }
}

bool Telegram::Bot::unbanChatMember(const std::variant<qint32, QString>& chat_id, const qint32& user_id, const std::optional<bool>& only_if_banned)
{
    /* Creating request body in JSON and filling it with request parameters */
    QJsonObject requestBody{ {"user_id", user_id} };

    if (std::holds_alternative<qint32>(chat_id))       requestBody.insert("chat_id", std::get<qint32>(chat_id));
    else if (std::holds_alternative<QString>(chat_id)) requestBody.insert("chat_id", std::get<QString>(chat_id));

    if (only_if_banned.has_value())      requestBody.insert("only_if_banned", *only_if_banned);

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(QJsonDocument(requestBody), QString("https://api.telegram.org/bot%1/unbanChatMember").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return false */
    if (response.object().value("ok").toBool())
        return true;
    else
    {
        emit errorOccured(Error(response.object()));
        return false;
    }
}

bool Telegram::Bot::restrictChatMember(const std::variant<qint32, QString>& chat_id, const qint32& user_id, const ChatPermissions& permissions, const std::optional<qint32>& until_date)
{
    /* Creating request body in JSON and filling it with request parameters */
    QJsonObject requestBody{ {"user_id", user_id}, {"permissions", permissions.toObject()} };

    if (std::holds_alternative<qint32>(chat_id))       requestBody.insert("chat_id", std::get<qint32>(chat_id));
    else if (std::holds_alternative<QString>(chat_id)) requestBody.insert("chat_id", std::get<QString>(chat_id));

    if (until_date.has_value()) requestBody.insert("until_date", *until_date);

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(QJsonDocument(requestBody), QString("https://api.telegram.org/bot%1/restrictChatMember").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return false */
    if (response.object().value("ok").toBool())
        return true;
    else
    {
        emit errorOccured(Error(response.object()));
        return false;
    }
}

bool Telegram::Bot::promoteChatMember(const std::variant<qint32, QString>& chat_id, const qint32& user_id, const std::optional<bool>& is_anonymous, const std::optional<bool>& can_manage_chat, const std::optional<bool>& can_post_messages, const std::optional<bool>& can_edit_messages, const std::optional<bool>& can_delete_messages, const std::optional<bool>& can_manage_voice_chats, const std::optional<bool>& can_restrict_members, const std::optional<bool>& can_promote_members, const std::optional<bool>& can_change_info, const std::optional<bool>& can_invite_users, const std::optional<bool>& can_pin_messages)
{
    /* Creating request body in JSON and filling it with request parameters */
    QJsonObject requestBody{ {"user_id", user_id} };

    if (std::holds_alternative<qint32>(chat_id))       requestBody.insert("chat_id", std::get<qint32>(chat_id));
    else if (std::holds_alternative<QString>(chat_id)) requestBody.insert("chat_id", std::get<QString>(chat_id));

    if (is_anonymous.has_value())           requestBody.insert("is_anonymous", *is_anonymous);
    if (can_manage_chat.has_value())        requestBody.insert("can_manage_chat", *can_manage_chat);
    if (can_post_messages.has_value())      requestBody.insert("can_post_messages", *can_post_messages);
    if (can_edit_messages.has_value())      requestBody.insert("can_edit_messages", *can_edit_messages);
    if (can_delete_messages.has_value())    requestBody.insert("can_delete_messages", *can_delete_messages);
    if (can_manage_voice_chats.has_value()) requestBody.insert("can_manage_voice_chats", *can_manage_voice_chats);
    if (can_restrict_members.has_value())   requestBody.insert("can_restrict_members", *can_restrict_members);
    if (can_promote_members.has_value())    requestBody.insert("can_promote_members", *can_promote_members);
    if (can_change_info.has_value())        requestBody.insert("can_change_info", *can_change_info);
    if (can_invite_users.has_value())       requestBody.insert("can_invite_users", *can_invite_users);
    if (can_pin_messages.has_value())       requestBody.insert("can_pin_messages", *can_pin_messages);

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(QJsonDocument(requestBody), QString("https://api.telegram.org/bot%1/promoteChatMember").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return false */
    if (response.object().value("ok").toBool())
        return true;
    else
    {
        emit errorOccured(Error(response.object()));
        return false;
    }
}

bool Telegram::Bot::setChatAdministratorCustomTitle(const std::variant<qint32, QString>& chat_id, const qint32& user_id, const QString& custom_title)
{
    /* Creating request body in JSON and filling it with request parameters */
    QJsonObject requestBody{ {"user_id", user_id}, {"custom_title", custom_title} };

    if (std::holds_alternative<qint32>(chat_id))       requestBody.insert("chat_id", std::get<qint32>(chat_id));
    else if (std::holds_alternative<QString>(chat_id)) requestBody.insert("chat_id", std::get<QString>(chat_id));

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(QJsonDocument(requestBody), QString("https://api.telegram.org/bot%1/setChatAdministratorCustomTitle").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return false */
    if (response.object().value("ok").toBool())
        return true;
    else
    {
        emit errorOccured(Error(response.object()));
        return false;
    }
}

bool Telegram::Bot::setChatPermissions(const std::variant<qint32, QString>& chat_id, const ChatPermissions& permissions)
{
    /* Creating request body in JSON and filling it with request parameters */
    QJsonObject requestBody{ {"permissions", permissions.toObject()} };

    if (std::holds_alternative<qint32>(chat_id))       requestBody.insert("chat_id", std::get<qint32>(chat_id));
    else if (std::holds_alternative<QString>(chat_id)) requestBody.insert("chat_id", std::get<QString>(chat_id));

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(QJsonDocument(requestBody), QString("https://api.telegram.org/bot%1/setChatPermissions").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return false */
    if (response.object().value("ok").toBool())
        return true;
    else
    {
        emit errorOccured(Error(response.object()));
        return false;
    }
}

QString Telegram::Bot::exportChatInviteLink(const std::variant<qint32, QString>& chat_id)
{
    /* Creating request body in JSON and filling it with request parameters */
    QJsonObject requestBody;

    if (std::holds_alternative<qint32>(chat_id))       requestBody.insert("chat_id", std::get<qint32>(chat_id));
    else if (std::holds_alternative<QString>(chat_id)) requestBody.insert("chat_id", std::get<QString>(chat_id));

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(QJsonDocument(requestBody), QString("https://api.telegram.org/bot%1/exportChatInviteLink").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return empty object */
    if (response.object().value("ok").toBool() == true)
        return response.object().value("result").toString();
    else
    {
        emit errorOccured(Error(response.object()));
        return QString();
    }
}

Telegram::ChatInviteLink Telegram::Bot::createChatInviteLink(const std::variant<qint32, QString>& chat_id, const std::optional<qint32>& expire_date, const std::optional<qint32>& member_limit)
{
    /* Creating request body in JSON and filling it with request parameters */
    QJsonObject requestBody;

    if (std::holds_alternative<qint32>(chat_id))       requestBody.insert("chat_id", std::get<qint32>(chat_id));
    else if (std::holds_alternative<QString>(chat_id)) requestBody.insert("chat_id", std::get<QString>(chat_id));

    if (expire_date.has_value())  requestBody.insert("expire_date", *expire_date);
    if (member_limit.has_value()) requestBody.insert("member_limit", *member_limit);

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(QJsonDocument(requestBody), QString("https://api.telegram.org/bot%1/createChatInviteLink").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return empty object */
    if (response.object().value("ok").toBool() == true)
        return ChatInviteLink(response.object().value("result").toObject());
    else
    {
        emit errorOccured(Error(response.object()));
        return ChatInviteLink();
    }
}

Telegram::ChatInviteLink Telegram::Bot::editChatInviteLink(const std::variant<qint32, QString>& chat_id, const QString& invite_link, const std::optional<qint32>& expire_date, const std::optional<qint32>& member_limit)
{
    /* Creating request body in JSON and filling it with request parameters */
    QJsonObject requestBody{ {"invite_link", invite_link} };

    if (std::holds_alternative<qint32>(chat_id))       requestBody.insert("chat_id", std::get<qint32>(chat_id));
    else if (std::holds_alternative<QString>(chat_id)) requestBody.insert("chat_id", std::get<QString>(chat_id));

    if (expire_date.has_value())  requestBody.insert("expire_date", *expire_date);
    if (member_limit.has_value()) requestBody.insert("member_limit", *member_limit);

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(QJsonDocument(requestBody), QString("https://api.telegram.org/bot%1/editChatInviteLink").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return empty object */
    if (response.object().value("ok").toBool() == true)
        return ChatInviteLink(response.object().value("result").toObject());
    else
    {
        emit errorOccured(Error(response.object()));
        return ChatInviteLink();
    }
}

Telegram::ChatInviteLink Telegram::Bot::revokeChatInviteLink(const std::variant<qint32, QString>& chat_id, const QString& invite_link)
{
    /* Creating request body in JSON and filling it with request parameters */
    QJsonObject requestBody{ {"invite_link", invite_link} };

    if (std::holds_alternative<qint32>(chat_id))       requestBody.insert("chat_id", std::get<qint32>(chat_id));
    else if (std::holds_alternative<QString>(chat_id)) requestBody.insert("chat_id", std::get<QString>(chat_id));

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(QJsonDocument(requestBody), QString("https://api.telegram.org/bot%1/revokeChatInviteLink").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return empty object */
    if (response.object().value("ok").toBool() == true)
        return ChatInviteLink(response.object().value("result").toObject());
    else
    {
        emit errorOccured(Error(response.object()));
        return ChatInviteLink();
    }
}

bool Telegram::Bot::setChatPhoto(const std::variant<qint32, QString>& chat_id, const QFile* photo)
{
    /* Preparing request body */
    QVector<QPair<QString, QVariant>> requestParameters;

    if (std::holds_alternative<qint32>(chat_id))       requestParameters.push_back(QPair<QString, QVariant>("chat_id", std::get<qint32>(chat_id)));
    else if (std::holds_alternative<QString>(chat_id)) requestParameters.push_back(QPair<QString, QVariant>("chat_id", std::get<QString>(chat_id)));

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest({ {"photo", const_cast<QFile*>(photo)} }, requestParameters, QString("https://api.telegram.org/bot%1/setChatPhoto").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return empty object */
    if (response.object().value("ok").toBool())
        return true;
    else
    {
        emit errorOccured(Error(response.object()));
        return false;
    }
}

bool Telegram::Bot::deleteChatPhoto(const std::variant<qint32, QString>& chat_id)
{
    /* Creating request body in JSON and filling it with request parameters */
    QJsonObject requestBody;

    if (std::holds_alternative<qint32>(chat_id))       requestBody.insert("chat_id", std::get<qint32>(chat_id));
    else if (std::holds_alternative<QString>(chat_id)) requestBody.insert("chat_id", std::get<QString>(chat_id));

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(QJsonDocument(requestBody), QString("https://api.telegram.org/bot%1/deleteChatPhoto").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return false */
    if (response.object().value("ok").toBool())
        return true;
    else
    {
        emit errorOccured(Error(response.object()));
        return false;
    }
}

bool Telegram::Bot::setChatTitle(const std::variant<qint32, QString>& chat_id, const QString& title)
{
    /* Creating request body in JSON and filling it with request parameters */
    QJsonObject requestBody{ {"title", title} };

    if (std::holds_alternative<qint32>(chat_id))       requestBody.insert("chat_id", std::get<qint32>(chat_id));
    else if (std::holds_alternative<QString>(chat_id)) requestBody.insert("chat_id", std::get<QString>(chat_id));

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(QJsonDocument(requestBody), QString("https://api.telegram.org/bot%1/setChatTitle").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return false */
    if (response.object().value("ok").toBool())
        return true;
    else
    {
        emit errorOccured(Error(response.object()));
        return false;
    }
}

bool Telegram::Bot::setChatDescription(const std::variant<qint32, QString>& chat_id, const std::optional<QString>& description)
{
    /* Creating request body in JSON and filling it with request parameters */
    QJsonObject requestBody;

    if (std::holds_alternative<qint32>(chat_id))       requestBody.insert("chat_id", std::get<qint32>(chat_id));
    else if (std::holds_alternative<QString>(chat_id)) requestBody.insert("chat_id", std::get<QString>(chat_id));

    if(description.has_value()) requestBody.insert("description", *description);

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(QJsonDocument(requestBody), QString("https://api.telegram.org/bot%1/setChatDescription").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return false */
    if (response.object().value("ok").toBool())
        return true;
    else
    {
        emit errorOccured(Error(response.object()));
        return false;
    }
}

bool Telegram::Bot::pinChatMessage(const std::variant<qint32, QString>& chat_id, const qint32& message_id, const std::optional<bool>& disable_notification)
{
    /* Creating request body in JSON and filling it with request parameters */
    QJsonObject requestBody{ {"message_id", message_id} };

    if (std::holds_alternative<qint32>(chat_id))       requestBody.insert("chat_id", std::get<qint32>(chat_id));
    else if (std::holds_alternative<QString>(chat_id)) requestBody.insert("chat_id", std::get<QString>(chat_id));

    if (disable_notification.has_value()) requestBody.insert("disable_notification", *disable_notification);

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(QJsonDocument(requestBody), QString("https://api.telegram.org/bot%1/pinChatMessage").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return false */
    if (response.object().value("ok").toBool())
        return true;
    else
    {
        emit errorOccured(Error(response.object()));
        return false;
    }
}

bool Telegram::Bot::unpinChatMessage(const std::variant<qint32, QString>& chat_id, const std::optional<qint32>& message_id)
{
    /* Creating request body in JSON and filling it with request parameters */
    QJsonObject requestBody;

    if (std::holds_alternative<qint32>(chat_id))       requestBody.insert("chat_id", std::get<qint32>(chat_id));
    else if (std::holds_alternative<QString>(chat_id)) requestBody.insert("chat_id", std::get<QString>(chat_id));

    if (message_id.has_value()) requestBody.insert("message_id", *message_id);

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(QJsonDocument(requestBody), QString("https://api.telegram.org/bot%1/unpinChatMessage").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return false */
    if (response.object().value("ok").toBool())
        return true;
    else
    {
        emit errorOccured(Error(response.object()));
        return false;
    }
}

bool Telegram::Bot::unpinAllChatMessages(const std::variant<qint32, QString>& chat_id)
{
    /* Creating request body in JSON and filling it with request parameters */
    QJsonObject requestBody;

    if (std::holds_alternative<qint32>(chat_id))       requestBody.insert("chat_id", std::get<qint32>(chat_id));
    else if (std::holds_alternative<QString>(chat_id)) requestBody.insert("chat_id", std::get<QString>(chat_id));

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(QJsonDocument(requestBody), QString("https://api.telegram.org/bot%1/unpinAllChatMessages").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return false */
    if (response.object().value("ok").toBool())
        return true;
    else
    {
        emit errorOccured(Error(response.object()));
        return false;
    }
}

bool Telegram::Bot::leaveChat(const std::variant<qint32, QString>& chat_id)
{
    /* Creating request body in JSON and filling it with request parameters */
    QJsonObject requestBody;

    if (std::holds_alternative<qint32>(chat_id))       requestBody.insert("chat_id", std::get<qint32>(chat_id));
    else if (std::holds_alternative<QString>(chat_id)) requestBody.insert("chat_id", std::get<QString>(chat_id));

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(QJsonDocument(requestBody), QString("https://api.telegram.org/bot%1/leaveChat").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return false */
    if (response.object().value("ok").toBool())
        return true;
    else
    {
        emit errorOccured(Error(response.object()));
        return false;
    }
}

Telegram::Chat Telegram::Bot::getChat(const std::variant<qint32, QString>& chat_id)
{
    /* Creating request body in JSON and filling it with request parameters */
    QJsonObject requestBody;

    if (std::holds_alternative<qint32>(chat_id))       requestBody.insert("chat_id", std::get<qint32>(chat_id));
    else if (std::holds_alternative<QString>(chat_id)) requestBody.insert("chat_id", std::get<QString>(chat_id));

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(QJsonDocument(requestBody), QString("https://api.telegram.org/bot%1/getChat").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return empty object */
    if (response.object().value("ok").toBool() == true)
        return Chat(response.object().value("result").toObject());
    else
    {
        emit errorOccured(Error(response.object()));
        return Chat();
    }
}

QVector<Telegram::ChatMember> Telegram::Bot::getChatAdministrators(const std::variant<qint32, QString>& chat_id)
{
    /* Creating request body in JSON and filling it with request parameters */
    QJsonObject requestBody;

    if (std::holds_alternative<qint32>(chat_id))       requestBody.insert("chat_id", std::get<qint32>(chat_id));
    else if (std::holds_alternative<QString>(chat_id)) requestBody.insert("chat_id", std::get<QString>(chat_id));

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(QJsonDocument(requestBody), QString("https://api.telegram.org/bot%1/getChatAdministrators").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return empty object */
    if (response.object().value("ok").toBool() == true)
        return QVector<ChatMember>(QJsonArrayToQVector<ChatMember>(response.object().value("result").toArray()));
    else
    {
        emit errorOccured(Error(response.object()));
        return QVector<ChatMember>();
    }
}

int Telegram::Bot::getChatMemberCount(const std::variant<qint32, QString>& chat_id)
{
    /* Creating request body in JSON and filling it with request parameters */
    QJsonObject requestBody;

    if (std::holds_alternative<qint32>(chat_id))       requestBody.insert("chat_id", std::get<qint32>(chat_id));
    else if (std::holds_alternative<QString>(chat_id)) requestBody.insert("chat_id", std::get<QString>(chat_id));

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(QJsonDocument(requestBody), QString("https://api.telegram.org/bot%1/getChatMemberCount").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return empty object */
    if (response.object().value("ok").toBool() == true)
        return response.object().value("result").toInt();
    else
    {
        emit errorOccured(Error(response.object()));
        return -1;
    }
}

Telegram::ChatMember Telegram::Bot::getChatMember(const std::variant<qint32, QString>& chat_id, const qint32& user_id)
{
    /* Creating request body in JSON and filling it with request parameters */
    QJsonObject requestBody{ {"user_id", user_id} };

    if (std::holds_alternative<qint32>(chat_id))       requestBody.insert("chat_id", std::get<qint32>(chat_id));
    else if (std::holds_alternative<QString>(chat_id)) requestBody.insert("chat_id", std::get<QString>(chat_id));

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(QJsonDocument(requestBody), QString("https://api.telegram.org/bot%1/getChatMember").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return empty object */
    if (response.object().value("ok").toBool() == true)
        return ChatMember(response.object().value("result").toObject());
    else
    {
        emit errorOccured(Error(response.object()));
        return ChatMember();
    }
}

bool Telegram::Bot::setChatStickerSet(const std::variant<qint32, QString>& chat_id, const QString& sticker_set_name)
{
    /* Creating request body in JSON and filling it with request parameters */
    QJsonObject requestBody{ {"sticker_set_name", sticker_set_name} };

    if (std::holds_alternative<qint32>(chat_id))       requestBody.insert("chat_id", std::get<qint32>(chat_id));
    else if (std::holds_alternative<QString>(chat_id)) requestBody.insert("chat_id", std::get<QString>(chat_id));

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(QJsonDocument(requestBody), QString("https://api.telegram.org/bot%1/setChatStickerSet").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return false */
    if (response.object().value("ok").toBool())
        return true;
    else
    {
        emit errorOccured(Error(response.object()));
        return false;
    }
}

bool Telegram::Bot::deleteChatStickerSet(const std::variant<qint32, QString>& chat_id)
{
    /* Creating request body in JSON and filling it with request parameters */
    QJsonObject requestBody;

    if (std::holds_alternative<qint32>(chat_id))       requestBody.insert("chat_id", std::get<qint32>(chat_id));
    else if (std::holds_alternative<QString>(chat_id)) requestBody.insert("chat_id", std::get<QString>(chat_id));

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(QJsonDocument(requestBody), QString("https://api.telegram.org/bot%1/deleteChatStickerSet").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return false */
    if (response.object().value("ok").toBool())
        return true;
    else
    {
        emit errorOccured(Error(response.object()));
        return false;
    }
}

bool Telegram::Bot::answerCallbackQuery(const QString& callback_query_id, const std::optional<QString>& text, const std::optional<bool>& show_alert, const std::optional<QString>& url, const std::optional<qint32>& cache_time)
{
    /* Creating request body in JSON and filling it with request parameters */
    QJsonObject requestBody{ {"callback_query_id", callback_query_id} };

    if (text.has_value())       requestBody.insert("text", *text);
    if (show_alert.has_value()) requestBody.insert("show_alert", *show_alert);
    if (url.has_value())        requestBody.insert("url", *url);
    if (cache_time.has_value()) requestBody.insert("cache_time", *cache_time);

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(QJsonDocument(requestBody), QString("https://api.telegram.org/bot%1/answerCallbackQuery").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return false */
    if (response.object().value("ok").toBool())
        return true;
    else
    {
        emit errorOccured(Error(response.object()));
        return false;
    }
}

bool Telegram::Bot::setMyCommands(const QVector<BotCommand>& commands, const std::optional<std::variant<BotCommandScopeAllChatAdministrators, BotCommandScopeAllGroupChats, BotCommandScopeAllPrivateChats, BotCommandScopeChat, BotCommandScopeChatAdministrators, BotCommandScopeChatMember, BotCommandScopeDefault>>& scope, const std::optional<QString>& language_code)
{
    /* Creating request body in JSON and filling it with request parameters */
    QJsonObject requestBody{ {"commands", QVectorToQJsonArray(commands)} };

    if (scope.has_value())
    {
        if (std::holds_alternative<BotCommandScopeAllChatAdministrators>(*scope))    requestBody.insert("scope", std::get<BotCommandScopeAllChatAdministrators>(*scope).toObject());
        else if (std::holds_alternative<BotCommandScopeAllGroupChats>(*scope))       requestBody.insert("scope", std::get<BotCommandScopeAllGroupChats>(*scope).toObject());
        else if (std::holds_alternative<BotCommandScopeAllPrivateChats>(*scope))     requestBody.insert("scope", std::get<BotCommandScopeAllPrivateChats>(*scope).toObject());
        else if (std::holds_alternative<BotCommandScopeChat>(*scope))                requestBody.insert("scope", std::get<BotCommandScopeChat>(*scope).toObject());
        else if (std::holds_alternative<BotCommandScopeChatAdministrators>(*scope))  requestBody.insert("scope", std::get<BotCommandScopeChatAdministrators>(*scope).toObject());
        else if (std::holds_alternative<BotCommandScopeChatMember>(*scope))          requestBody.insert("scope", std::get<BotCommandScopeChatMember>(*scope).toObject());
        else if (std::holds_alternative<BotCommandScopeDefault>(*scope))             requestBody.insert("scope", std::get<BotCommandScopeDefault>(*scope).toObject());
    }

    if (language_code.has_value()) requestBody.insert("language_code", *language_code);

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(QJsonDocument(requestBody), QString("https://api.telegram.org/bot%1/setMyCommands").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return false and emit errorOccured() signal */
    if (response.object().value("ok").toBool())
        return true;
    else
    {
        emit errorOccured(Error(response.object()));
        return false;
    }
    
}

bool Telegram::Bot::deleteMyCommands(const std::optional<std::variant<BotCommandScopeAllChatAdministrators, BotCommandScopeAllGroupChats, BotCommandScopeAllPrivateChats, BotCommandScopeChat, BotCommandScopeChatAdministrators, BotCommandScopeChatMember, BotCommandScopeDefault>>& scope, const std::optional<QString>& language_code)
{
    /* Creating request body in JSON and filling it with request parameters */
    QJsonObject requestBody;

    if (scope.has_value())
    {
        if (std::holds_alternative<BotCommandScopeAllChatAdministrators>(*scope))    requestBody.insert("scope", std::get<BotCommandScopeAllChatAdministrators>(*scope).toObject());
        else if (std::holds_alternative<BotCommandScopeAllGroupChats>(*scope))       requestBody.insert("scope", std::get<BotCommandScopeAllGroupChats>(*scope).toObject());
        else if (std::holds_alternative<BotCommandScopeAllPrivateChats>(*scope))     requestBody.insert("scope", std::get<BotCommandScopeAllPrivateChats>(*scope).toObject());
        else if (std::holds_alternative<BotCommandScopeChat>(*scope))                requestBody.insert("scope", std::get<BotCommandScopeChat>(*scope).toObject());
        else if (std::holds_alternative<BotCommandScopeChatAdministrators>(*scope))  requestBody.insert("scope", std::get<BotCommandScopeChatAdministrators>(*scope).toObject());
        else if (std::holds_alternative<BotCommandScopeChatMember>(*scope))          requestBody.insert("scope", std::get<BotCommandScopeChatMember>(*scope).toObject());
        else if (std::holds_alternative<BotCommandScopeDefault>(*scope))             requestBody.insert("scope", std::get<BotCommandScopeDefault>(*scope).toObject());
    }

    if (language_code.has_value()) requestBody.insert("language_code", *language_code);

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(QJsonDocument(requestBody), QString("https://api.telegram.org/bot%1/deleteMyCommands").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return false */
    if (response.object().value("ok").toBool())
        return true;
    else
    {
        emit errorOccured(Error(response.object()));
        return false;
    }
}

QVector<Telegram::BotCommand> Telegram::Bot::getMyCommands(const std::optional<std::variant<BotCommandScopeAllChatAdministrators, BotCommandScopeAllGroupChats, BotCommandScopeAllPrivateChats, BotCommandScopeChat, BotCommandScopeChatAdministrators, BotCommandScopeChatMember, BotCommandScopeDefault>>& scope, const std::optional<QString>& language_code)
{
    /* Creating request body in JSON and filling it with request parameters */
    QJsonObject requestBody;

    if (scope.has_value())
    {
        if (std::holds_alternative<BotCommandScopeAllChatAdministrators>(*scope))    requestBody.insert("scope", std::get<BotCommandScopeAllChatAdministrators>(*scope).toObject());
        else if (std::holds_alternative<BotCommandScopeAllGroupChats>(*scope))       requestBody.insert("scope", std::get<BotCommandScopeAllGroupChats>(*scope).toObject());
        else if (std::holds_alternative<BotCommandScopeAllPrivateChats>(*scope))     requestBody.insert("scope", std::get<BotCommandScopeAllPrivateChats>(*scope).toObject());
        else if (std::holds_alternative<BotCommandScopeChat>(*scope))                requestBody.insert("scope", std::get<BotCommandScopeChat>(*scope).toObject());
        else if (std::holds_alternative<BotCommandScopeChatAdministrators>(*scope))  requestBody.insert("scope", std::get<BotCommandScopeChatAdministrators>(*scope).toObject());
        else if (std::holds_alternative<BotCommandScopeChatMember>(*scope))          requestBody.insert("scope", std::get<BotCommandScopeChatMember>(*scope).toObject());
        else if (std::holds_alternative<BotCommandScopeDefault>(*scope))             requestBody.insert("scope", std::get<BotCommandScopeDefault>(*scope).toObject());
    }

    if (language_code.has_value()) requestBody.insert("language_code", *language_code);

    /* Sending request */
    QJsonDocument response = QJsonDocument::fromJson(requestManager.SendPostRequest(QJsonDocument(requestBody), QString("https://api.telegram.org/bot%1/getMyCommands").arg(BOT_TOKEN)));

    /* Check if request was successful. In case of error return empty object */
    if (response.object().value("ok").toBool() == true)
        return QVector<BotCommand>(QJsonArrayToQVector<BotCommand>(response.object().value("result").toArray()));
    else
    {
        emit errorOccured(Error(response.object()));
        return QVector<BotCommand>();
    }
}


