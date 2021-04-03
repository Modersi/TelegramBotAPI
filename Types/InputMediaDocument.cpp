#include "InputMediaDocument.h"

InputMediaDocument::InputMediaDocument() {}

InputMediaDocument::InputMediaDocument(QString media)
{
    _jsonObject.insert("type", "document");
    _jsonObject.insert("media", media);
}

InputMediaDocument::InputMediaDocument(QJsonObject jsonObject)
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
}

// "get", "set" methods for "media" field //

QString InputMediaDocument::media()
{
    return _jsonObject.value("media").toString();
}

void InputMediaDocument::setMedia(QString media)
{
    _jsonObject.insert("media", media);
}

// "get", "set", "has" methods for "thumb" field //

//InputFile InputMediaDocument::thumb()
//{
//    return InputFile(_jsonObject.value("thumb").toObject());
//}

QString InputMediaDocument::thumb()
{
    return _jsonObject.value("thumb").toString();
}

//void InputMediaDocument::setThumb(InputFile thumb)
//{
//    _jsonObject.insert("thumb", thumb);
//}

void InputMediaDocument::setThumb(QString thumb)
{
    _jsonObject.insert("thumb", thumb);
}

bool InputMediaDocument::hasThumb()
{
    return _jsonObject.contains("thumb");
}

// "get", "set", "has" methods for "caption" field //

QString InputMediaDocument::caption()
{
    return _jsonObject.value("caption").toString();
}

void InputMediaDocument::setCaption(QString caption)
{
    _jsonObject.insert("caption", caption);
}

bool InputMediaDocument::hasCaption()
{
    return _jsonObject.contains("caption");
}

// "get", "set", "has" methods for "parse_mode" field //

QString InputMediaDocument::parseMode()
{
    return _jsonObject.value("parse_mode").toString();
}

void InputMediaDocument::setParseMode(QString parseMode)
{
    _jsonObject.insert("parse_mode", parseMode);
}

bool InputMediaDocument::hasParseMode()
{
    return _jsonObject.contains("parse_mode");
}

