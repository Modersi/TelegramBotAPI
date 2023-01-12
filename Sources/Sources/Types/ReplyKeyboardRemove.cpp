#include "Types/ReplyKeyboardRemove.h"

Telegram::ReplyKeyboardRemove::ReplyKeyboardRemove(const std::optional<bool>& selective) :
	selective(selective)
{}

Telegram::ReplyKeyboardRemove::ReplyKeyboardRemove(const QJsonObject& json_object) {
	json_object.contains("selective") ? selective = json_object["selective"].toBool() : selective = std::nullopt;
}

QJsonObject Telegram::ReplyKeyboardRemove::toObject() const
{
	QJsonObject reply_keyboard_remove_json_object{ {"remove_keyboard", remove_keyboard} };

	if (selective.has_value())	reply_keyboard_remove_json_object.insert("selective", *selective);

	return reply_keyboard_remove_json_object;
}

bool Telegram::ReplyKeyboardRemove::isEmpty() const {
	return selective == std::nullopt;
}
