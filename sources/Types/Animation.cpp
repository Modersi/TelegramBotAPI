#include "Types/Animation.h"
/*!
    \brief A default constructor. Constructs an empty object
*/
Animation::Animation() {}

/*!
    \brief Class contructor
    \param fileId       Identifier for this file
    \param fileUniqueId Unique identifier for this file, which is supposed to be the same over time and for different bots
    \param width        Animation width as defined by sender
    \param height       Animation height as defined by sender
    \param duration     Duration of the animation in seconds as defined by sender
*/
Animation::Animation(QString    fileId,
                     QString    fileUniqueId,
                     qint32     width,
                     qint32     height,
                     qint32     duration)
{
    _jsonObject.insert("file_id", fileId);
    _jsonObject.insert("file_unique_id", fileUniqueId);
    _jsonObject.insert("width", width);
    _jsonObject.insert("height", height);
    _jsonObject.insert("duration", duration);
}

/*!
    \brief Constructor from QJsonObject
    \param QJsonObject QJsonObject which contains fields suitable for the class
*/
Animation::Animation(QJsonObject jsonObject)
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
QString Animation::fileId()
{
    return _jsonObject.value("file_id").toString();
}

/*!
    \brief Set new value for **fileId**
    \param QString New value of **fileId**
*/
void Animation::setFileId(QString fileId)
{
    _jsonObject.insert("file_id", fileId);
}


/***//*!
    \brief Get **fileUniqueId** value
    \return Value of **fileUniqueId**
*/
QString Animation::fileUniqueId()
{
    return _jsonObject.value("file_unique_id").toString();
}

/*!
    \brief Set new value for **fileUniqueId**
    \param QString New value of **fileUniqueId**
*/
void Animation::setFileUniqueId(QString fileUniqueId)
{
    _jsonObject.insert("file_unique_id", fileUniqueId);
}


/***//*!
    \brief Get **width** value
    \return Value of **width**
*/
qint32 Animation::width()
{
    return _jsonObject.value("width").toInt();
}

/*!
    \brief Set new value for **width**
    \param qint32 New value of **width**
*/
void Animation::setWidth(qint32 width)
{
    _jsonObject.insert("width", width);
}


/***//*!
    \brief Get **height** value
    \return Value of **height**
*/
qint32 Animation::height()
{
    return _jsonObject.value("height").toInt();
}

/*!
    \brief Set new value for **height**
    \param qint32 New value of **height**
*/
void Animation::setHeight(qint32 height)
{
    _jsonObject.insert("height", height);
}


/***//*!
    \brief Get **duration** value
    \return Value of **duration**
*/
qint32 Animation::duration()
{
    return _jsonObject.value("duration").toInt();
}

/*!
    \brief Set new value for **duration**
    \param qint32 New value of **duration**
*/
void Animation::setDuration(qint32 duration)
{
    _jsonObject.insert("duration", duration);
}


/***//*!
    \brief Get **thumb** value
    \return Value of **thumb** in form of `PhotoSize` object
*/
PhotoSize Animation::thumb()
{
    return PhotoSize(_jsonObject.value("thumb").toObject());
}

/*!
    \brief Set new value for **thumb**
    \param PhotoSize New value of **thumb**
*/
void Animation::setThumb(PhotoSize thumb)
{
    _jsonObject.insert("thumb", thumb.toObject());
}

/*!
    \brief Check if object has **thumb**
    \return `True` if has **thumb**, `false` if doesn't
*/
bool Animation::hasThumb()
{
    return _jsonObject.contains("thumb");
}


/***//*!
    \brief Get **fileName** value
    \return Value of **fileName**
*/
QString Animation::fileName()
{
    return _jsonObject.value("file_name").toString();
}

/*!
    \brief Set new value for **fileName**
    \param QString New value of **fileName**
*/
void Animation::setFileName(QString fileName)
{
    _jsonObject.insert("file_name", fileName);
}

/*!
    \brief Check if object has **fileName**
    \return `True` if has **fileName**, `false` if doesn't
*/
bool Animation::hasFileName()
{
    return _jsonObject.contains("file_name");
}


/***//*!
    \brief Get **mimeType** value
    \return Value of **mimeType**
*/
QString Animation::mimeType()
{
    return _jsonObject.value("mime_type").toString();
}

/*!
    \brief Set new value for **mimeType**
    \param QString New value of **mimeType**
*/
void Animation::setMimeType(QString mimeType)
{
    _jsonObject.insert("mime_type", mimeType);
}

/*!
    \brief Check if object has **mimeType**
    \return `True` if has **mimeType**, `false` if doesn't
*/
bool Animation::hasMimeType()
{
    return _jsonObject.contains("mime_type");
}


/***//*!
    \brief Get **fileSize** value
    \return Value of **fileSize**
*/
qint32 Animation::fileSize()
{
    return _jsonObject.value("file_size").toInt();
}

/*!
    \brief Set new value for **fileSize**
    \param qint32 New value of **fileSize**
*/
void Animation::setFileSize(qint32 fileSize)
{
    _jsonObject.insert("file_size", fileSize);
}

/*!
    \brief Check if object has **fileSize**
    \return `True` if has **thumb** fileSize, `false` if doesn't
*/
bool Animation::hasFileSize()
{
    return _jsonObject.contains("file_size");
}
