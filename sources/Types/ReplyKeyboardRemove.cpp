#include "Types/ReplyKeyboardRemove.h"

#include "qjsonobject.h"

Telegram::ReplyKeyboardRemove::ReplyKeyboardRemove(const std::optional<bool>& selective) :
	selective(selective)
{}

Telegram::ReplyKeyboardRemove::ReplyKeyboardRemove(const QJsonObject& jsonObject)
{
	jsonObject.contains("selective") ? selective = jsonObject["selective"].toBool() : selective = std::nullopt;
}

QJsonObject Telegram::ReplyKeyboardRemove::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	return QJsonObject{ {"remove_keyboard", remove_keyboard}, {"selective",* selective} };
}

bool Telegram::ReplyKeyboardRemove::isEmpty() const
{
	return selective == std::nullopt;
}
