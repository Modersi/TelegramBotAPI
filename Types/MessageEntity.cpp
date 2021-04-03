#include "MessageEntity.h"

MessageEntity::MessageEntity()
{    
}

MessageEntity::MessageEntity(QString  type,
                             qint32   offset,
                             qint32   length,
                             QString  url,
                             User     user,
                             QString  language)
{
    _jsonObject.insert("type", QJsonValue(type));
    _jsonObject.insert("offset", QJsonValue(offset));
    _jsonObject.insert("length", QJsonValue(length));

    if(!url.isEmpty())
        _jsonObject.insert("url", QJsonValue(url));
    if(!user.isEmpty())
        _jsonObject.insert("user", QJsonValue(user.toObject()));
    if(!language.isEmpty())
        _jsonObject.insert("language", QJsonValue(language));
}

MessageEntity::MessageEntity(QJsonObject jsonObject)
{
    if(jsonObject.contains("type"))
        _jsonObject.insert("type", jsonObject.value("type"));

    if(jsonObject.contains("offset"))
        _jsonObject.insert("offset", jsonObject.value("offset"));

    if(jsonObject.contains("length"))
        _jsonObject.insert("length", jsonObject.value("length"));

    if(jsonObject.contains("url"))
        _jsonObject.insert("url", jsonObject.value("url"));

    if(jsonObject.contains("user"))
        _jsonObject.insert("user", jsonObject.value("user"));

    if(jsonObject.contains("language"))
        _jsonObject.insert("language", jsonObject.value("language"));
}

// "get", "set" methods for "type" field //

QString MessageEntity::type()
{
    return _jsonObject.value("type").toString();
}

void MessageEntity::setType(QString type)
{
    _jsonObject.insert("type", type);
}

// "get", "set" methods for "offset" field //

qint32 MessageEntity::offset()
{
    return _jsonObject.value("offset").toInt();
}

void MessageEntity::setOffset(qint32 offset)
{
    _jsonObject.insert("offset", offset);
}

// "get", "set" methods for "length" field //

qint32 MessageEntity::length()
{
    return _jsonObject.value("length").toInt();
}

void MessageEntity::setLength(qint32 length)
{
    _jsonObject.insert("length", length);
}

// "get", "set", "has" methods for "from" field //

QString MessageEntity::url()
{
    return _jsonObject.value("url").toString();
}

void MessageEntity::setUrl(QString url)
{
    _jsonObject.insert("url", url);
}

bool MessageEntity::hasUrl()
{
    return _jsonObject.contains("url");
}

// "get", "set", "has" methods for "from" field //

User MessageEntity::user()
{
    return User(_jsonObject.value("user").toObject());
}

void MessageEntity::setUser(User user)
{
    _jsonObject.insert("user", user.toObject());
}

bool MessageEntity::hasUser()
{
    return _jsonObject.contains("user");
}

// "get", "set", "has" methods for "from" field //

QString MessageEntity::language()
{
    return _jsonObject.value("language").toString();
}

void MessageEntity::setLanguage(QString language)
{
    _jsonObject.insert("language", language);
}

bool MessageEntity::hasLanguage()
{
    return _jsonObject.contains("language");
}
