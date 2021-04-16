#include "Types/InputMediaVideo.h"

InputMediaVideo::InputMediaVideo() {}

InputMediaVideo::InputMediaVideo(QString media)
{
    _jsonObject.insert("type", "video");
    _jsonObject.insert("media", media);
}

InputMediaVideo::InputMediaVideo(QJsonObject jsonObject)
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

    if(jsonObject.contains("supports_streaming"))
        _jsonObject.insert("supports_streaming", jsonObject.value("supports_streaming"));
}

// "get", "set" methods for "media" field //

QString InputMediaVideo::media()
{
    return _jsonObject.value("media").toString();
}

void InputMediaVideo::setMedia(QString media)
{
    _jsonObject.insert("media", media);
}

// "get", "set", "has" methods for "thumb" field //

//InputFile InputMediaVideo::thumb()
//{
//    return InputFile(_jsonObject.value("thumb").toObject());
//}

QString InputMediaVideo::thumb()
{
    return _jsonObject.value("thumb").toString();
}

//void InputMediaVideo::setThumb(InputFile thumb)
//{
//    _jsonObject.insert("thumb", thumb);
//}

void InputMediaVideo::setThumb(QString thumb)
{
    _jsonObject.insert("thumb", thumb);
}

bool InputMediaVideo::hasThumb()
{
    return _jsonObject.contains("thumb");
}

// "get", "set", "has" methods for "caption" field //

QString InputMediaVideo::caption()
{
    return _jsonObject.value("caption").toString();
}

void InputMediaVideo::setCaption(QString caption)
{
    _jsonObject.insert("caption", caption);
}

bool InputMediaVideo::hasCaption()
{
    return _jsonObject.contains("caption");
}

// "get", "set", "has" methods for "parse_mode" field //

QString InputMediaVideo::parseMode()
{
    return _jsonObject.value("parse_mode").toString();
}

void InputMediaVideo::setParseMode(QString parseMode)
{
    _jsonObject.insert("parse_mode", parseMode);
}

bool InputMediaVideo::hasParseMode()
{
    return _jsonObject.contains("parse_mode");
}

// "get", "set", "has" methods for "width" field //

qint32 InputMediaVideo::width()
{
    return _jsonObject.value("width").toInt();
}

void InputMediaVideo::setWidth(qint32 width)
{
    _jsonObject.insert("width", width);
}

bool InputMediaVideo::hasWidth()
{
    return _jsonObject.contains("width");
}

// "get", "set", "has" methods for "height" field //

qint32 InputMediaVideo::height()
{
    return _jsonObject.value("height").toInt();
}

void InputMediaVideo::setHeight(qint32 height)
{
    _jsonObject.insert("height", height);
}

bool InputMediaVideo::hasHeight()
{
    return _jsonObject.contains("height");
}

// "get", "set", "has" methods for "duration" field //

qint32 InputMediaVideo::duration()
{
    return _jsonObject.value("duration").toInt();
}

void InputMediaVideo::setDuration(qint32 duration)
{
    _jsonObject.insert("duration", duration);
}

bool InputMediaVideo::hasDuration()
{
    return _jsonObject.contains("duration");
}

// "get", "set", "has" methods for "supports_streaming" field //

bool InputMediaVideo::supportsStreaming()
{
    return _jsonObject.value("supports_streaming").toBool();
}

void InputMediaVideo::setSupportsStreaming(bool supportsStreaming)
{
    _jsonObject.insert("supports_streaming", supportsStreaming);
}

bool InputMediaVideo::hasSupportsStreaming()
{
    return _jsonObject.contains("supports_streaming");
}
