#include "Types/InlineKeyboardMarkup.h"

/*!
    \brief A default constructor. Constructs an empty object
*/
InlineKeyboardMarkup::InlineKeyboardMarkup() {}

/*!
    \brief Class contructor
    \param inlineKeyboard QVector of button rows, each represented by an QVector of InlineKeyboardButton objects
*/
InlineKeyboardMarkup::InlineKeyboardMarkup(QVector<QVector<InlineKeyboardButton> > inlineKeyboard)
{
    QJsonArray tempJsonArray;
    
    for(int i = 0; i < inlineKeyboard.size(); i++)
        tempJsonArray.insert(tempJsonArray.end(), Type::QVectorToQJsonArray(inlineKeyboard[i]));
    
    _jsonObject.insert("inline_keyboard", tempJsonArray);
}

/*!
    \brief Constructor from QJsonObject
    \param QJsonObject QJsonObject which contains fields suitable for the class
*/
InlineKeyboardMarkup::InlineKeyboardMarkup(QJsonObject jsonObject)
{
    if(jsonObject.contains("inline_keyboard"))
        _jsonObject.insert("inline_keyboard", jsonObject.value("inline_keyboard"));
}


/***//*!
    \brief Get **inlineKeyboard** value
    \return Value of **inlineKeyboard**
*/
QVector<QVector<InlineKeyboardButton> > InlineKeyboardMarkup::inlineKeyboard()
{
    QJsonArray inlineKeyboardArray = _jsonObject.value("inline_keyboard").toArray();
    QVector<QVector<InlineKeyboardButton>> tempQVector;

    for(QJsonArray::const_iterator i = inlineKeyboardArray.begin(); i < inlineKeyboardArray.end(); i++)
        tempQVector.insert(tempQVector.end(), Type::QJsonArrayToQVector(i->toArray(), InlineKeyboardButton()));

    return tempQVector;
}

/*!
    \brief Set new value for **inlineKeyboard**
    \param QVector<QVector<InlineKeyboardButton> New value of **inlineKeyboard**
*/
void InlineKeyboardMarkup::setInlineKeyboard(QVector<QVector<InlineKeyboardButton> > keyboard)
{
    QJsonArray tempJsonArray;

    for(int i = 0; i < keyboard.size(); i++)
        tempJsonArray.insert(tempJsonArray.end(), Type::QVectorToQJsonArray(keyboard[i]));

    _jsonObject.insert("inline_keyboard", tempJsonArray);
}
