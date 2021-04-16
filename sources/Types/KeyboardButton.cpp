#include "Types/KeyboardButton.h"

KeyboardButton::KeyboardButton()
{

}

KeyboardButton::KeyboardButton(QString text)
{
    _jsonObject.insert("text", QJsonValue(text));
}

KeyboardButton::KeyboardButton(QJsonObject jsonObject)
{
    if(jsonObject.contains("text"))
        _jsonObject.insert("text", jsonObject.value("text"));

    if(jsonObject.contains("request_contact"))
        _jsonObject.insert("request_contact", jsonObject.value("request_contact"));

    if(jsonObject.contains("request_location"))
        _jsonObject.insert("request_location", jsonObject.value("request_location"));

    if(jsonObject.contains("request_poll"))
        _jsonObject.insert("request_poll", jsonObject.value("request_poll"));
}

// "get", "set" methods for "text" field //

QString KeyboardButton::text()
{
    return _jsonObject.value("text").toString();
}

void KeyboardButton::setText(QString text)
{
    _jsonObject.insert("text", text);
}

// "get", "set", "has" methods for "request_contact" field //

bool KeyboardButton::requestContact()
{
    return _jsonObject.value("request_contact").toBool();
}

void KeyboardButton::setRequestContact(bool requestContact)
{
    _jsonObject.insert("request_contact", requestContact);
}

bool KeyboardButton::hasRequestContact()
{
    return _jsonObject.contains("request_contact");
}

// "get", "set", "has" methods for "request_contact" field //

bool KeyboardButton::requestLocation()
{
    return _jsonObject.value("request_location").toBool();
}

void KeyboardButton::setRequestLocation(bool requestLocation)
{
    _jsonObject.insert("request_location", requestLocation);
}

bool KeyboardButton::hasRequestLocation()
{
    return _jsonObject.contains("request_location");
}

// "get", "set", "has" methods for "request_contact" field //

//KeyboardButtonPollType KeyboardButton::requestPoll()
//{
//
//}
//
//void KeyboardButton::setRequestPoll(KeyboardButtonPollType requestPoll)
//{
//
//}
//
//bool KeyboardButton::hasRequestPoll()
//{
//
//}
