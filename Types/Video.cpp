#include "Video.h"

Video::Video()
{

}

Video::Video(QString    fileId,
             QString    fileUniqueId,
             qint32     width,
             qint32     height,
             qint32     duration,
             PhotoSize  thumb,
             QString    mimeType,
             qint32     fileSize)
{
    _jsonObject.insert("file_id", QJsonValue(fileId));
    _jsonObject.insert("file_unique_id", QJsonValue(fileUniqueId));
    _jsonObject.insert("width", QJsonValue(width));
    _jsonObject.insert("height", QJsonValue(height));
    _jsonObject.insert("duration", QJsonValue(duration));

    if(!thumb.isEmpty())
        _jsonObject.insert("thumb", QJsonValue(thumb.toObject()));
    if(!mimeType.isEmpty())
        _jsonObject.insert("mime_type", QJsonValue(mimeType));
    if(fileSize != 0)
        _jsonObject.insert("file_size", QJsonValue(fileSize));
}

Video::Video(QJsonObject jsonObject)
{
    if(jsonObject.contains("file_id"))
        _jsonObject.insert("file_id", jsonObject.value("file_id"));

    if(jsonObject.contains("file_unique_id"))
        _jsonObject.insert("file_unique_id", jsonObject.value("file_unique_id"));

    if(jsonObject.contains("width"))
        _jsonObject.insert("width", jsonObject.value("width"));

    if(jsonObject.contains("height"))
        _jsonObject.insert("height", jsonObject.value("height"));

    if(jsonObject.contains("duration"))
        _jsonObject.insert("duration", jsonObject.value("duration"));

    if(jsonObject.contains("thumb"))
        _jsonObject.insert("thumb", jsonObject.value("thumb"));

    if(jsonObject.contains("mime_type"))
        _jsonObject.insert("mime_type", jsonObject.value("mime_type"));

    if(jsonObject.contains("file_size"))
        _jsonObject.insert("file_size", jsonObject.value("file_size"));
}

// "get", "set" methods for "file_id" field //

QString Video::fileId()
{
    return _jsonObject.value("file_id").toString();
}

void Video::setFileId(QString fileId)
{
    _jsonObject.insert("file_id", fileId);
}

// "get", "set" methods for "file_unique_id" field //

QString Video::fileUniqueId()
{
    return _jsonObject.value("file_unique_id").toString();
}

void Video::setFileUniqueId(QString fileUniqueId)
{
    _jsonObject.insert("file_unique_id", fileUniqueId);
}

// "get", "set" methods for "width" field //

qint32 Video::width()
{
    return _jsonObject.value("width").toInt();
}

void Video::setWidth(qint32 width)
{
    _jsonObject.insert("width", width);
}

// "get", "set" methods for "height" field //

qint32 Video::height()
{
    return _jsonObject.value("height").toInt();
}

void Video::setHeight(qint32 height)
{
    _jsonObject.insert("height", height);
}

// "get", "set" methods for "duration" field //

qint32 Video::duration()
{
    return _jsonObject.value("duration").toInt();
}

void Video::setDuration(qint32 duration)
{
    _jsonObject.insert("duration", duration);
}

// "get", "set", "has" methods for "thumb" field //

PhotoSize Video::thumb()
{
    return PhotoSize(_jsonObject.value("thumb").toObject());
}

void Video::setThumb(PhotoSize thumb)
{
    _jsonObject.insert("thumb", thumb.toObject());
}

bool Video::hasThumb()
{
    return _jsonObject.contains("thumb");
}

// "get", "set", "has" methods for "mime_type" field //

QString Video::mimeType()
{
    return _jsonObject.value("mime_type").toString();
}

void Video::setMimeType(QString mimeType)
{
    _jsonObject.insert("mime_type", mimeType);
}

bool Video::hasMimeType()
{
    return _jsonObject.contains("mime_type");
}

// "get", "set", "has" methods for "file_size" field //

qint32 Video::fileSize()
{
    return _jsonObject.value("file_size").toInt();
}

void Video::setFileSize(qint32 fileSize)
{
    _jsonObject.insert("file_size", fileSize);
}

bool Video::hasFileSize()
{
    return _jsonObject.contains("file_size");
}
