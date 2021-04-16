#include "Types/Audio.h"

/*!
    \brief A default constructor. Constructs an empty object
*/
Audio::Audio() {}

/*!
    \brief Class contructor
    \param fileId       Identifier for this file
    \param fileUniqueId Unique identifier for this file, which is supposed to be the same over time and for different bots
    \param duration     Duration of the audio in seconds as defined by sender
*/
Audio::Audio(QString    fileId,
             QString    fileUniqueId,
             qint32     duration)
{
    _jsonObject.insert("file_id", fileId);
    _jsonObject.insert("file_unique_id", fileUniqueId);
    _jsonObject.insert("duration", duration);
}

/*!
    \brief Constructor from QJsonObject
    \param QJsonObject QJsonObject which contains fields suitable for the class
*/
Audio::Audio(QJsonObject jsonObject)
{
    if(jsonObject.contains("file_id"))
        _jsonObject.insert("file_id", jsonObject.value("file_id"));

    if(jsonObject.contains("file_unique_id"))
        _jsonObject.insert("file_unique_id", jsonObject.value("file_unique_id"));

    if(jsonObject.contains("duration"))
        _jsonObject.insert("duration", jsonObject.value("duration"));

    if(jsonObject.contains("performer"))
        _jsonObject.insert("performer", jsonObject.value("performer"));

    if(jsonObject.contains("title"))
        _jsonObject.insert("title", jsonObject.value("title"));

    if(jsonObject.contains("mime_type"))
        _jsonObject.insert("mime_type", jsonObject.value("mime_type"));

    if(jsonObject.contains("file_size"))
        _jsonObject.insert("file_size", jsonObject.value("file_size"));

    if(jsonObject.contains("thumb"))
        _jsonObject.insert("thumb", jsonObject.value("thumb"));
}


/***//*!
    \brief Get **fileId** value
    \return Value of **fileId**
*/
QString Audio::fileId()
{
    return _jsonObject.value("file_id").toString();
}

/*!
    \brief Set new value for **fileId**
    \param QString New value of **fileId**
*/
void Audio::setFileId(QString fileId)
{
    _jsonObject.insert("file_id", fileId);
}


/***//*!
    \brief Get **fileUniqueId** value
    \return Value of **fileUniqueId**
*/
QString Audio::fileUniqueId()
{
    return _jsonObject.value("file_unique_id").toString();
}

/*!
    \brief Set new value for **fileUniqueId**
    \param QString New value of **fileUniqueId**
*/
void Audio::setFileUniqueId(QString fileUniqueId)
{
     _jsonObject.insert("file_unique_id", fileUniqueId);
}


/***//*!
    \brief Get **duration** value
    \return Value of **duration**
*/
qint32 Audio::duration()
{
    return _jsonObject.value("duration").toInt();
}

/*!
    \brief Set new value for **duration**
    \param QString New value of **duration**
*/
void Audio::setDuration(qint32 duration)
{
    _jsonObject.insert("duration", duration);
}


/***//*!
    \brief Get **performer** value
    \return Value of **performer**
*/
QString Audio::performer()
{
    return _jsonObject.value("performer").toString();
}

/*!
    \brief Set new value for **performer**
    \param QString New value of **performer**
*/
void Audio::setPerformer(QString performer)
{
    _jsonObject.insert("performer", performer);
}

/*!
    \brief Check if object has **performer**
    \return `True` if has **performer**, `false` if doesn't
*/
bool Audio::hasPerformer()
{
    return _jsonObject.contains("performer");
}


/***//*!
    \brief Get **title** value
    \return Value of **title**
*/
QString Audio::title()
{
    return _jsonObject.value("title").toString();
}

/*!
    \brief Set new value for **title**
    \param QString New value of **title**
*/
void Audio::setTitle(QString title)
{
    _jsonObject.insert("title", title);
}

/*!
    \brief Check if object has **title**
    \return `True` if has **title**, `false` if doesn't
*/
bool Audio::hasTitle()
{
    return _jsonObject.contains("title");
}


/***//*!
    \brief Get **mimeType** value
    \return Value of **mimeType**
*/
QString Audio::mimeType()
{
    return _jsonObject.value("mime_type").toString();
}

/*!
    \brief Set new value for **mimeType**
    \param QString New value of **mimeType**
*/
void Audio::setMimeType(QString mimeType)
{
    _jsonObject.insert("mime_type", mimeType);
}

/*!
    \brief Check if object has **mimeType**
    \return `True` if has **mimeType**, `false` if doesn't
*/
bool Audio::hasMimeType()
{
    return _jsonObject.contains("mime_type");
}


/***//*!
    \brief Get **fileSize** value
    \return Value of **fileSize**
*/
qint32 Audio::fileSize()
{
    return _jsonObject.value("file_size").toInt();
}

/*!
    \brief Set new value for **fileSize**
    \param qint32 New value of **fileSize**
*/
void Audio::setFileSize(qint32 fileSize)
{
    _jsonObject.insert("file_size", fileSize);
}

/*!
    \brief Check if object has **fileSize**
    \return `True` if has **fileSize**, `false` if doesn't
*/
bool Audio::hasFileSize()
{
    return _jsonObject.contains("file_size");
}


/***//*!
    \brief Get **thumb** value
    \return Value of **thumb** in form of `PhotoSize` object
*/
PhotoSize Audio::thumb()
{
    return PhotoSize(_jsonObject.value("thumb").toObject());
}

/*!
    \brief Set new value for **thumb**
    \param PhotoSize New value of **thumb**
*/
void Audio::setThumb(PhotoSize thumb)
{
    _jsonObject.insert("thumb", thumb.toObject());
}

/*!
    \brief Check if object has **thumb**
    \return `True` if has **thumb**, `false` if doesn't
*/
bool Audio::hasThumb()
{
    return _jsonObject.contains("thumb");
}
