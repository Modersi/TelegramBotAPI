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
	QJsonObject replyKeyboardRemoveJsonObject{ {"remove_keyboard", remove_keyboard} };

	if (selective.has_value())	replyKeyboardRemoveJsonObject.insert("selective", *selective);

	return replyKeyboardRemoveJsonObject;
}

bool Telegram::ReplyKeyboardRemove::isEmpty() const
{
	return selective == std::nullopt;
}
