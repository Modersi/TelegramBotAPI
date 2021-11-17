#include "Types/MessageId.h"

#include "qjsonobject.h"

Telegram::MessageId::MessageId() :
	message_id()
{}

Telegram::MessageId::MessageId(const qint32& message_id) :
	message_id(message_id)
{}

Telegram::MessageId::MessageId(const QJsonObject& jsonObject)
{
	jsonObject.contains("message_id") ? message_id = jsonObject["message_id"].toInt() : message_id = 0;
}

QJsonObject Telegram::MessageId::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	return QJsonObject{ {"message_id", message_id} };
}

bool Telegram::MessageId::isEmpty() const
{
	return message_id == 0;
}
