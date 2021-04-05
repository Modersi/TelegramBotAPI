#include "User.h"

User::User() {}

User::User(qint32 id, bool isBot, QString firstName, QString lastName, QString username, QString languageCode)
{
    _jsonObject.insert("id", QJsonValue(id));
    _jsonObject.insert("is_bot", QJsonValue(isBot));
    _jsonObject.insert("first_name", QJsonValue(firstName));

    if(!lastName.isEmpty())
        _jsonObject.insert("last_name", QJsonValue(lastName));
    if(!username.isEmpty())
        _jsonObject.insert("username", QJsonValue(username));
    if(!languageCode.isEmpty())
        _jsonObject.insert("language_code", QJsonValue(languageCode));
}

User::User(QJsonObject jsonObject)
{
    if(jsonObject.contains("id"))
        _jsonObject.insert("id", jsonObject.value("id"));

    if(jsonObject.contains("is_bot"))
        _jsonObject.insert("is_bot", jsonObject.value("is_bot"));

    if(jsonObject.contains("first_name"))
        _jsonObject.insert("first_name", jsonObject.value("first_name"));

    if(jsonObject.contains("last_name"))
        _jsonObject.insert("last_name", jsonObject.value("last_name"));

    if(jsonObject.contains("username"))
        _jsonObject.insert("username", jsonObject.value("username"));

    if(jsonObject.contains("can_join_groups"))
        _jsonObject.insert("can_join_groups", jsonObject.value("can_join_groups"));

    if(jsonObject.contains("can_read_all_group_messages"))
        _jsonObject.insert("can_read_all_group_messages", jsonObject.value("can_read_all_group_messages"));

    if(jsonObject.contains("supports_inline_queries"))
        _jsonObject.insert("supports_inline_queries", jsonObject.value("supports_inline_queries"));
}

// "get", "set" methods for "id" field //

qint32 User::id()
{
    return _jsonObject.value("id").toInt();
}

void User::setId(qint32 id)
{
    _jsonObject.insert("id", id);
}

// "get", "set" methods for "is_bot" field //

bool User::isBot()
{
    return _jsonObject.value("is_bot").toBool();
}

void User::setIsBot(bool isBot)
{
    _jsonObject.insert("is_bot", isBot);
}

// "get", "set" methods for "first_name" field //

QString User::firstName()
{
    return _jsonObject.value("first_name").toString();
}

void User::setFirstName(QString firstName)
{
    _jsonObject.insert("first_name", firstName);
}

// "get", "set", "has" methods for "last_name" field //

QString User::lastName()
{
    return _jsonObject.value("last_name").toString();
}

void User::setLastName(QString lastName)
{
    _jsonObject.insert("last_name", lastName);
}

bool User::hasLastName()
{
    return _jsonObject.contains("last_name");
}

// "get", "set", "has" methods for "username" field //

QString User::username()
{
    return _jsonObject.value("username").toString();
}

void User::setUsername(QString username)
{
    _jsonObject.insert("username", username);
}

bool User::hasUsername()
{
    return _jsonObject.contains("username");
}

// "get", "set", "has" methods for "language_code" field //

QString User::languageCode()
{
    return _jsonObject.value("language_code").toString();
}

void User::setLanguageCode(QString languageCode)
{
    _jsonObject.insert("language_code", languageCode);
}

bool User::hasLanguageCode()
{
    return _jsonObject.contains("language_code");
}

// "get", "set", "has" methods for "can_join_groups" field //

bool User::canJoinGroups()
{
    return _jsonObject.value("can_join_groups").toBool();
}

void User::setCanJoinGroups(bool canJoinGroups)
{
    _jsonObject.insert("can_join_groups", canJoinGroups);
}

bool User::hasCanJoinGroups()
{
    return _jsonObject.contains("can_join_groups");
}

// "get", "set", "has" methods for "can_read_all_group_messages" field //

bool User::canReadAllGroupMessages()
{
    return _jsonObject.value("can_read_all_group_messages").toBool();
}

void User::setCanReadAllGroupMessages(bool canReadAllGroupMessages)
{
    _jsonObject.insert("can_read_all_group_messages", canReadAllGroupMessages);
}

bool User::hasCanReadAllGroupMessages()
{
    return _jsonObject.contains("can_read_all_group_messages");
}

// "get", "set", "has" methods for "supports_inline_queries" field //

bool User::supportsInlineQueries()
{
    return _jsonObject.value("supports_inline_queries").toBool();
}

void User::setSupportsInlineQueries(bool supportsInlineQueries)
{
    _jsonObject.insert("can_read_all_group_messages", supportsInlineQueries);
}

bool User::hasSupportsInlineQueries()
{
    return _jsonObject.contains("supports_inline_queries");
}
