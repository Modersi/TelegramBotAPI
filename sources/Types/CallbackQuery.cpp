#include "Types/CallbackQuery.h"

/*!
    \brief A default constructor. Constructs an empty object
*/
CallbackQuery::CallbackQuery() {}

/*!
    \brief Class contructor
    \param id            Unique identifier for this query
    \param from          Sender
    \param chatInstance  Global identifier, uniquely corresponding to the chat to which the message with the callback button was sent
*/
CallbackQuery::CallbackQuery(QString id,
                             User    from,
                             QString chatInstance)
{
    _jsonObject.insert("id", id);
    _jsonObject.insert("from", from.toObject());
    _jsonObject.insert("chat_instance", chatInstance);
}

/*!
    \brief Constructor from QJsonObject
    \param QJsonObject QJsonObject which contains fields suitable for the class
*/
CallbackQuery::CallbackQuery(QJsonObject jsonObject)
{
    if(jsonObject.contains("id"))
        _jsonObject.insert("id", jsonObject.value("id"));

    if(jsonObject.contains("from"))
        _jsonObject.insert("from", jsonObject.value("from"));

    if(jsonObject.contains("message"))
        _jsonObject.insert("message", jsonObject.value("message"));

    if(jsonObject.contains("inline_message_id"))
        _jsonObject.insert("inline_message_id", jsonObject.value("inline_message_id"));

    if(jsonObject.contains("chat_instance"))
        _jsonObject.insert("chat_instance", jsonObject.value("chat_instance"));

    if(jsonObject.contains("data"))
        _jsonObject.insert("data", jsonObject.value("data"));

    if(jsonObject.contains("game_short_name"))
        _jsonObject.insert("game_short_name", jsonObject.value("game_short_name"));
}


/***//*!
    \brief Get **id** value
    \return Value of **id**
*/
QString CallbackQuery::id()
{
    return _jsonObject.value("id").toString();
}

/*!
    \brief Set new value for **id**
    \param QString New value of **id**
*/
void CallbackQuery::setId(QString id)
{
    _jsonObject.insert("id", id);
}


/***//*!
    \brief Get **user** value
    \return Value of **user** in form of `User` object
*/
User CallbackQuery::user()
{
    return User(_jsonObject.value("user").toObject());
}

/*!
    \brief Set new value for **user**
    \param User New value of **user**
*/
void CallbackQuery::setUser(User user)
{
    _jsonObject.insert("user", user.toObject());
}


/***//*!
    \brief Get **chatInstance** value
    \return Value of **chatInstance**
*/
QString CallbackQuery::chatInstance()
{
    return _jsonObject.value("chat_instance").toString();
}

/*!
    \brief Set new value for **chatInstance**
    \param QString New value of **chatInstance**
*/
void CallbackQuery::setChatInstance(QString chatInstance)
{
    _jsonObject.insert("chat_instance", chatInstance);
}


/***//*!
    \brief Get **message** value
    \return Value of **message** in form of `Message` object
*/
Message CallbackQuery::message()
{
    return Message(_jsonObject.value("message").toObject());
}

/*!
    \brief Set new value for **message**
    \param QString New value of **message**
*/
void CallbackQuery::setMessage(Message message)
{
    _jsonObject.insert("message", message.toObject());
}

/*!
    \brief Check if object has **message**
    \return `True` if has **message**, `false` if doesn't
*/
bool CallbackQuery::hasMessage()
{
    return _jsonObject.contains("message");
}


/***//*!
    \brief Get **inlineMessageId** value
    \return Value of **inlineMessageId**
*/
QString CallbackQuery::inlineMessageId()
{
    return _jsonObject.value("inline_message_id").toString();
}

/*!
    \brief Set new value for **inlineMessageId**
    \param QString New value of **inlineMessageId**
*/
void CallbackQuery::setInlineMessageId(QString inlineMessageId)
{
    _jsonObject.insert("inline_message_id", inlineMessageId);
}

/*!
    \brief Check if object has **inlineMessageId**
    \return `True` if has **inlineMessageId**, `false` if doesn't
*/
bool CallbackQuery::hasInlineMessageId()
{
    return _jsonObject.contains("inline_message_id");
}


/***//*!
    \brief Get **data** value
    \return Value of **data**
*/
QString CallbackQuery::data()
{
    return _jsonObject.value("data").toString();
}

/*!
    \brief Set new value for **data**
    \param QString New value of **data**
*/
void CallbackQuery::setData(QString data)
{
    _jsonObject.insert("data", data);
}

/*!
    \brief Check if object has **data**
    \return `True` if has **data**, `false` if doesn't
*/
bool CallbackQuery::hasData()
{
    return _jsonObject.contains("data");
}


/***//*!
    \brief Get **gameShortName** value
    \return Value of **gameShortName**
*/
QString CallbackQuery::gameShortName()
{
    return _jsonObject.value("game_short_name").toString();
}

/*!
    \brief Set new value for **gameShortName**
    \param QString New value of **gameShortName**
*/
void CallbackQuery::setGameShortName(QString gameShortName)
{
    _jsonObject.insert("game_short_name", gameShortName);
}

/*!
    \brief Check if object has **gameShortName**
    \return `True` if has **gameShortName**, `false` if doesn't
*/
bool CallbackQuery::hasGameShortName()
{
    return _jsonObject.contains("game_short_name");
}
