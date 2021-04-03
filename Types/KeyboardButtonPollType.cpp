#include "KeyboardButtonPollType.h"

KeyboardButtonPollType::KeyboardButtonPollType() {}

KeyboardButtonPollType::KeyboardButtonPollType(QString type)
{
    _jsonObject.insert("type", QJsonValue(type));
}

KeyboardButtonPollType::KeyboardButtonPollType(QJsonObject jsonObject)
{
    if(jsonObject.contains("type"))
        _jsonObject.insert("type", jsonObject.value("type"));
}

// "get", "set" methods for "type" field //

QString KeyboardButtonPollType::type()
{
    return _jsonObject.value("type").toString();
}

void KeyboardButtonPollType::setType(QString type)
{
     _jsonObject.insert("type", type);
}
