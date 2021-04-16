#include "Types/Document.h"

/*!
    \brief A default constructor. Constructs an empty object
*/
Document::Document() {}

/*!
    \brief Class contructor
    \param fileId        Identifier for this file
    \param fileUniqueId  Unique identifier for this file
*/
Document::Document(QString   fileId,
                   QString   fileUniqueId)
{
    _jsonObject.insert("file_id", fileId);
    _jsonObject.insert("file_unique_id", fileUniqueId);
}

/*!
    \brief Constructor from QJsonObject
    \param QJsonObject QJsonObject which contains fields suitable for the class
*/
Document::Document(QJsonObject jsonObject)
{
    if(jsonObject.contains("file_id"))
        _jsonObject.insert("file_id", jsonObject.value("file_id"));

    if(jsonObject.contains("file_unique_id"))
        _jsonObject.insert("file_unique_id", jsonObject.value("file_unique_id"));

    if(jsonObject.contains("thumb"))
        _jsonObject.insert("thumb", jsonObject.value("thumb"));

    if(jsonObject.contains("file_name"))
        _jsonObject.insert("file_name", jsonObject.value("file_name"));

    if(jsonObject.contains("mime_type"))
        _jsonObject.insert("mime_type", jsonObject.value("mime_type"));

    if(jsonObject.contains("file_size"))
        _jsonObject.insert("file_size", jsonObject.value("file_size"));
}


/***//*!
    \brief Get **fileId** value
    \return Value of **fileId**
*/
QString Document::fileId()
{
    return _jsonObject.value("file_id").toString();
}

/*!
    \brief Set new value for **fileId**
    \param QString New value of **fileId**
*/
void Document::setFileId(QString fileId)
{
    _jsonObject.insert("file_id", fileId);
}


/***//*!
    \brief Get **fileUniqueId** value
    \return Value of **fileUniqueId**
*/
QString Document::fileUniqueId()
{
    return _jsonObject.value("file_unique_id").toString();
}

/*!
    \brief Set new value for **fileUniqueId**
    \param QString New value of **fileUniqueId**
*/
void Document::setFileUniqueId(QString fileUniqueId)
{
     _jsonObject.insert("file_unique_id", fileUniqueId);
}


/***//*!
    \brief Get **thumb** value
    \return Value of **thumb**
*/
PhotoSize Document::thumb()
{
    return PhotoSize(_jsonObject.value("thumb").toObject());
}

/*!
    \brief Set new value for **thumb**
    \param PhotoSize New value of **thumb**
*/
void Document::setThumb(PhotoSize thumb)
{
    _jsonObject.insert("thumb", thumb.toObject());
}

/*!
    \brief Check if object has **thumb**
    \return `True` if has **thumb**, `false` if doesn't
*/
bool Document::hasThumb()
{
    return _jsonObject.contains("thumb");
}


/***//*!
    \brief Get **fileName** value
    \return Value of **fileName**
*/
QString Document::fileName()
{
    return _jsonObject.value("file_name").toString();
}

/*!
    \brief Set new value for **fileName**
    \param QString New value of **fileName**
*/
void Document::setFileName(QString fileName)
{
    _jsonObject.insert("file_name", fileName);
}

/*!
    \brief Check if object has **fileName**
    \return `True` if has **fileName**, `false` if doesn't
*/
bool Document::hasFileName()
{
    return _jsonObject.contains("file_name");
}


/***//*!
    \brief Get **mimeType** value
    \return Value of **mimeType**
*/
QString Document::mimeType()
{
    return _jsonObject.value("mime_type").toString();
}

/*!
    \brief Set new value for **mimeType**
    \param QString New value of **mimeType**
*/
void Document::setMimeType(QString mimeType)
{
    _jsonObject.insert("mime_type", mimeType);
}

/*!
    \brief Check if object has **mimeType**
    \return `True` if has **mimeType**, `false` if doesn't
*/
bool Document::hasMimeType()
{
    return _jsonObject.contains("mime_type");
}


/***//*!
    \brief Get **fileSize** value
    \return Value of **fileSize**
*/
qint32 Document::fileSize()
{
    return _jsonObject.value("file_size").toInt();
}

/*!
    \brief Set new value for **fileSize**
    \param qint32 New value of **fileSize**
*/
void Document::setFileSize(qint32 fileSize)
{
    _jsonObject.insert("file_size", fileSize);
}

/*!
    \brief Check if object has **fileSize**
    \return `True` if has **fileSize**, `false` if doesn't
*/
bool Document::hasFileSize()
{
    return _jsonObject.contains("file_size");
}
