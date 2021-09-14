#include "Types/Dice.h"

#include "qjsonobject.h"

Telegram::Dice::Dice() :
    emoji(""),
    value(0)
{}

Telegram::Dice::Dice(const QString& emoji, 
                     const qint32& value) :
    emoji(emoji),
    value(value)
{}

Telegram::Dice::Dice(const QJsonObject& jsonObject)
{
    jsonObject.contains("emoji") ? emoji = jsonObject["emoji"].toString() : emoji = "";
    jsonObject.contains("value") ? value = jsonObject["value"].toInt()    : value = 0;
}

QJsonObject Telegram::Dice::toObject() const
{
    if (isEmpty())
        return QJsonObject();

    return QJsonObject{ {"emoji", emoji}, {"value", value} };
}

bool Telegram::Dice::isEmpty() const
{
    return emoji == "" and value == 0;
}          
