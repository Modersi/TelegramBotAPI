#include "ChatPhoto.h"

/*!
    \brief A default constructor. Constructs an empty object
*/
ChatPhoto::ChatPhoto() {}

/*!
    \brief Class contructor
    \param smallFileId          File identifier of small chat photo
    \param smallFileUniqueId    Unique file identifier of small chat photo
    \param bigFileId            File identifier of big chat photo
    \param bigFileUniqueId      Unique file identifier of big chat photo
*/
ChatPhoto::ChatPhoto(QString smallFileId,
                     QString smallFileUniqueId,
                     QString bigFileId,
                     QString bigFileUniqueId)
{
    _jsonObject.insert("file_id", smallFileId);
    _jsonObject.insert("file_unique_id", smallFileUniqueId);
    _jsonObject.insert("duration", bigFileId);
    _jsonObject.insert("duration", bigFileUniqueId);
}

/*!
    \brief Constructor from QJsonObject
    \param QJsonObject QJsonObject which contains fields suitable for the class
*/
ChatPhoto::ChatPhoto(QJsonObject jsonObject)
{
    if(jsonObject.contains("small_file_id"))
        _jsonObject.insert("small_file_id", jsonObject.value("small_file_id"));

    if(jsonObject.contains("small_file_unique_id"))
        _jsonObject.insert("small_file_unique_id", jsonObject.value("small_file_unique_id"));

    if(jsonObject.contains("big_file_id"))
        _jsonObject.insert("big_file_id", jsonObject.value("big_file_id"));

    if(jsonObject.contains("big_file_unique_id"))
        _jsonObject.insert("big_file_unique_id", jsonObject.value("big_file_unique_id"));

}


/***//*!
    \brief Get **smallFileId** value
    \return Value of **smallFileId**
*/
QString ChatPhoto::smallFileId()
{
    return _jsonObject.value("small_file_id").toString();
}

/*!
    \brief Set new value for **smallFileId**
    \param QString New value of **smallFileId**
*/
void ChatPhoto::setSmallFileId(QString smallFileId)
{
    _jsonObject.insert("small_file_id", smallFileId);
}


/***//*!
    \brief Get **smallFileUniqueId** value
    \return Value of **smallFileUniqueId**
*/
QString ChatPhoto::smallFileUniqueId()
{
    return _jsonObject.value("small_file_unique_id").toString();
}

/*!
    \brief Set new value for **smallFileUniqueId**
    \param QString New value of **smallFileUniqueId**
*/
void ChatPhoto::setSmallFileUniqueId(QString smallFileUniqueId)
{
    _jsonObject.insert("small_file_unique_id", smallFileUniqueId);
}


/***//*!
    \brief Get **bigFileId** value
    \return Value of **bigFileId**
*/
QString ChatPhoto::bigFileId()
{
    return _jsonObject.value("big_file_id").toString();
}

/*!
    \brief Set new value for **bigFileId**
    \param QString New value of **bigFileId**
*/
void ChatPhoto::setBigFileId(QString bigFileId)
{
    _jsonObject.insert("big_file_id", bigFileId);
}


/***//*!
    \brief Get **bigFileUniqueId** value
    \return Value of **bigFileUniqueId**
*/
QString ChatPhoto::bigFileUniqueId()
{
    return _jsonObject.value("big_file_unique_id").toString();
}

/*!
    \brief Set new value for **bigFileUniqueId**
    \param QString New value of **bigFileUniqueId**
*/
void ChatPhoto::setBigFileUniqueId(QString bigFileUniqueId)
{
    _jsonObject.insert("big_file_unique_id", bigFileUniqueId);
}
