#include "Types/KeyboardButtonPollType.h"

#include "qjsonobject.h"

Telegram::KeyboardButtonPollType::KeyboardButtonPollType(const std::optional<Poll::Type>& type) :
	type(type)
{}

Telegram::KeyboardButtonPollType::KeyboardButtonPollType(const QJsonObject& jsonObject)
{
	if (jsonObject.contains("type"))
	{
		if (jsonObject["type"] == "quiz") type = Poll::Type::QUIZ;
		if (jsonObject["type"] == "regular") type = Poll::Type::REGULAR;
	}
	else type = std::nullopt;
}

QJsonObject Telegram::KeyboardButtonPollType::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	if (type == Poll::Type::QUIZ) return QJsonObject{ {"type", "quiz"} };
	if (type == Poll::Type::REGULAR) return QJsonObject{ {"type", "regular"} };
}

bool Telegram::KeyboardButtonPollType::isEmpty() const
{
	return type == std::nullopt;
}
