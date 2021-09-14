#include "Types/VoiceChatScheduled.h"

#include "qjsonobject.h"

Telegram::VoiceChatScheduled::VoiceChatScheduled() :
	start_date(0)
{}

Telegram::VoiceChatScheduled::VoiceChatScheduled(const qint32& start_date) :
	start_date(start_date)
{}

Telegram::VoiceChatScheduled::VoiceChatScheduled(const QJsonObject& jsonObject)
{
	jsonObject.contains("start_date") ? start_date = jsonObject["start_date"].toInt() : start_date = 0;
}

QJsonObject Telegram::VoiceChatScheduled::toObject() const
{
	if(isEmpty())
		return QJsonObject();

	return QJsonObject{ {"start_date", start_date} };
}

bool Telegram::VoiceChatScheduled::isEmpty() const
{
	return start_date == 0;
}
