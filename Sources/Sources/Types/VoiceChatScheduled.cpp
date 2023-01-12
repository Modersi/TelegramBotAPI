#include "Types/VoiceChatScheduled.h"

Telegram::VoiceChatScheduled::VoiceChatScheduled() :
	start_date()
{}

Telegram::VoiceChatScheduled::VoiceChatScheduled(const qint32& start_date) :
	start_date(start_date)
{}

Telegram::VoiceChatScheduled::VoiceChatScheduled(const QJsonObject& json_object) {
	json_object.contains("start_date") ? start_date = json_object["start_date"].toInt() : start_date = 0;
}

QJsonObject Telegram::VoiceChatScheduled::toObject() const {
	if (isEmpty()) return {};

	return { {"start_date", start_date} };
}

bool Telegram::VoiceChatScheduled::isEmpty() const {
	return start_date == 0;
}
