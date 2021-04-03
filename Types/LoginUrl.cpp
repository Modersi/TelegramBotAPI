#include "LoginUrl.h"

LoginUrl::LoginUrl()
{

}

LoginUrl::LoginUrl(QString url,
                   QString forwardText,
                   QString botUsername,
                   bool    requestWriteAccess)
{
    _jsonObject.insert("url", QJsonValue(url));

    if(!forwardText.isEmpty())
        _jsonObject.insert("forward_text", QJsonValue(forwardText));
    if(!botUsername.isEmpty())
        _jsonObject.insert("bot_username", QJsonValue(botUsername));
    if(requestWriteAccess != false)
        _jsonObject.insert("request_write_access", QJsonValue(requestWriteAccess));
}

LoginUrl::LoginUrl(QJsonObject jsonObject)
{
    if(jsonObject.contains("url"))
        _jsonObject.insert("url", jsonObject.value("url"));

    if(jsonObject.contains("forward_text"))
        _jsonObject.insert("forward_text", jsonObject.value("forward_text"));

    if(jsonObject.contains("bot_username"))
        _jsonObject.insert("bot_username", jsonObject.value("bot_username"));

    if(jsonObject.contains("request_write_access"))
        _jsonObject.insert("request_write_access", jsonObject.value("request_write_access"));

}

// "get", "set" methods for "url" field //

QString LoginUrl::url()
{
    return _jsonObject.value("url").toString();
}

void LoginUrl::setUrl(QString url)
{
    _jsonObject.insert("url", url);
}

// "get", "set", "has" methods for "forward_text" field //

QString LoginUrl::forwardText()
{
    return _jsonObject.value("forward_text").toString();
}

void LoginUrl::setForwardText(QString forwardText)
{
    _jsonObject.insert("forward_text", forwardText);
}

bool LoginUrl::hasForwardText()
{
    return _jsonObject.contains("forward_text");
}

// "get", "set", "has" methods for "bot_username" field //

QString LoginUrl::botUsername()
{
    return _jsonObject.value("bot_username").toString();
}

void LoginUrl::setBotUsername(QString botUsername)
{
    _jsonObject.insert("bot_username", botUsername);
}

bool LoginUrl::hasBotUsername()
{
    return _jsonObject.contains("bot_username");
}

// "get", "set", "has" methods for "request_write_access" field //

bool LoginUrl::requestWriteAccess()
{
    return _jsonObject.value("request_write_access").toBool();
}

void LoginUrl::setRequestWriteAccess(bool requestWriteAccess)
{
    _jsonObject.insert("request_write_access", requestWriteAccess);
}

bool LoginUrl::hasRequestWriteAccess()
{
    return _jsonObject.contains("request_write_access");
}
