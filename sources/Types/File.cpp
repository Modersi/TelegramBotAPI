#include "Types/File.h"

/*!
    \brief A default constructor. Constructs an empty object
*/
File::File() {}

/*!
    \brief Class contructor
    \param fileId        Identifier for this file
    \param fileUniqueId  Unique identifier for this file
*/
File::File(QString  fileId,
           QString  fileUniqueId)
{
    _jsonObject.insert("file_id", fileId);
    _jsonObject.insert("file_unique_id", fileUniqueId);

}

/*!
    \brief Constructor from QJsonObject
    \param QJsonObject QJsonObject which contains fields suitable for the class
*/
File::File(QJsonObject jsonObject)
{
    if(jsonObject.contains("file_id"))
        _jsonObject.insert("file_id", jsonObject.value("file_id"));

    if(jsonObject.contains("file_unique_id"))
        _jsonObject.insert("file_unique_id", jsonObject.value("file_unique_id"));

    if(jsonObject.contains("file_size"))
        _jsonObject.insert("file_size", jsonObject.value("file_size"));

    if(jsonObject.contains("file_path"))
        _jsonObject.insert("file_path", jsonObject.value("file_path"));
}


/***//*!
    \brief Get **fileId** value
    \return Value of **fileId**
*/
QString File::fileId()
{
    return _jsonObject.value("file_id").toString();
}

/*!
    \brief Set new value for **fileId**
    \param QString New value of **fileId**
*/
void File::setFileId(QString fileId)
{
    _jsonObject.insert("file_id", fileId);
}


/***//*!
    \brief Get **fileUniqueId** value
    \return Value of **fileUniqueId**
*/
QString File::fileUniqueId()
{
    return _jsonObject.value("file_unique_id").toString();
}

/*!
    \brief Set new value for **fileUniqueId**
    \param QString New value of **fileUniqueId**
*/
void File::setFileUniqueId(QString fileUniqueId)
{
    _jsonObject.insert("file_unique_id", fileUniqueId);
}


/***//*!
    \brief Get **fileSize** value
    \return Value of **fileSize**
*/
qint32 File::fileSize()
{
    return _jsonObject.value("file_size").toInt();
}

/*!
    \brief Set new value for **fileSize**
    \param qint32 New value of **fileSize**
*/
void File::setFileSize(qint32 fileSize)
{
    _jsonObject.insert("file_size", fileSize);
}

/*!
    \brief Check if object has **fileSize**
    \return `True` if has **fileSize**, `false` if doesn't
*/
bool File::hasFileSize()
{
    return _jsonObject.contains("file_size");
}


/***//*!
    \brief Get **filePath** value
    \return Value of **filePath**
*/
QString File::filePath()
{
    return _jsonObject.value("file_path").toString();
}

/*!
    \brief Set new value for **filePath**
    \param QString New value of **filePath**
*/
void File::setFilePath(QString filePath)
{
    _jsonObject.insert("file_path", filePath);
}

/*!
    \brief Check if object has **filePath**
    \return `True` if has **filePath**, `false` if doesn't
*/
bool File::hasFilePath()
{
    return _jsonObject.contains("file_path");
}
