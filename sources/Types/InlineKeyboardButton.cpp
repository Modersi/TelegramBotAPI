#include "InlineKeyboardButton.h"

/*!
    \brief A default constructor. Constructs an empty object
*/
InlineKeyboardButton::InlineKeyboardButton() {}

/*!
    \brief Class contructor
    \param text Label text on the button
*/
InlineKeyboardButton::InlineKeyboardButton(QString text)
{
    _jsonObject.insert("text", text);
}

/*!
    \brief Constructor from QJsonObject
    \param QJsonObject QJsonObject which contains fields suitable for the class
*/
InlineKeyboardButton::InlineKeyboardButton(QJsonObject jsonObject)
{
    if(jsonObject.contains("text"))
        _jsonObject.insert("text", jsonObject.value("text"));

    if(jsonObject.contains("url"))
        _jsonObject.insert("url", jsonObject.value("url"));

    if(jsonObject.contains("login_url"))
        _jsonObject.insert("login_url", jsonObject.value("login_url"));

    if(jsonObject.contains("callback_data"))
        _jsonObject.insert("callback_data", jsonObject.value("callback_data"));

    if(jsonObject.contains("switch_inline_query"))
        _jsonObject.insert("switch_inline_query", jsonObject.value("switch_inline_query"));

    if(jsonObject.contains("switch_inline_query_current_chat"))
        _jsonObject.insert("switch_inline_query_current_chat", jsonObject.value("switch_inline_query_current_chat"));

    if(jsonObject.contains("callback_game"))
        _jsonObject.insert("callback_game", jsonObject.value("callback_game"));

    if(jsonObject.contains("pay"))
        _jsonObject.insert("pay", jsonObject.value("pay"));
}


/***//*!
    \brief Get **text** value
    \return Value of **text**
*/
QString InlineKeyboardButton::text()
{
    return _jsonObject.value("text").toString();
}

/*!
    \brief Set new value for **text**
    \param QString New value of **text**
*/
void InlineKeyboardButton::setText(QString text)
{
    _jsonObject.insert("text", text);
}


/***//*!
    \brief Get **url** value
    \return Value of **url**
*/
QString InlineKeyboardButton::url()
{
    return _jsonObject.value("url").toString();
}

/*!
    \brief Set new value for **url**
    \param QString New value of **url**
*/
void InlineKeyboardButton::setUrl(QString url)
{
    _jsonObject.insert("url", url);
}

/*!
    \brief Check if object has **url**
    \return `True` if has **url**, `false` if doesn't
*/
bool InlineKeyboardButton::hasUrl()
{
    return _jsonObject.contains("url");
}


/***//*!
    \brief Get **loginUrl** value
    \return Value of **loginUrl**
*/
LoginUrl InlineKeyboardButton::loginUrl()
{
    return LoginUrl(_jsonObject.value("login_url").toObject());
}

/*!
    \brief Set new value for **loginUrl**
    \param LoginUrl New value of **loginUrl**
*/
void InlineKeyboardButton::setLoginUrl(LoginUrl loginUrl)
{
    _jsonObject.insert("login_url", loginUrl.toObject());
}

/*!
    \brief Check if object has **loginUrl**
    \return `True` if has **loginUrl**, `false` if doesn't
*/
bool InlineKeyboardButton::hasLoginUrl()
{
    return _jsonObject.contains("login_url");
}


/***//*!
    \brief Get **callbackData** value
    \return Value of **callbackData**
*/
QString InlineKeyboardButton::callbackData()
{
    return _jsonObject.value("callback_data").toString();
}

/*!
    \brief Set new value for **callbackData**
    \param QString New value of **callbackData**
*/
void InlineKeyboardButton::setCallbackData(QString callbackData)
{
    _jsonObject.insert("callback_data", callbackData);
}


/*!
    \brief Check if object has **callbackData**
    \return `True` if has **callbackData**, `false` if doesn't
*/
bool InlineKeyboardButton::hasCallbackData()
{
    return _jsonObject.contains("callback_data");
}


/***//*!
    \brief Get **switchInlineQuery** value
    \return Value of **switchInlineQuery**
*/
QString InlineKeyboardButton::switchInlineQuery()
{
    return _jsonObject.value("switch_inline_query").toString();
}

/*!
    \brief Set new value for **switchInlineQuery**
    \param QString New value of **switchInlineQuery**
*/
void InlineKeyboardButton::setSwitchInlineQuery(QString switchInlineQuery)
{
    _jsonObject.insert("switch_inline_query", switchInlineQuery);
}

/*!
    \brief Check if object has **switchInlineQuery**
    \return `True` if has **switchInlineQuery**, `false` if doesn't
*/
bool InlineKeyboardButton::hasSwitchInlineQuery()
{
    return _jsonObject.contains("switch_inline_query");
}


/***//*!
    \brief Get **switchInlineQueryCurrentChat** value
    \return Value of **switchInlineQueryCurrentChat**
*/
QString InlineKeyboardButton::switchInlineQueryCurrentChat()
{
    return _jsonObject.value("switch_inline_query_current_chat").toString();
}

/*!
    \brief Set new value for **switchInlineQueryCurrentChat**
    \param QString New value of **switchInlineQueryCurrentChat**
*/
void InlineKeyboardButton::setSwitchInlineQueryCurrentChat(QString switchInlineQueryCurrentChat)
{
    _jsonObject.insert("switch_inline_query_current_chat", switchInlineQueryCurrentChat);
}

/*!
    \brief Check if object has **switchInlineQueryCurrentChat**
    \return `True` if has **switchInlineQueryCurrentChat**, `false` if doesn't
*/
bool InlineKeyboardButton::hasSwitchInlineQueryCurrentChat()
{
    return _jsonObject.contains("switch_inline_query_current_chat");
}

///***//*!
//    \brief Get **smallFileId** value
//    \return Value of **smallFileId**
//*/
//CallbackGame InlineKeyboardButton::callbackGame()
//{
//    return CallbackGame(_jsonObject.value("callback_game").toObject());
//}
//
//void InlineKeyboardButton::setCallbackGame(CallbackGame callbackGame)
//{
//    _jsonObject.insert("callback_game", callbackGame);
//}
//
//bool InlineKeyboardButton::hasCallbackGame()
//{
//    return _jsonObject.contains("callback_game");
//}


/***//*!
    \brief Get **isPay** value
    \return Value of **isPay**
*/
bool InlineKeyboardButton::isPay()
{
    return _jsonObject.value("pay").toBool();
}

/*!
    \brief Set new value for **isPay**
    \param bool New value of **isPay**
*/
void InlineKeyboardButton::setPay(bool pay)
{
    _jsonObject.insert("pay", pay);
}

/*!
    \brief Check if object has **isPay** field
    \return `True` if has **isPay** field, `false` if doesn't
*/
bool InlineKeyboardButton::hasPay()
{
    return _jsonObject.contains("pay");
}


