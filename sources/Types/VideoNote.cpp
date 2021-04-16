#include "Types/VideoNote.h"

VideoNote::VideoNote() {}

VideoNote::VideoNote(QString    fileId,
                     QString    fileUniqueId,
                     qint32     length,
                     qint32     duration,
                     PhotoSize  thumb,
                     qint32     fileSize)
{
    _jsonObject.insert("file_id", QJsonValue(fileId));
    _jsonObject.insert("file_unique_id", QJsonValue(fileUniqueId));
    _jsonObject.insert("length", QJsonValue(length));
    _jsonObject.insert("duration", QJsonValue(duration));

    if(!thumb.isEmpty())
        _jsonObject.insert("thumb", QJsonValue(thumb.toObject()));
    if(fileSize != 0)
        _jsonObject.insert("file_size", QJsonValue(fileSize));
}

VideoNote::VideoNote(QJsonObject jsonObject)
{
    if(jsonObject.contains("file_id"))
        _jsonObject.insert("file_id", jsonObject.value("file_id"));

    if(jsonObject.contains("file_unique_id"))
        _jsonObject.insert("file_unique_id", jsonObject.value("file_unique_id"));

    if(jsonObject.contains("length"))
        _jsonObject.insert("length", jsonObject.value("length"));

    if(jsonObject.contains("duration"))
        _jsonObject.insert("duration", jsonObject.value("duration"));

    if(jsonObject.contains("thumb"))
        _jsonObject.insert("thumb", jsonObject.value("thumb"));

    if(jsonObject.contains("file_size"))
        _jsonObject.insert("file_size", jsonObject.value("file_size"));
}

// "get", "set" methods for "file_id" field //

QString VideoNote::fileId()
{
    return _jsonObject.value("file_id").toString();
}

void VideoNote::setFileId(QString fileId)
{
    _jsonObject.insert("file_id", fileId);
}

// "get", "set" methods for "file_unique_id" field //

QString VideoNote::fileUniqueId()
{
    return _jsonObject.value("file_unique_id").toString();
}

void VideoNote::setFileUniqueId(QString fileUniqueId)
{
    _jsonObject.insert("file_unique_id", fileUniqueId);
}

// "get", "set" methods for "length" field //

qint32 VideoNote::length()
{
    return _jsonObject.value("length").toInt();
}

void VideoNote::setLength(qint32 length)
{
    _jsonObject.insert("length", length);
}

// "get", "set" methods for "duration" field //

qint32 VideoNote::duration()
{
    return _jsonObject.value("duration").toInt();
}

void VideoNote::setDuration(qint32 duration)
{
    _jsonObject.insert("duration", duration);
}

// "get", "set", "has" methods for "thumb" field //

PhotoSize VideoNote::thumb()
{
    return PhotoSize(_jsonObject.value("thumb").toObject());
}

void VideoNote::setThumb(PhotoSize thumb)
{
    _jsonObject.insert("thumb", thumb.toObject());
}

bool VideoNote::hasThumb()
{
    return _jsonObject.contains("thumb");
}

// "get", "set", "has" methods for "file_size" field //

qint32 VideoNote::fileSize()
{
    return _jsonObject.value("file_size").toInt();
}

void VideoNote::setFileSize(qint32 fileSize)
{
    _jsonObject.insert("file_size", fileSize);
}

bool VideoNote::hasFileSize()
{
    return _jsonObject.contains("file_size");
}
