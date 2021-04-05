#include "Chat.h"
#include "Message.h"

/*!
    \brief A default constructor. Constructs an empty object
*/
Chat::Chat() {}

/*!
    \brief Class contructor
    \param id   Unique identifier for this chat
    \param type Type of chat, can be either “private”, “group”, “supergroup” or “channel”
*/
Chat::Chat(qint64 id,
           QString type)
{
    _jsonObject.insert("id", id);
    _jsonObject.insert("type", type);
}

/*!
    \brief Constructor from QJsonObject
    \param QJsonObject QJsonObject which contains fields suitable for the class
*/
Chat::Chat(QJsonObject jsonObject)
{
    if(jsonObject.contains("id"))
        _jsonObject.insert("id", jsonObject.value("id"));

    if(jsonObject.contains("type"))
        _jsonObject.insert("type", jsonObject.value("type"));

    if(jsonObject.contains("title"))
        _jsonObject.insert("title", jsonObject.value("title"));

    if(jsonObject.contains("username"))
        _jsonObject.insert("username", jsonObject.value("username"));

    if(jsonObject.contains("first_name"))
        _jsonObject.insert("first_name", jsonObject.value("first_name"));

    if(jsonObject.contains("last_name"))
        _jsonObject.insert("last_name", jsonObject.value("last_name"));

    if(jsonObject.contains("photo"))
        _jsonObject.insert("photo", jsonObject.value("photo"));

    if(jsonObject.contains("description"))
        _jsonObject.insert("description", jsonObject.value("description"));

    if(jsonObject.contains("invite_link"))
        _jsonObject.insert("invite_link", jsonObject.value("invite_link"));

    if(jsonObject.contains("pinned_message"))
        _jsonObject.insert("pinned_message", jsonObject.value("pinned_message"));

    if(jsonObject.contains("permissions"))
        _jsonObject.insert("permissions", jsonObject.value("permissions"));

    if(jsonObject.contains("slow_mode_delay"))
        _jsonObject.insert("slow_mode_delay", jsonObject.value("slow_mode_delay"));

    if(jsonObject.contains("sticker_set_name"))
        _jsonObject.insert("sticker_set_name", jsonObject.value("sticker_set_name"));

    if(jsonObject.contains("can_set_sticker_set"))
        _jsonObject.insert("can_set_sticker_set", jsonObject.value("can_set_sticker_set"));
}


/***//*!
    \brief Get **id** value
    \return Value of **id**
*/
qint64 Chat::id()
{
    return _jsonObject.value("id").toInt();
}

/*!
    \brief Set new value for **id**
    \param qint64 New value of **id**
*/
void Chat::setId(qint64 id)
{
    _jsonObject.insert("id", id);
}


/***//*!
    \brief Get **type** value
    \return Value of **type**
*/
QString Chat::type()
{
    return _jsonObject.value("type").toString();
}

/*!
    \brief Set new value for **type**
    \param QString New value of **type**
*/
void Chat::setType(QString type)
{
    _jsonObject.insert("type", type);
}


/***//*!
    \brief Get **title** value
    \return Value of **title**
*/
QString Chat::title()
{
    return _jsonObject.value("title").toString();
}

/*!
    \brief Set new value for **title**
    \param QString New value of **title**
*/
void Chat::setTitle(QString title)
{
    _jsonObject.insert("title", title);
}

/*!
    \brief Check if object has **title**
    \return `True` if has **title**, `false` if doesn't
*/
bool Chat::hasTitle()
{
    return  _jsonObject.contains("title");
}


/***//*!
    \brief Get **username** value
    \return Value of **username**
*/
QString Chat::username()
{
    return _jsonObject.value("username").toString();
}

/*!
    \brief Set new value for **username**
    \param QString New value of **username**
*/
void Chat::setUsername(QString username)
{
    _jsonObject.insert("username", username);
}

/*!
    \brief Check if object has **username**
    \return `True` if has **username**, `false` if doesn't
*/
bool Chat::hasUsername()
{
    return _jsonObject.contains("username");
}


/***//*!
    \brief Get **firstName** value
    \return Value of **firstName**
*/
QString Chat::firstName()
{
    return _jsonObject.value("first_name").toString();
}

/*!
    \brief Set new value for **firstName**
    \param QString New value of **firstName**
*/
void Chat::setFirstName(QString firstName)
{
    _jsonObject.insert("first_name", firstName);
}

/*!
    \brief Check if object has **firstName**
    \return `True` if has **firstName**, `false` if doesn't
*/
bool Chat::hasFirstName()
{
    return _jsonObject.contains("first_name");
}


/***//*!
    \brief Get **lastName** value
    \return Value of **lastName**
*/
QString Chat::lastName()
{
    return _jsonObject.value("last_name").toString();
}

/*!
    \brief Set new value for **lastName**
    \param QString New value of **lastName**
*/
void Chat::setLastName(QString lastName)
{
    _jsonObject.insert("last_name", lastName);
}

/*!
    \brief Check if object has **lastName**
    \return `True` if has **lastName**, `false` if doesn't
*/
bool Chat::hasLastName()
{
    return _jsonObject.contains("last_name");
}


/***//*!
    \brief Get **photo** value
    \return Value of **photo** in form of `ChatPhoto` object
*/
ChatPhoto Chat::photo()
{
    return ChatPhoto(_jsonObject.value("photo").toObject());
}

/*!
    \brief Set new value for **photo**
    \param ChatPhoto New value of **photo**
*/
void Chat::setPhoto(ChatPhoto photo)
{
    _jsonObject.insert("photo", photo.toObject());
}

/*!
    \brief Check if object has **photo**
    \return `True` if has **photo**, `false` if doesn't
*/
bool Chat::hasPhoto()
{
    return _jsonObject.contains("photo");
}


/***//*!
    \brief Get **description** value
    \return Value of **description**
*/
QString Chat::description()
{
    return _jsonObject.value("description").toString();
}

/*!
    \brief Set new value for **description**
    \param QString New value of **description**
*/
void Chat::setDescription(QString description)
{
    _jsonObject.insert("description", description);
}

/*!
    \brief Check if object has **description**
    \return `True` if has **description**, `false` if doesn't
*/
bool Chat::hasDescription()
{
    return _jsonObject.contains("description");
}


/***//*!
    \brief Get **inviteLink** value
    \return Value of **inviteLink**
*/
QString Chat::inviteLink()
{
    return _jsonObject.value("invite_link").toString();
}

/*!
    \brief Set new value for **inviteLink**
    \param QString New value of **inviteLink**
*/
void Chat::setInviteLink(QString inviteLink)
{
    _jsonObject.insert("invite_link", inviteLink);
}

/*!
    \brief Check if object has **inviteLink**
    \return `True` if has **inviteLink**, `false` if doesn't
*/
bool Chat::hasInviteLink()
{
    return _jsonObject.contains("invite_link");
}


/***//*!
    \brief Get **pinnedMessage** value
    \return QSharedPointer on value of **pinnedMessage** in form of `Message` object
*/
QSharedPointer<Message> Chat::pinnedMessage()
{
    return QSharedPointer<Message>(new Message(_jsonObject.value("pinned_message").toObject()));
}

/*!
    \brief Set new value for **pinnedMessage**
    \param Message New value of **pinnedMessage**
*/
void Chat::setPinnedMessage(Message pinnedMessage)
{
    _jsonObject.insert("pinned_message", pinnedMessage.toObject());
}

/*!
    \brief Check if object has **pinnedMessage**
    \return `True` if has **pinnedMessage**, `false` if doesn't
*/
bool Chat::hasPinnedMessage()
{
    return _jsonObject.contains("pinned_message");
}


/***//*!
    \brief Get **permissions** value
    \return Value of **permissions** in form of `ChatPermissions` object
*/
ChatPermissions Chat::permissions()
{
    return ChatPermissions(_jsonObject.value("permissions").toObject());
}

/*!
    \brief Set new value for **permissions**
    \param ChatPermissions New value of **permissions**
*/
void Chat::setPermissions(ChatPermissions permissions)
{
    _jsonObject.insert("permissions", permissions.toObject());
}

/*!
    \brief Check if object has **permissions**
    \return `True` if has **permissions**, `false` if doesn't
*/
bool Chat::hasPermissions()
{
    return _jsonObject.contains("permissions");
}


/***//*!
    \brief Get **slowModeDelay** value
    \return Value of **slowModeDelay**
*/
qint32 Chat::slowModeDelay()
{
    return _jsonObject.value("slow_mode_delay").toInt();
}

/*!
    \brief Set new value for **slowModeDelay**
    \param qint32 New value of **slowModeDelay**
*/
void Chat::setSlowModeDelay(qint32 slowModeDelay)
{
    _jsonObject.insert("slow_mode_delay", slowModeDelay);
}

/*!
    \brief Check if object has **slowModeDelay**
    \return `True` if has **slowModeDelay**, `false` if doesn't
*/
bool Chat::hasSlowModeDelay()
{
    return _jsonObject.contains("slow_mode_delay");
}


/***//*!
    \brief Get **stickerSetName** value
    \return Value of **stickerSetName**
*/
QString Chat::stickerSetName()
{
    return _jsonObject.value("sticker_set_name").toString();
}

/*!
    \brief Set new value for **stickerSetName**
    \param QString New value of **stickerSetName**
*/
void Chat::setStickerSetName(QString stickerSetName)
{
    _jsonObject.insert("sticker_set_name", stickerSetName);
}

/*!
    \brief Check if object has **stickerSetName**
    \return `True` if has **stickerSetName**, `false` if doesn't
*/
bool Chat::hasStickerSetName()
{
    return _jsonObject.contains("sticker_set_name");
}


/***//*!
    \brief Get **canSetStickerSet** value
    \return Value of **canSetStickerSet**
*/
bool Chat::canSetStickerSet()
{
    return _jsonObject.value("can_set_sticker_set").toBool();
}

/*!
    \brief Set new value for **canSetStickerSet**
    \param bool New value of **canSetStickerSet**
*/
void Chat::setCanSetStickerSet(bool canSetStickerSet)
{
    _jsonObject.insert("can_set_sticker_set", canSetStickerSet);
}

/*!
    \brief Check if object has **canSetStickerSet**
    \return `True` if has **canSetStickerSet**, `false` if doesn't
*/
bool Chat::hasCanSetStickerSet()
{
    return _jsonObject.contains("can_set_sticker_set");
}
