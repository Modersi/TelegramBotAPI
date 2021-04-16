#include "Types/ReplyKeyboardMarkup.h"

ReplyKeyboardMarkup::ReplyKeyboardMarkup() {}

ReplyKeyboardMarkup::ReplyKeyboardMarkup(QVector<QVector<KeyboardButton>> keyboard)
{
    QJsonArray tempJsonArray;
    for(int i = 0; i < keyboard.size(); i++)
        tempJsonArray.insert(tempJsonArray.end(), Type::QVectorToQJsonArray(keyboard[i]));

    _jsonObject.insert("keyboard", QJsonValue(tempJsonArray));
}

ReplyKeyboardMarkup::ReplyKeyboardMarkup(QJsonObject jsonObject)
{
    if(jsonObject.contains("keyboard"))
        _jsonObject.insert("keyboard", jsonObject.value("keyboard"));

    if(jsonObject.contains("resize_keyboard"))
        _jsonObject.insert("resize_keyboard", jsonObject.value("resize_keyboard"));

    if(jsonObject.contains("one_time_keyboard"))
        _jsonObject.insert("one_time_keyboard", jsonObject.value("one_time_keyboard"));

    if(jsonObject.contains("selective"))
        _jsonObject.insert("selective", jsonObject.value("selective"));
}

QVector<QVector<KeyboardButton>> ReplyKeyboardMarkup::keyboard()
{
    QJsonArray keyboardArray = _jsonObject.value("keyboard").toArray();
    QVector<QVector<KeyboardButton>> tempQVector;

    for(QJsonArray::const_iterator i = keyboardArray.begin(); i < keyboardArray.end(); i++)
        tempQVector.insert(tempQVector.end(), Type::QJsonArrayToQVector(i->toArray(), KeyboardButton()));

    return tempQVector;
}

void ReplyKeyboardMarkup::setKeyboard(QVector<QVector<KeyboardButton>> keyboard)
{
    QJsonArray tempJsonArray;

    for(int i = 0; i < keyboard.size(); i++)
        tempJsonArray.insert(tempJsonArray.end(), Type::QVectorToQJsonArray(keyboard[i]));

    _jsonObject.insert("keyboard", tempJsonArray);
}

// "get", "set", "has" methods for "resize_keyboard" field //

bool ReplyKeyboardMarkup::resizeKeyboard()
{
    return _jsonObject.value("resize_keyboard").toBool();
}

void ReplyKeyboardMarkup::setResizeKeyboard(bool resizeKeyboard)
{
    _jsonObject.insert("resize_keyboard", resizeKeyboard);
}

bool ReplyKeyboardMarkup::hasResizeKeyboard()
{
    return _jsonObject.contains("resize_keyboard");
}

// "get", "set", "has" methods for "one_time_keyboard" field //

bool ReplyKeyboardMarkup::oneTimeKeyboard()
{
    return _jsonObject.value("one_time_keyboard").toBool();
}

void ReplyKeyboardMarkup::setOneTimeKeyboard(bool oneTimeKeyboard)
{
    _jsonObject.insert("one_time_keyboard", oneTimeKeyboard);
}

bool ReplyKeyboardMarkup::hasOneTimeKeyboard()
{
    return _jsonObject.contains("one_time_keyboard");
}

// "get", "set", "has" methods for "selective" field //

bool ReplyKeyboardMarkup::selective()
{
    return _jsonObject.value("selective").toBool();
}

void ReplyKeyboardMarkup::setSelective(bool selective)
{
    _jsonObject.insert("selective", selective);
}

bool ReplyKeyboardMarkup::hasSelective()
{
    return _jsonObject.contains("selective");
}
