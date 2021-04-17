#include "Types/ReplyKeyboardRemove.h"

ReplyKeyboardRemove::ReplyKeyboardRemove()
{
    _jsonObject.insert("remove_keyboard", true);
}

ReplyKeyboardRemove::ReplyKeyboardRemove(bool selective)
{
    _jsonObject.insert("remove_keyboard", true);

    if(selective != false)
        _jsonObject.insert("selective", QJsonValue(selective));
}

ReplyKeyboardRemove::ReplyKeyboardRemove(QJsonObject jsonObject)
{
    if(jsonObject.contains("remove_keyboard"))
        _jsonObject.insert("remove_keyboard", jsonObject.value("remove_keyboard"));

    if(jsonObject.contains("selective"))
        _jsonObject.insert("selective", jsonObject.value("selective"));
}

bool ReplyKeyboardRemove::isSelective()
{
    return _jsonObject.value("selective").toBool();
}

void ReplyKeyboardRemove::setSelective(bool selective)
{
    _jsonObject.insert("selective", selective);
}

bool ReplyKeyboardRemove::hasSelective()
{
    return _jsonObject.contains("selective");
}
