#include "InputMediaAudio.h"

InputMediaAudio::InputMediaAudio() {}

InputMediaAudio::InputMediaAudio(QString media)
{
    _jsonObject.insert("type", "audio");
    _jsonObject.insert("media", media);
}

InputMediaAudio::InputMediaAudio(QJsonObject jsonObject)
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

    if(jsonObject.contains("duration"))
        _jsonObject.insert("duration", jsonObject.value("duration"));

    if(jsonObject.contains("performer"))
        _jsonObject.insert("performer", jsonObject.value("performer"));

    if(jsonObject.contains("title"))
        _jsonObject.insert("title", jsonObject.value("title"));
}

// "get", "set" methods for "media" field //

QString InputMediaAudio::media()
{
    return _jsonObject.value("media").toString();
}

void InputMediaAudio::setMedia(QString media)
{
    _jsonObject.insert("media", media);
}

// "get", "set", "has" methods for "thumb" field //

//InputFile InputMediaAudio::thumb()
//{
//    return InputFile(_jsonObject.value("thumb").toObject());
//}

QString InputMediaAudio::thumb()
{
    return _jsonObject.value("thumb").toString();
}

//void InputMediaAudio::setThumb(InputFile thumb)
//{
//    _jsonObject.insert("thumb", thumb);
//}

void InputMediaAudio::setThumb(QString thumb)
{
    _jsonObject.insert("thumb", thumb);
}

bool InputMediaAudio::hasThumb()
{
    return _jsonObject.contains("thumb");
}

// "get", "set", "has" methods for "caption" field //

QString InputMediaAudio::caption()
{
    return _jsonObject.value("caption").toString();
}

void InputMediaAudio::setCaption(QString caption)
{
    _jsonObject.insert("caption", caption);
}

bool InputMediaAudio::hasCaption()
{
    return _jsonObject.contains("caption");
}

// "get", "set", "has" methods for "parse_mode" field //

QString InputMediaAudio::parseMode()
{
    return _jsonObject.value("parse_mode").toString();
}

void InputMediaAudio::setParseMode(QString parseMode)
{
    _jsonObject.insert("parse_mode", parseMode);
}

bool InputMediaAudio::hasParseMode()
{
    return _jsonObject.contains("parse_mode");
}

// "get", "set", "has" methods for "performer" field //

QString InputMediaAudio::performer()
{
    return _jsonObject.value("performer").toString();
}

void InputMediaAudio::setPerformer(QString performer)
{
    _jsonObject.insert("performer", performer);
}

bool InputMediaAudio::hasPerformer()
{
    return _jsonObject.contains("performer");
}

// "get", "set", "has" methods for "title" field //

QString InputMediaAudio::title()
{
    return _jsonObject.value("title").toString();
}

void InputMediaAudio::setTitle(QString title)
{
    _jsonObject.insert("title", title);
}

bool InputMediaAudio::hasTitle()
{
    return _jsonObject.contains("title");
}
