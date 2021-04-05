#include "Message.h"


Message::Message()
{
}

Message::Message(qint32                 messageId,
                 qint32                 date,
                 Chat                  chat,
                 User                  from,
                 Chat                  forwardFromChat,
                 User                  forwardFrom,
                 qint32                 forwardFromMessageId,
                 QString                forwardSignature,
                 QString                forwardSenderName,
                 qint32                 forwardDate,
                 Message               replyToMessage,
                 User                  viaBot,
                 qint32                 editDate,
                 QString                mediaGroupId,
                 QString                authorSignature,
                 QString                text,
                 //MessageEntity entities[],
                 //Animation animation,
                 //Audio audio,
                 //Document document,
                 //PhotoSize photo[],
                 //Sticker sticker,
                 //Video video,
                 //VideoNote videoNote,
                 //Voice voice,
                 QString                caption,
                 //MessageEntity captionEntities[],
                 //Contact contact,
                 //Dice dice,
                 //Game game,
                 //Poll poll,
                 //Venue venue,
                 //Location location,
                 QVector<User>            newChatMembers,
                 User                   leftChatMember,
                 QString                newChatTitle,
                 //PhotoSize newChatPhoto[],
                 bool                   deleteChatPhoto,
                 bool                   groupChatCreated,
                 bool                   supergroupChatCreated,
                 bool                   channelChatCreated,
                 qint64                 migrateToChatId,
                 qint64                 migrateFromChatId,
                 Message               pinnedMessage,
                 //Invoice invoice,
                 //SuccessfulPayment    successfulPayment,
                 //PassportData         passportData,
                 //InlineKeyboardMarkup replyMarkup,
                 QString                connectedWebsite)
{
    _jsonObject.insert("message_id", QJsonValue(messageId));
    _jsonObject.insert("date", QJsonValue(date));
    _jsonObject.insert("chat", QJsonValue(chat.toObject()));

    if(!from.isEmpty())
        _jsonObject.insert("from", QJsonValue(from.toObject()));

    if(!forwardFromChat.isEmpty())
        _jsonObject.insert("forward_from_chat", QJsonValue(forwardFromChat.toObject()));

    if(!forwardFrom.isEmpty())
        _jsonObject.insert("forward_from", QJsonValue(forwardFrom.toObject()));

    if(forwardFromMessageId != 0)
        _jsonObject.insert("forward_from_message_id", QJsonValue(forwardFromMessageId));

    if(!forwardSignature.isEmpty())
        _jsonObject.insert("forward_signature", QJsonValue(forwardSignature));

    if(!forwardSenderName.isEmpty())
        _jsonObject.insert("forward_sender_name", QJsonValue(forwardSenderName));

    if(forwardDate != 0)
        _jsonObject.insert("forward_date", QJsonValue(forwardDate));

    if(!replyToMessage.isEmpty())
        _jsonObject.insert("reply_to_message", QJsonValue(replyToMessage.toObject()));

    if(!viaBot.isEmpty())
        _jsonObject.insert("via_bot", QJsonValue(viaBot.toObject()));

    if(editDate != 0)
        _jsonObject.insert("edit_date", QJsonValue(editDate));

    if(!mediaGroupId.isEmpty())
        _jsonObject.insert("media_group_id", QJsonValue(mediaGroupId));

    if(!authorSignature.isEmpty())
        _jsonObject.insert("author_signature", QJsonValue(authorSignature));

    if(!text.isEmpty())
        _jsonObject.insert("text", QJsonValue(text));

    //if(!entities.isEmpty())
    //    _jsonObject.insert("entities", QJsonValue(entities.toObject()));
    //
    //if(!animation.isEmpty())
    //    _jsonObject.insert("animation", QJsonValue(animation.toObject()));
    //
    //if(!audio.isEmpty())
    //    _jsonObject.insert("audio", QJsonValue(audio.toObject()));
    //
    //if(!document.isEmpty())
    //    _jsonObject.insert("document", QJsonValue(document.toObject()));
    //
    //if(!photo.isEmpty())
    //    _jsonObject.insert("photo", QJsonValue(photo.toObject()));
    //
    //if(!video.isEmpty())
    //    _jsonObject.insert("video", QJsonValue(video.toObject()));
    //
    //if(!videoNote.isEmpty())
    //    _jsonObject.insert("videoNote", QJsonValue(videoNote.toObject()));
    //
    //if(!voice.isEmpty())
    //    _jsonObject.insert("voice", QJsonValue(voice.toObject()));

    if(!caption.isEmpty())
        _jsonObject.insert("caption", QJsonValue(caption));

    //if(!captionEntities.isEmpty())
    //    _jsonObject.insert("caption_entities", QJsonValue(captionEntities.toObject()));
    //
    //if(!contact.isEmpty())
    //    _jsonObject.insert("contact", QJsonValue(contact.toObject()));
    //
    //if(!dice.isEmpty())
    //    _jsonObject.insert("dice", QJsonValue(dice.toObject()));
    //
    //if(!game.isEmpty())
    //    _jsonObject.insert("game", QJsonValue(game.toObject()));
    //
    //if(!poll.isEmpty())
    //    _jsonObject.insert("poll", QJsonValue(poll.toObject()));
    //
    //if(!venue.isEmpty())
    //    _jsonObject.insert("venue", QJsonValue(venue.toObject()));
    //
    //if(!location.isEmpty())
    //    _jsonObject.insert("location", QJsonValue(location.toObject()));

    if(!newChatMembers.isEmpty())
        _jsonObject.insert("new_chat_members", QJsonValue(Type::QVectorToQJsonArray(newChatMembers)));

    if(!leftChatMember.isEmpty())
        _jsonObject.insert("left_chat_member", QJsonValue(leftChatMember.toObject()));

    if(!newChatTitle.isEmpty())
        _jsonObject.insert("new_chat_title", QJsonValue(newChatTitle));

    //if(newChatPhoto != nullptr)
    //   _jsonObject.insert("new_chat_photo", QJsonValue(newChatPhoto.toObject()));

    if(deleteChatPhoto == true)
        _jsonObject.insert("delete_chat_photo", QJsonValue(deleteChatPhoto));

    if(groupChatCreated == true)
        _jsonObject.insert("group_chat_created", QJsonValue(groupChatCreated));

    if(supergroupChatCreated == true)
        _jsonObject.insert("supergroup_chat_created", QJsonValue(supergroupChatCreated));

    if(channelChatCreated == true)
        _jsonObject.insert("channel_chat_created", QJsonValue(channelChatCreated));

    if(migrateToChatId != 0)
        _jsonObject.insert("migrate_to_chat_id", QJsonValue(migrateToChatId));

    if(migrateFromChatId != 0)
        _jsonObject.insert("migrate_from_chat_id", QJsonValue(migrateFromChatId));

    if(!pinnedMessage.isEmpty())
        _jsonObject.insert("pinned_message", QJsonValue(pinnedMessage.toObject()));

    if(!connectedWebsite.isEmpty())
        _jsonObject.insert("connected_website", QJsonValue(connectedWebsite));

}

Message::Message(QJsonObject jsonObject)
{
    if(jsonObject.contains("message_id"))
        _jsonObject.insert("message_id", jsonObject.value("message_id"));

    if(jsonObject.contains("from"))
        _jsonObject.insert("from", jsonObject.value("from"));

    if(jsonObject.contains("date"))
        _jsonObject.insert("date", jsonObject.value("date"));

    if(jsonObject.contains("chat"))
        _jsonObject.insert("chat", jsonObject.value("chat"));

    if(jsonObject.contains("forward_from"))
        _jsonObject.insert("forward_from", jsonObject.value("forward_from"));

    if(jsonObject.contains("forward_from_chat"))
        _jsonObject.insert("forward_from_chat", jsonObject.value("forward_from_chat"));

    if(jsonObject.contains("forward_from_message_id"))
        _jsonObject.insert("forward_from_message_id", jsonObject.value("forward_from_message_id"));

    if(jsonObject.contains("forward_signature"))
        _jsonObject.insert("forward_signature", jsonObject.value("forward_signature"));

    if(jsonObject.contains("forward_sender_name"))
        _jsonObject.insert("forward_sender_name", jsonObject.value("forward_sender_name"));

    if(jsonObject.contains("forward_date"))
        _jsonObject.insert("forward_date", jsonObject.value("forward_date"));

    if(jsonObject.contains("reply_to_message"))
        _jsonObject.insert("reply_to_message", jsonObject.value("reply_to_message"));

    if(jsonObject.contains("via_bot"))
        _jsonObject.insert("via_bot", jsonObject.value("via_bot"));

    if(jsonObject.contains("edit_date"))
        _jsonObject.insert("edit_date", jsonObject.value("edit_date"));

    if(jsonObject.contains("media_group_id"))
        _jsonObject.insert("media_group_id", jsonObject.value("media_group_id"));

    if(jsonObject.contains("entities"))
        _jsonObject.insert("entities", jsonObject.value("entities"));

    if(jsonObject.contains("animation"))
        _jsonObject.insert("animation", jsonObject.value("animation"));

    if(jsonObject.contains("audio"))
        _jsonObject.insert("audio", jsonObject.value("audio"));

    if(jsonObject.contains("document"))
        _jsonObject.insert("document", jsonObject.value("document"));

    if(jsonObject.contains("photo"))
        _jsonObject.insert("photo", jsonObject.value("photo"));

    if(jsonObject.contains("sticker"))
        _jsonObject.insert("sticker", jsonObject.value("sticker"));

    if(jsonObject.contains("video"))
        _jsonObject.insert("video", jsonObject.value("video"));

    if(jsonObject.contains("video_note"))
        _jsonObject.insert("video_note", jsonObject.value("video_note"));

    if(jsonObject.contains("voice"))
        _jsonObject.insert("voice", jsonObject.value("voice"));

    if(jsonObject.contains("caption"))
        _jsonObject.insert("caption", jsonObject.value("caption"));

    if(jsonObject.contains("caption_entities"))
        _jsonObject.insert("caption_entities", jsonObject.value("caption_entities"));

    if(jsonObject.contains("contact"))
        _jsonObject.insert("contact", jsonObject.value("contact"));

    if(jsonObject.contains("dice"))
        _jsonObject.insert("dice", jsonObject.value("dice"));

    if(jsonObject.contains("game"))
        _jsonObject.insert("game", jsonObject.value("game"));

    if(jsonObject.contains("poll"))
        _jsonObject.insert("poll", jsonObject.value("poll"));

    if(jsonObject.contains("venue"))
        _jsonObject.insert("venue", jsonObject.value("venue"));

    if(jsonObject.contains("location"))
        _jsonObject.insert("location", jsonObject.value("location"));

    if(jsonObject.contains("new_chat_members"))
        _jsonObject.insert("new_chat_members", jsonObject.value("new_chat_members"));

    if(jsonObject.contains("left_chat_member"))
        _jsonObject.insert("left_chat_member", jsonObject.value("left_chat_member"));

    if(jsonObject.contains("new_chat_title"))
        _jsonObject.insert("new_chat_title", jsonObject.value("new_chat_title"));

    if(jsonObject.contains("new_chat_photo"))
        _jsonObject.insert("new_chat_photo", jsonObject.value("new_chat_photo"));

    if(jsonObject.contains("delete_chat_photo"))
        _jsonObject.insert("delete_chat_photo", jsonObject.value("delete_chat_photo"));

    if(jsonObject.contains("group_chat_created"))
        _jsonObject.insert("group_chat_created", jsonObject.value("group_chat_created"));

    if(jsonObject.contains("supergroup_chat_created"))
        _jsonObject.insert("supergroup_chat_created", jsonObject.value("supergroup_chat_created"));

    if(jsonObject.contains("channel_chat_created"))
        _jsonObject.insert("channel_chat_created", jsonObject.value("channel_chat_created"));

    if(jsonObject.contains("migrate_to_chat_id"))
        _jsonObject.insert("migrate_to_chat_id", jsonObject.value("migrate_to_chat_id"));

    if(jsonObject.contains("migrate_from_chat_id"))
        _jsonObject.insert("migrate_from_chat_id", jsonObject.value("migrate_from_chat_id"));

    if(jsonObject.contains("pinned_message"))
        _jsonObject.insert("pinned_message", jsonObject.value("pinned_message"));

    if(jsonObject.contains("invoice"))
        _jsonObject.insert("invoice", jsonObject.value("invoice"));

    if(jsonObject.contains("successful_payment"))
        _jsonObject.insert("successful_payment", jsonObject.value("successful_payment"));

    if(jsonObject.contains("connected_website"))
        _jsonObject.insert("connected_website", jsonObject.value("connected_website"));

    if(jsonObject.contains("passport_data"))
        _jsonObject.insert("passport_data", jsonObject.value("passport_data"));

    if(jsonObject.contains("reply_markup"))
        _jsonObject.insert("reply_markup", jsonObject.value("reply_markup"));
}

// "get", "set" methods for "message_id" field //

qint32 Message::messageId()
{
    return _jsonObject.value("message_id").toInt();
}

void Message::setMessageId(qint32 messageId)
{
    _jsonObject.insert("message_id", messageId);
}

// "get", "set" methods for "date" field //

qint32 Message::date()
{
    return _jsonObject.value("date").toInt();
}

void Message::setDate(qint32 date)
{
    _jsonObject.insert("date", date);
}

// "get", "set" methods for "chat" field //

Chat Message::chat()
{
    return Chat(_jsonObject.value("chat").toObject());
}

void Message::setChat(Chat chat)
{
    _jsonObject.insert("chat", chat.toObject());
}

// "get", "set", "has" methods for "from" field //

User Message::from()
{
    return User(_jsonObject.value("from").toObject());
}

void Message::setFrom(User from)
{
    _jsonObject.insert("from", from.toObject());
}

bool Message::hasFrom()
{
    return _jsonObject.contains("from");
}

// "get", "set", "has" methods for "forward_from_chat" field //

Chat Message::forwardFromChat()
{
    return Chat(_jsonObject.value("forward_from_chat").toObject());
}

void Message::setForwardFromChat(Chat forwardFromChat)
{
    _jsonObject.insert("forward_from_chat", forwardFromChat.toObject());
}

bool Message::hasForwardFromChat()
{
    return _jsonObject.contains("forward_from_chat");
}

// "get", "set", "has" methods for "forward_from" field //

User Message::forwardFrom()
{
    return User(_jsonObject.value("forward_from").toObject());
}

void Message::setForwardFrom(User forwardFrom)
{
    _jsonObject.insert("forward_from", forwardFrom.toObject());
}

bool Message::hasForwardFrom()
{
    return _jsonObject.contains("forward_from");
}

// "get", "set", "has" methods for "forward_from_message_id" field //

qint32 Message::forwardFromMessageId()
{
    return _jsonObject.value("forward_from_message_id").toInt();
}

void Message::setForwardFromMessageId(qint32 forwardFromMessageId)
{
    _jsonObject.insert("forward_from_message_id", forwardFromMessageId);
}

bool Message::hasForwardFromMessageId()
{
    return _jsonObject.contains("forward_from_message_id");
}

// "get", "set", "has" methods for "forward_signature" field //

QString Message::forwardSignature()
{
    return _jsonObject.value("forward_signature").toString();
}

void Message::setForwardSignature(QString forwardSignature)
{
    _jsonObject.insert("forward_signature", forwardSignature);
}

bool Message::hasForwardSignature()
{
    return _jsonObject.contains("forward_signature");
}

// "get", "set", "has" methods for "forward_sender_name" field //

QString Message::forwardSenderName()
{
    return _jsonObject.value("forward_sender_name").toString();
}

void Message::setForwardSenderName(QString forwardSenderName)
{
    _jsonObject.insert("forward_sender_name", forwardSenderName);
}

bool Message::hasForwardSenderName()
{
    return _jsonObject.contains("forward_sender_name");
}

// "get", "set", "has" methods for "forward_date" field //

qint32 Message::forwardDate()
{
    return _jsonObject.value("forward_date").toInt();
}

void Message::setForwardDate(qint32 forwardDate)
{
    _jsonObject.insert("forward_date", forwardDate);
}

bool Message::hasForwardDate()
{
    return _jsonObject.contains("forward_date");
}

// "get", "set", "has" methods for "reply_to_message" field //

Message Message::replyToMessage()
{
    return Message(_jsonObject.value("reply_to_message").toObject());
}

void Message::setReplyToMessage(Message replyToMessage)
{
    _jsonObject.insert("reply_to_message", replyToMessage.toObject());
}

bool Message::hasReplyToMessage()
{
    return _jsonObject.contains("reply_to_message");
}

// "get", "set", "has" methods for "via_bot" field //

User Message::viaBot()
{
    return User(_jsonObject.value("via_bot").toObject());
}

void Message::setViaBot(User viaBot)
{
    _jsonObject.insert("via_bot", viaBot.toObject());
}

bool Message::hasViaBot()
{
    return _jsonObject.contains("via_bot");
}

// "get", "set", "has" methods for "edit_date" field //

qint32 Message::editDate()
{
    return _jsonObject.value("edit_date").toInt();
}

void Message::setEditDate(qint32 editDate)
{
    _jsonObject.insert("edit_date", editDate);
}

bool Message::hasEditDate()
{
    return _jsonObject.contains("edit_date");
}

// "get", "set", "has" methods for "media_group_id" field //

QString Message::mediaGroupId()
{
    return _jsonObject.value("media_group_id").toString();
}

void Message::setMediaGroupId(QString mediaGroupId)
{
    _jsonObject.insert("media_group_id", mediaGroupId);
}

bool Message::hasMediaGroupId()
{
    return _jsonObject.contains("media_group_id");
}

// "get", "set", "has" methods for "author_signature" field //

QString Message::authorSignature()
{
    return _jsonObject.value("author_signature").toString();
}

void Message::setAuthorSignature(QString authorSignature)
{
    _jsonObject.insert("author_signature", authorSignature);
}

bool Message::hasAuthorSignature()
{
    return _jsonObject.contains("author_signature");
}

// "get", "set", "has" methods for "text" field //

QString Message::text()
{
    return _jsonObject.value("text").toString();
}

void Message::setText(QString text)
{
    _jsonObject.insert("text", text);
}

bool Message::hasText()
{
    return _jsonObject.contains("text");
}

// "get", "set", "has" methods for "caption" field //

QString Message::caption()
{
    return _jsonObject.value("caption").toString();
}

void Message::setCaption(QString caption)
{
    _jsonObject.insert("caption", caption);
}

bool Message::hasCaption()
{
    return _jsonObject.contains("caption");
}

// "get", "set", "has" methods for "new_chat_members" field //

QVector<User> Message::newChatMembers()
{
    return Type::QJsonArrayToQVector(_jsonObject.value("new_chat_members").toArray(), User());
}

void Message::setNewChatMembers(QVector<User> newChatMembers)
{
    _jsonObject.insert("new_chat_members", Type::QVectorToQJsonArray(newChatMembers));
}

bool Message::hasNewChatMembers()
{
    return _jsonObject.contains("new_chat_members");
}

// "get", "set", "has" methods for "left_chat_member" field //

User Message::leftChatMember()
{
    return User(_jsonObject.value("left_chat_member").toObject());
}

void Message::setLeftChatMember(User leftChatMember)
{
    _jsonObject.insert("left_chat_member", leftChatMember.toObject());
}

bool Message::hasLeftChatMember()
{
    return _jsonObject.contains("left_chat_member");
}

// "get", "set", "has" methods for "new_chat_title" field //

QString Message::newChatTitle()
{
    return _jsonObject.value("new_chat_title").toString();
}

void Message::setNewChatTitle(QString newChatTitle)
{
    _jsonObject.insert("new_chat_title", newChatTitle);
}

bool Message::hasNewChatTitle()
{
    return _jsonObject.contains("new_chat_title");
}

// "get", "set", "has" methods for "delete_chat_photo" field //

bool Message::chatPhotoDeleted()
{
    return _jsonObject.value("delete_chat_photo").toBool();
}

void Message::setChatPhotoDeleted(bool deleteChatPhoto)
{
    _jsonObject.insert("delete_chat_photo", deleteChatPhoto);
}

bool Message::hasChatPhotoDeleted()
{
    return _jsonObject.contains("delete_chat_photo");
}

// "get", "set", "has" methods for "group_chat_created" field //

bool Message::groupChatCreated()
{
    return _jsonObject.value("group_chat_created").toBool();
}

void Message::setGroupChatCreated(bool groupChatCreated)
{
    _jsonObject.insert("group_chat_created", groupChatCreated);
}

bool Message::hasGroupChatCreated()
{
    return _jsonObject.contains("group_chat_created");
}

// "get", "set", "has" methods for "supergroup_chat_created" field //

bool Message::supergroupChatCreated()
{
    return _jsonObject.value("supergroup_chat_created").toBool();
}

void Message::setSupergroupChatCreated(bool supergroupChatCreated)
{
    _jsonObject.insert("supergroup_chat_created", supergroupChatCreated);
}

bool Message::hasSupergroupChatCreated()
{
    return _jsonObject.contains("supergroup_chat_created");
}

// "get", "set", "has" methods for "channel_chat_created" field //

bool Message::channelChatCreated()
{
    return _jsonObject.value("channel_chat_created").toBool();
}

void Message::setChannelChatCreated(bool channelChatCreated)
{
    _jsonObject.insert("channel_chat_created", channelChatCreated);
}

bool Message::hasChannelChatCreated()
{
    return _jsonObject.contains("channel_chat_created");
}

// "get", "set", "has" methods for "migrate_to_chat_id" field //

qint64 Message::migrateToChatId()
{
    return _jsonObject.value("migrate_to_chat_id").toInt();
}

void Message::setMigrateToChatId(qint64 migrateToChatId)
{
    _jsonObject.insert("migrate_to_chat_id", migrateToChatId);
}

bool Message::hasMigrateToChatId()
{
    return _jsonObject.contains("migrate_to_chat_id");
}

// "get", "set", "has" methods for "migrate_from_chat_id" field //

qint64 Message::migrateFromChatId()
{
    return _jsonObject.value("migrate_from_chat_id").toInt();
}

void Message::setMigrateFromChatId(qint64 migrateFromChatId)
{
    _jsonObject.insert("migrate_from_chat_id", migrateFromChatId);
}

bool Message::hasMigrateFromChatId()
{
    return _jsonObject.contains("migrate_from_chat_id");
}

// "get", "set", "has" methods for "pinned_message" field //

Message Message::pinnedMessage()
{
    return Message(_jsonObject.value("pinned_message").toObject());
}

void Message::setPinnedMessage(Message pinnedMessage)
{
    _jsonObject.insert("pinned_message", pinnedMessage.toObject());
}

bool Message::hasPinnedMessage()
{
    return _jsonObject.contains("pinned_message");
}

// "get", "set", "has" methods for "connected_website" field //

QString Message::connectedWebsite()
{
    return _jsonObject.value("connected_website").toString();
}

void Message::setConnectedWebsite(QString connectedWebsite)
{
    _jsonObject.insert("connected_website", connectedWebsite);
}

bool Message::hasConnectedWebsite()
{
    return _jsonObject.contains("connected_website");
}

