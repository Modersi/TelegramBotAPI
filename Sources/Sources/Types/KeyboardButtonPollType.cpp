#include "Types/KeyboardButtonPollType.h"

Telegram::KeyboardButtonPollType::KeyboardButtonPollType(const std::optional<Poll::Type>& type) :
	type(type)
{}

Telegram::KeyboardButtonPollType::KeyboardButtonPollType(const QJsonObject& json_object) {
	json_object.contains("type") ? type = static_cast<Poll::Type>(QMetaEnum::fromType<Poll::Type>().keyToValue(json_object["type"].toString().toUpper().toUtf8())) : type = std::nullopt;
}

QJsonObject Telegram::KeyboardButtonPollType::toObject() const {
	if (isEmpty()) return {};

	return { {"type", QString(QMetaEnum::fromType<Poll::Type>().valueToKey(static_cast<int>(*type))).toLower()} };
}

bool Telegram::KeyboardButtonPollType::isEmpty() const {
	return type == std::nullopt;
}
