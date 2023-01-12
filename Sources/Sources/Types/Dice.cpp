#include "Types/Dice.h"

Telegram::Dice::Dice() :
    emoji(),
    value()
{}

Telegram::Dice::Dice(const QString& emoji, 
                     const qint32& value) :
    emoji(emoji),
    value(value)
{}

Telegram::Dice::Dice(const QJsonObject& json_object) {
    json_object.contains("emoji") ? emoji = json_object["emoji"].toString() : emoji = "";
    json_object.contains("value") ? value = json_object["value"].toInt()    : value = 0;
}

QJsonObject Telegram::Dice::toObject() const {
    if (isEmpty()) return {};

    return QJsonObject{ {"emoji", emoji}, {"value", value} };
}

bool Telegram::Dice::isEmpty() const {
    return emoji == "" and value == 0;
}          
