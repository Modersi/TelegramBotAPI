#include "Types/Dice.h"

/*!
    \brief A default constructor. Constructs an empty object
*/
Dice::Dice() {}

/*!
    \brief Class contructor
    \param emoji Emoji on which the dice throw animation is based
    \param value Value of the dice, 1-6 for “🎲” (dice) and “🎯”(darts throw) base emoji, 1-5 for “🏀”(ball throw) base emoji
*/
Dice::Dice(QString emoji, qint32 value)
{
    _jsonObject.insert("emoji", QJsonValue(emoji));
    _jsonObject.insert("value", QJsonValue(value));
}

/*!
    \brief Constructor from QJsonObject
    \param QJsonObject QJsonObject which contains fields suitable for the class
*/
Dice::Dice(QJsonObject jsonObject)
{
    if(jsonObject.contains("emoji"))
        _jsonObject.insert("emoji", jsonObject.value("emoji"));

    if(jsonObject.contains("value"))
        _jsonObject.insert("value", jsonObject.value("value"));
}


/***//*!
    \brief Get **emoji** value
    \return Value of **emoji**
*/
QString Dice::emoji()
{
    return _jsonObject.value("emoji").toString();
}

/*!
    \brief Set new value for **emoji**
    \param QString New value of **emoji**
*/
void Dice::setEmoji(QString emoji)
{
    _jsonObject.insert("emoji", emoji);
}


/***//*!
    \brief Get **value** value
    \return Value of **value**
*/
qint32 Dice::value()
{
    return _jsonObject.value("value").toInt();
}

/*!
    \brief Set new value for **value**
    \param qint32 New value of **value**
*/
void Dice::setValue(qint32 value)
{
    _jsonObject.insert("value", value);
}
