#include "Contact.h"

/*!
    \brief A default constructor. Constructs an empty object
*/
Contact::Contact() {}

/*!
    \brief Class contructor
    \param phoneNumber  Contact's phone number
    \param firstName    Contact's first name
*/
Contact::Contact(QString phoneNumber,
                 QString firstName)
{
    _jsonObject.insert("phone_number", phoneNumber);
    _jsonObject.insert("first_name", firstName);
}

/*!
    \brief Constructor from QJsonObject
    \param QJsonObject QJsonObject which contains fields suitable for the class
*/
Contact::Contact(QJsonObject jsonObject)
{
    if(jsonObject.contains("phone_number"))
        _jsonObject.insert("phone_number", jsonObject.value("phone_number"));

    if(jsonObject.contains("first_name"))
        _jsonObject.insert("first_name", jsonObject.value("first_name"));

    if(jsonObject.contains("last_name"))
        _jsonObject.insert("last_name", jsonObject.value("last_name"));

    if(jsonObject.contains("user_id"))
        _jsonObject.insert("user_id", jsonObject.value("user_id"));

    if(jsonObject.contains("vcard"))
        _jsonObject.insert("vcard", jsonObject.value("vcard"));
}


/***//*!
    \brief Get **phoneNumber** value
    \return Value of **phoneNumber**
*/
QString Contact::phoneNumber()
{
    return _jsonObject.value("phone_number").toString();
}

/*!
    \brief Set new value for **phoneNumber**
    \param QString New value of **phoneNumber**
*/
void Contact::setPhoneNumber(QString phoneNumber)
{
    _jsonObject.insert("phone_number", phoneNumber);
}


/***//*!
    \brief Get **firstName** value
    \return Value of **firstName**
*/
QString Contact::firstName()
{
    return _jsonObject.value("first_name").toString();
}

/*!
    \brief Set new value for **firstName**
    \param QString New value of **firstName**
*/
void Contact::setFirstName(QString firstName)
{
    _jsonObject.insert("first_name", firstName);
}


/***//*!
    \brief Get **lastName** value
    \return Value of **lastName**
*/
QString Contact::lastName()
{
    return _jsonObject.value("last_name").toString();
}

/*!
    \brief Set new value for **lastName**
    \param QString New value of **lastName**
*/
void Contact::setLastName(QString lastName)
{
    _jsonObject.insert("last_name", lastName);
}

/*!
    \brief Check if object has **lastName**
    \return `True` if has **lastName**, `false` if doesn't
*/
bool Contact::hasLastName()
{
    return _jsonObject.contains("last_name");
}


/***//*!
    \brief Get **userId** value
    \return Value of **userId**
*/
qint32 Contact::userId()
{
    return _jsonObject.value("user_id").toInt();
}

/*!
    \brief Set new value for **userId**
    \param qint32 New value of **userId**
*/
void Contact::setUserId(qint32 userId)
{
    _jsonObject.insert("user_id", userId);
}

/*!
    \brief Check if object has **userId**
    \return `True` if has **userId**, `false` if doesn't
*/
bool Contact::hasUserId()
{
    return _jsonObject.contains("user_id");
}


/***//*!
    \brief Get **vcard** value
    \return Value of **vcard**
*/
QString Contact::vcard()
{
    return _jsonObject.value("vcard").toString();
}

/*!
    \brief Set new value for **vcard**
    \param QString New value of **vcard**
*/
void Contact::setVcard(QString vcard)
{
    _jsonObject.insert("vcard", vcard);
}

/*!
    \brief Check if object has **vcard**
    \return `True` if has **vcard**, `false` if doesn't
*/
bool Contact::hasVcard()
{
    return _jsonObject.contains("vcard");
}
