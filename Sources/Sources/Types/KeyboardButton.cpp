#include "Types/KeyboardButton.h"

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

Telegram::KeyboardButton::KeyboardButton(const QJsonObject& json_object)
{
    json_object.contains("text")             ? text = json_object["text"].toString()                                         : text = "";
    json_object.contains("request_contact")  ? request_contact = json_object["request_contact"].toBool()                     : request_contact = std::nullopt;
    json_object.contains("request_location") ? request_location = json_object["request_location"].toBool()                   : request_location = std::nullopt;
    json_object.contains("request_poll")     ? request_poll = KeyboardButtonPollType(json_object["request_poll"].toObject()) : request_poll = std::nullopt;
}

QJsonObject Telegram::KeyboardButton::toObject() const {
    if (isEmpty()) return {};

    QJsonObject keyboard_button_json_object{ {"text", text} };

    if (request_contact.has_value())		keyboard_button_json_object.insert("request_contact", *request_contact);
    if (request_location.has_value())		keyboard_button_json_object.insert("request_location", *request_location);
    if (request_poll.has_value())			keyboard_button_json_object.insert("request_poll", request_poll->toObject());

    return keyboard_button_json_object;
}

bool Telegram::KeyboardButton::isEmpty() const {
    return text == ""
           and request_contact == std::nullopt
           and request_location == std::nullopt
           and request_poll == std::nullopt;
}
