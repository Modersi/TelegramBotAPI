#include "Types/ForceReply.h"

/*!
    \brief A default constructor. Constructs a valid ForceReply object ready to be used
*/
ForceReply::ForceReply()
{
    _jsonObject.insert("force_reply", true);
}

/*!
    \brief Constructor from QJsonObject
    \param QJsonObject QJsonObject which contains fields suitable for the class
*/
ForceReply::ForceReply(QJsonObject jsonObject)
{
    if(jsonObject.contains("remove_keyboard"))
        _jsonObject.insert("remove_keyboard", jsonObject.value("remove_keyboard"));

    if(jsonObject.contains("selective"))
        _jsonObject.insert("selective", jsonObject.value("selective"));
}


/***//*!
    \brief Get **isSelective** value
    \return Value of **isSelective**
*/
bool ForceReply::isSelective()
{
    return _jsonObject.value("selective").toBool();
}

/*!
    \brief Set new value for **isSelective**
    \param bool New value of **isSelective**
*/
void ForceReply::setSelective(bool selective)
{
    _jsonObject.insert("selective", selective);
}

/*!
    \brief Check if object has **isSelective** field
    \return `True` if has **isSelective** field, `false` if doesn't
*/
bool ForceReply::hasSelective()
{
    return _jsonObject.contains("selective");
}
