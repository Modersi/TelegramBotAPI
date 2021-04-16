#include "Types/InputMediaPhoto.h"

InputMediaPhoto::InputMediaPhoto() {}

InputMediaPhoto::InputMediaPhoto(QString media)
{
    _jsonObject.insert("type", "photo");
    _jsonObject.insert("media", media);
}

InputMediaPhoto::InputMediaPhoto(QJsonObject jsonObject)
{
    if(jsonObject.contains("type"))
        _jsonObject.insert("type", jsonObject.value("type"));

    if(jsonObject.contains("media"))
        _jsonObject.insert("media", jsonObject.value("media"));

    if(jsonObject.contains("caption"))
        _jsonObject.insert("caption", jsonObject.value("caption"));

    if(jsonObject.contains("parse_mode"))
        _jsonObject.insert("parse_mode", jsonObject.value("parse_mode"));
}

// "get", "set" methods for "media" field //

QString InputMediaPhoto::media()
{
    return _jsonObject.value("media").toString();
}

void InputMediaPhoto::setMedia(QString media)
{
    _jsonObject.insert("media", media);
}

// "get", "set", "has" methods for "caption" field //

QString InputMediaPhoto::caption()
{
    return _jsonObject.value("caption").toString();
}

void InputMediaPhoto::setCaption(QString caption)
{
    _jsonObject.insert("caption", caption);
}

bool InputMediaPhoto::hasCaption()
{
    return _jsonObject.contains("caption");
}

// "get", "set", "has" methods for "parse_mode" field //

QString InputMediaPhoto::parseMode()
{
    return _jsonObject.value("parse_mode").toString();
}

void InputMediaPhoto::setParseMode(QString parseMode)
{
    _jsonObject.insert("parse_mode", parseMode);
}

bool InputMediaPhoto::hasParseMode()
{
    return _jsonObject.contains("parse_mode");
}
