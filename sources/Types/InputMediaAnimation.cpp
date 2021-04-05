#include "InputMediaAnimation.h"

InputMediaAnimation::InputMediaAnimation() {}

InputMediaAnimation::InputMediaAnimation(QString media)
{
    _jsonObject.insert("type", "animation");
    _jsonObject.insert("media", media);
}

InputMediaAnimation::InputMediaAnimation(QJsonObject jsonObject)
{
    if(jsonObject.contains("type"))
        _jsonObject.insert("type", jsonObject.value("type"));

    if(jsonObject.contains("media"))
        _jsonObject.insert("media", jsonObject.value("media"));

    if(jsonObject.contains("thumb"))
        _jsonObject.insert("thumb", jsonObject.value("thumb"));

    if(jsonObject.contains("caption"))
        _jsonObject.insert("caption", jsonObject.value("caption"));

    if(jsonObject.contains("parse_mode"))
        _jsonObject.insert("parse_mode", jsonObject.value("parse_mode"));

    if(jsonObject.contains("width"))
        _jsonObject.insert("width", jsonObject.value("width"));

    if(jsonObject.contains("height"))
        _jsonObject.insert("height", jsonObject.value("height"));

    if(jsonObject.contains("duration"))
        _jsonObject.insert("duration", jsonObject.value("duration"));
}
// "get", "set" methods for "media" field //

QString InputMediaAnimation::media()
{
    return _jsonObject.value("media").toString();
}

void InputMediaAnimation::setMedia(QString media)
{
    _jsonObject.insert("media", media);
}

// "get", "set", "has" methods for "thumb" field //

//InputFile InputMediaAnimation::thumb()
//{
//    return InputFile(_jsonObject.value("thumb").toObject());
//}

QString InputMediaAnimation::thumb()
{
    return _jsonObject.value("thumb").toString();
}

//void InputMediaAnimation::setThumb(InputFile thumb)
//{
//    _jsonObject.insert("thumb", thumb);
//}

void InputMediaAnimation::setThumb(QString thumb)
{
    _jsonObject.insert("thumb", thumb);
}

bool InputMediaAnimation::hasThumb()
{
    return _jsonObject.contains("thumb");
}

// "get", "set", "has" methods for "caption" field //

QString InputMediaAnimation::caption()
{
    return _jsonObject.value("caption").toString();
}

void InputMediaAnimation::setCaption(QString caption)
{
    _jsonObject.insert("caption", caption);
}

bool InputMediaAnimation::hasCaption()
{
    return _jsonObject.contains("caption");
}

// "get", "set", "has" methods for "parse_mode" field //

QString InputMediaAnimation::parseMode()
{
    return _jsonObject.value("parse_mode").toString();
}

void InputMediaAnimation::setParseMode(QString parseMode)
{
    _jsonObject.insert("parse_mode", parseMode);
}

bool InputMediaAnimation::hasParseMode()
{
    return _jsonObject.contains("parse_mode");
}

// "get", "set", "has" methods for "width" field //

qint32 InputMediaAnimation::width()
{
    return _jsonObject.value("width").toInt();
}

void InputMediaAnimation::setWidth(qint32 width)
{
    _jsonObject.insert("width", width);
}

bool InputMediaAnimation::hasWidth()
{
    return _jsonObject.contains("width");
}

// "get", "set", "has" methods for "height" field //

qint32 InputMediaAnimation::height()
{
    return _jsonObject.value("height").toInt();
}

void InputMediaAnimation::setHeight(qint32 height)
{
    _jsonObject.insert("height", height);
}

bool InputMediaAnimation::hasHeight()
{
    return _jsonObject.contains("height");
}

// "get", "set", "has" methods for "duration" field //

qint32 InputMediaAnimation::duration()
{
    return _jsonObject.value("duration").toInt();
}

void InputMediaAnimation::setDuration(qint32 duration)
{
    _jsonObject.insert("duration", duration);
}

bool InputMediaAnimation::hasDuration()
{
    return _jsonObject.contains("duration");
}
