#include "Voice.h"

Voice::Voice() {}

Voice::Voice(QString fileId,
             QString fileUniqueId,
             qint32  duration,
             QString mimeType,
             qint32  fileSize)
{
    _jsonObject.insert("file_id", QJsonValue(fileId));
    _jsonObject.insert("file_unique_id", QJsonValue(fileUniqueId));
    _jsonObject.insert("duration", QJsonValue(duration));

    if(!mimeType.isEmpty())
        _jsonObject.insert("mime_type", QJsonValue(mimeType));
    if(fileSize != 0)
        _jsonObject.insert("file_size", QJsonValue(fileSize));
}

Voice::Voice(QJsonObject jsonObject)
{
    if(jsonObject.contains("file_id"))
        _jsonObject.insert("file_id", jsonObject.value("file_id"));

    if(jsonObject.contains("file_unique_id"))
        _jsonObject.insert("file_unique_id", jsonObject.value("file_unique_id"));

    if(jsonObject.contains("duration"))
        _jsonObject.insert("duration", jsonObject.value("duration"));

    if(jsonObject.contains("mime_type"))
        _jsonObject.insert("mime_type", jsonObject.value("mime_type"));

    if(jsonObject.contains("file_size"))
        _jsonObject.insert("file_size", jsonObject.value("file_size"));
}

// "get", "set" methods for "file_id" field //

QString Voice::fileId()
{
    return _jsonObject.value("file_id").toString();
}

void Voice::setFileId(QString fileId)
{
    _jsonObject.insert("file_id", fileId);
}

// "get", "set" methods for "file_unique_id" field //

QString Voice::fileUniqueId()
{
    return _jsonObject.value("file_unique_id").toString();
}

void Voice::setFileUniqueId(QString fileUniqueId)
{
    _jsonObject.insert("file_unique_id", fileUniqueId);
}

// "get", "set" methods for "duration" field //

qint32 Voice::duration()
{
    return _jsonObject.value("duration").toInt();
}

void Voice::setDuration(qint32 duration)
{
    _jsonObject.insert("duration", duration);
}

// "get", "set", "has" methods for "mime_type" field //

QString Voice::mimeType()
{
    return _jsonObject.value("mime_type").toString();
}

void Voice::setMimeType(QString mimeType)
{
    _jsonObject.insert("mime_type", mimeType);
}

bool Voice::hasMimeType()
{
    return _jsonObject.contains("mime_type");
}

// "get", "set", "has" methods for "file_size" field //

qint32 Voice::fileSize()
{
    return _jsonObject.value("file_size").toInt();
}

void Voice::setFileSize(qint32 fileSize)
{
    _jsonObject.insert("file_size", fileSize);
}

bool Voice::hasFileSize()
{
    return _jsonObject.contains("file_size");
}
