#include "Types/MessageId.h"

#include "qjsonobject.h"

Telegram::MessageId::MessageId() :
	message_id()
{}

Telegram::MessageId::MessageId(const qint32& message_id) :
	message_id(message_id)
{}

Telegram::MessageId::MessageId(const QJsonObject& json_object) {
	json_object.contains("message_id") ? message_id = json_object["message_id"].toInt() : message_id = 0;
}

QJsonObject Telegram::MessageId::toObject() const {
	if (isEmpty()) return {};

	return { {"message_id", message_id} };
}

bool Telegram::MessageId::isEmpty() const {
	return message_id == 0;
}
