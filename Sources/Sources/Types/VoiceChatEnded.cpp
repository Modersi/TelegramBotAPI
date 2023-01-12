#include "Types/VoiceChatEnded.h"

Telegram::VoiceChatEnded::VoiceChatEnded() :
	duration()
{}

Telegram::VoiceChatEnded::VoiceChatEnded(const qint32& duration) :
	duration(duration)
{}

Telegram::VoiceChatEnded::VoiceChatEnded(const QJsonObject& json_object) {
	json_object.contains("duration") ? duration = json_object["duration"].toInt() : duration = 0;
}

QJsonObject Telegram::VoiceChatEnded::toObject() const {
	if (isEmpty()) return {};

	return { {"duration", duration} };
}

bool Telegram::VoiceChatEnded::isEmpty() const {
	return duration == 0;
}
