#include "Types/VoiceChatEnded.h"

#include "qjsonobject.h"

Telegram::VoiceChatEnded::VoiceChatEnded() :
	duration()
{}

Telegram::VoiceChatEnded::VoiceChatEnded(const qint32& duration) :
	duration(duration)
{}

Telegram::VoiceChatEnded::VoiceChatEnded(const QJsonObject& jsonObject)
{
	jsonObject.contains("duration") ? duration = jsonObject["duration"].toInt() : duration = 0;
}

QJsonObject Telegram::VoiceChatEnded::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	return QJsonObject{ {"duration", duration} };
}

bool Telegram::VoiceChatEnded::isEmpty() const
{
	return duration == 0;
}
