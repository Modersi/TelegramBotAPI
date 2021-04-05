#include "TelegramBotAPI.h"
#include "QFile"

TelegramAPI::TelegramAPI(const QString botToken)
{
    requestManager = new RequestManager(botToken);
}

User TelegramAPI::getMe()
{
    QJsonDocument requestResultJsonDocument = requestManager->sendRequest("getMe", QJsonDocument());

    if(requestResultJsonDocument.object().value("ok").toBool() == true)
        return User(requestResultJsonDocument.object().value("result").toObject());
    else
        return User();
}

Message TelegramAPI::sendMessage(qint32 chatId, QString text, QString parseMode, bool disableWebPagePreview, bool disableNotification, qint32 replyToMessageId)
{
    QJsonObject requestJsonObject;

    requestJsonObject.insert("chat_id", QJsonValue(chatId));
    requestJsonObject.insert("text", QJsonValue(text));
    requestJsonObject.insert("parse_mode", QJsonValue(parseMode));

    if(disableWebPagePreview != false)
        requestJsonObject.insert("disable_web_page_preview", QJsonValue(disableWebPagePreview));
    if(disableNotification != false)
        requestJsonObject.insert("disable_notification", QJsonValue(disableNotification));
    if(replyToMessageId != 0)
        requestJsonObject.insert("reply_to_message_id", QJsonValue(replyToMessageId));


    QJsonDocument requestResultJsonDocument = requestManager->sendRequest("sendMessage", QJsonDocument(requestJsonObject));

    if(requestResultJsonDocument.object().value("ok").toBool() == true)
        return Message(requestResultJsonDocument.object().value("result").toObject());
    else
        return Message();
}

Message TelegramAPI::sendMessage(QString chatId, QString text, QString parseMode, bool disableWebPagePreview, bool disableNotification, qint32 replyToMessageId)
{
    QJsonObject requestJsonObject;

    requestJsonObject.insert("chat_id", QJsonValue(chatId));
    requestJsonObject.insert("text", QJsonValue(text));
    requestJsonObject.insert("parse_mode", QJsonValue(parseMode));

    if(disableWebPagePreview != false)
        requestJsonObject.insert("disable_web_page_preview", QJsonValue(disableWebPagePreview));
    if(disableNotification != false)
        requestJsonObject.insert("disable_notification", QJsonValue(disableNotification));
    if(replyToMessageId != 0)
        requestJsonObject.insert("reply_to_message_id", QJsonValue(replyToMessageId));


    QJsonDocument requestResultJsonDocument = requestManager->sendRequest("sendMessage", QJsonDocument(requestJsonObject));

    if(requestResultJsonDocument.object().value("ok").toBool() == true)
        return Message(requestResultJsonDocument.object().value("result").toObject());
    else
        return Message();
}

Chat TelegramAPI::getChat(const QString chatId)
{
    QJsonObject requestJsonObject;

    requestJsonObject.insert("chat_id", QJsonValue(chatId));


    QJsonDocument requestResultJsonDocument = requestManager->sendRequest("getChat", QJsonDocument(requestJsonObject));
    QFile file("getChat.txt");
    if(file.open(QFile::WriteOnly))
    {
        file.write(requestResultJsonDocument.toJson());
        file.close();
    }


    if(requestResultJsonDocument.object().value("ok").toBool() == true)
        return Chat(requestResultJsonDocument.object().value("result").toObject());
    else
        return Chat();
}

Chat TelegramAPI::getChat(const qint32 chatId)
{
    QJsonObject requestJsonObject;

    requestJsonObject.insert("chat_id", QJsonValue(chatId));


    QJsonDocument requestResultJsonDocument = requestManager->sendRequest("getChat", QJsonDocument(requestJsonObject));

    if(requestResultJsonDocument.object().value("ok").toBool() == true)
        return Chat(requestResultJsonDocument.object().value("result").toObject());
    else
        return Chat();
}

UserProfilePhotos TelegramAPI::getUserProfilePhotos(qint32 userId, qint32 offset, qint32 limit)
{
    QJsonObject requestJsonObject;

    requestJsonObject.insert("user_id", QJsonValue(userId));
    if(offset != 0)
        requestJsonObject.insert("offset", QJsonValue(offset));
    if(limit > 0 && limit <= 100)
        requestJsonObject.insert("offset", QJsonValue(offset));


    QJsonDocument requestResultJsonDocument = requestManager->sendRequest("getUserProfilePhotos", QJsonDocument(requestJsonObject));

    if(requestResultJsonDocument.object().value("ok").toBool() == true)
        return UserProfilePhotos(requestResultJsonDocument.object().value("result").toObject());
    else
        return UserProfilePhotos();
}

Message TelegramAPI::sendPhoto(qint32 chatId, QFile *file)
{
    QJsonObject requestJsonObject;

    requestJsonObject.insert("chat_id", QJsonValue(chatId));

    QJsonDocument requestResultJsonDocument = requestManager->sendMultiPartRequest("sendPhoto", QJsonDocument(requestJsonObject), file);

    qDebug() << requestResultJsonDocument;
    return Message(requestResultJsonDocument.object());

    /*if(requestResultJsonDocument.object().value("ok").toBool() == true)
        return Message(requestResultJsonDocument.object().value("result").toObject());
    else
        return Message();*/
}


QJsonDocument TelegramAPI::getUpdates()
{
    QJsonDocument jsonDocumnet;
    return requestManager->sendRequest("getUpdates", jsonDocumnet);
}
