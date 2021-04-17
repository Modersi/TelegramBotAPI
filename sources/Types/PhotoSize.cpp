#include "Types/PhotoSize.h"

PhotoSize::PhotoSize() {}

PhotoSize::PhotoSize(QString fileId,
                     QString fileUniqueId,
                     qint32  width,
                     qint32  height,
                     qint32  fileSize)
{
    _jsonObject.insert("file_id", QJsonValue(fileId));
    _jsonObject.insert("file_unique_id", QJsonValue(fileUniqueId));
    _jsonObject.insert("width", QJsonValue(width));
    _jsonObject.insert("height", QJsonValue(height));

    if(fileSize != 0)
        _jsonObject.insert("file_size", QJsonValue(fileSize));
}

PhotoSize::PhotoSize(QJsonObject jsonObject)
{
    if(jsonObject.contains("file_id"))
        _jsonObject.insert("file_id", jsonObject.value("file_id"));

    if(jsonObject.contains("file_unique_id"))
        _jsonObject.insert("file_unique_id", jsonObject.value("file_unique_id"));

    if(jsonObject.contains("width"))
        _jsonObject.insert("width", jsonObject.value("width"));

    if(jsonObject.contains("height"))
        _jsonObject.insert("height", jsonObject.value("height"));

    if(jsonObject.contains("file_size"))
        _jsonObject.insert("file_size", jsonObject.value("file_size"));
}

// "get", "set" methods for "file_id" field //

QString PhotoSize::fileId()
{
    return _jsonObject.value("file_id").toString();
}

void PhotoSize::setFileId(QString fileId)
{
    _jsonObject.insert("file_id", fileId);
}

// "get", "set" methods for "file_unique_id" field //

QString PhotoSize::fileUniqueId()
{
    return _jsonObject.value("file_unique_id").toString();
}

void PhotoSize::setFileUniqueId(QString fileUniqueId)
{
    _jsonObject.insert("file_unique_id", fileUniqueId);
}

// "get", "set" methods for "width" field //

qint32 PhotoSize::width()
{
    return _jsonObject.value("width").toInt();
}

void PhotoSize::setWidth(qint32 width)
{
    _jsonObject.insert("width", width);
}

// "get", "set" methods for "height" field //

qint32 PhotoSize::height()
{
    return _jsonObject.value("height").toInt();
}

void PhotoSize::setHeight(qint32 height)
{
    _jsonObject.insert("height", height);
}

// "get", "set", "has" methods for "file_size" field //

qint32 PhotoSize::fileSize()
{
    return _jsonObject.value("file_size").toInt();
}

void PhotoSize::setFileSize(qint32 fileSize)
{
    _jsonObject.insert("file_size", fileSize);
}

bool PhotoSize::hasFileSize()
{
    return _jsonObject.contains("file_size");
}

