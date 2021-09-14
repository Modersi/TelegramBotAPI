#include "Types/MessageAutoDeleteTimerChanged.h"

#include "qjsonobject.h"

Telegram::MessageAutoDeleteTimerChanged::MessageAutoDeleteTimerChanged() :
	message_auto_delete_time(0)
{}

Telegram::MessageAutoDeleteTimerChanged::MessageAutoDeleteTimerChanged(const qint32& message_auto_delete_time) :
	message_auto_delete_time(message_auto_delete_time)
{}

Telegram::MessageAutoDeleteTimerChanged::MessageAutoDeleteTimerChanged(const QJsonObject& jsonObject)
{
	jsonObject.contains("message_auto_delete_time") ? message_auto_delete_time = jsonObject["message_auto_delete_time"].toInt() : message_auto_delete_time = 0;
}

QJsonObject Telegram::MessageAutoDeleteTimerChanged::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	return QJsonObject{ {"message_auto_delete_time", message_auto_delete_time} };
}

bool Telegram::MessageAutoDeleteTimerChanged::isEmpty() const
{
	return message_auto_delete_time == 0;
}
