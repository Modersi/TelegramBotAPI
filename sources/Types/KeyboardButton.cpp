#include "Types/KeyboardButton.h"

#include "qjsonobject.h"

Telegram::KeyboardButton::KeyboardButton() :
    text(),
    request_contact(),
    request_location(),
    request_poll()
{}

Telegram::KeyboardButton::KeyboardButton(const QString& text, 
                                         const std::optional<bool>& request_contact, 
                                         const std::optional<bool>& request_location, 
                                         const std::optional<KeyboardButtonPollType>& request_poll) :
    text(text),
    request_contact(request_contact),
    request_location(request_location),
    request_poll(request_poll)
{}

Telegram::KeyboardButton::KeyboardButton(const QJsonObject& jsonObject)
{
    jsonObject.contains("text")             ? text = jsonObject["text"].toString()                                         : text = "";
    jsonObject.contains("request_contact")  ? request_contact = jsonObject["request_contact"].toBool()                     : request_contact = std::nullopt;
    jsonObject.contains("request_location") ? request_location = jsonObject["request_location"].toBool()                   : request_location = std::nullopt;
    jsonObject.contains("request_poll")     ? request_poll = KeyboardButtonPollType(jsonObject["request_poll"].toObject()) : request_poll = std::nullopt;
}

QJsonObject Telegram::KeyboardButton::toObject() const
{
    if (isEmpty())
        return QJsonObject();

    QJsonObject keyboardButtonJsonObject{ {"text", text} };

    if (request_contact.has_value())		keyboardButtonJsonObject.insert("request_contact", *request_contact);
    if (request_location.has_value())		keyboardButtonJsonObject.insert("request_location", *request_location);
    if (request_poll.has_value())			keyboardButtonJsonObject.insert("request_poll", request_poll->toObject());

    return keyboardButtonJsonObject;
}

bool Telegram::KeyboardButton::isEmpty() const
{
    return text == ""
           and request_contact == std::nullopt
           and request_location == std::nullopt
           and request_poll == std::nullopt;
}
