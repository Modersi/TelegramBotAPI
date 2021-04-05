#ifndef TELEGRAMAPI_H
#define TELEGRAMAPI_H

#include "RequestManager/RequestManager.h"

#include "Types/Chat.h"
#include "Types/User.h"
#include "Types/Message.h"
#include "Types/UserProfilePhotos.h"

class TelegramAPI
{
public:
    TelegramAPI(const QString);

    // A simple method for testing your bot's auth token. Requires no parameters. Returns basic information about the bot in form of a User object.
    User getMe();

    // !!  Раздуплить ексепшоны !! //
    // !!  ADD reply_markup !! //
    // Use this method to send text messages via chat ID. On success, the sent message in form of Message object is returned. On failure return empty Message object
    Message sendMessage(qint32  chatId,                             // Unique identifier for the target chat
                        QString text,                               // Text of the message to be sent, 1-4096 characters after entities parsing
                        QString parseMode = "",                     // Optional. Mode for parsing entities in the message text
                        bool    disableWebPagePreview = false,      // Optional. Disables link previews for links in this message
                        bool    disableNotification = false,        // Optional. Sends the message silently. Users will receive a notification with no sound
                        qint32  replyToMessageId = 0);              // Optional. If the message is a reply, ID of the original message

    // !!  ADD reply_markup !! //
    // Use this method to send text messages via username of the target channel. On success, the sent message in form of Message object is returned. On failure return empty Message object
    Message sendMessage(QString chatId,                             // Username of the target channel (in the format @channelusername)
                        QString text,
                        QString parseMode = "",
                        bool    disableWebPagePreview = false,
                        bool    disableNotification = false,
                        qint32  replyToMessageId = 0);

    // Use this method to get up to date information about the chat via username of the target channel (current name of the user for one-on-one conversations, current username of a user, group or channel, etc.). Returns a Chat object on success.
    Chat getChat(const QString chatId);

    // Use this method to get up to date information about the chat via chat ID (current name of the user for one-on-one conversations, current username of a user, group or channel, etc.). Returns a Chat object on success.
    Chat getChat(const qint32 chatId);

    UserProfilePhotos getUserProfilePhotos(qint32 userId, qint32 offset = 0, qint32 limit = 100);

    Message sendPhoto(qint32 chatId, QFile *file);

    QJsonDocument getUpdates();

private:
    RequestManager* requestManager;

};

#endif // TELEGRAMAPI_H
