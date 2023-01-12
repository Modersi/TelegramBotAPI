#include "Types/MessageAutoDeleteTimerChanged.h"

Telegram::MessageAutoDeleteTimerChanged::MessageAutoDeleteTimerChanged() :
	message_auto_delete_time()
{}

Telegram::MessageAutoDeleteTimerChanged::MessageAutoDeleteTimerChanged(const qint32& message_auto_delete_time) :
	message_auto_delete_time(message_auto_delete_time)
{}

Telegram::MessageAutoDeleteTimerChanged::MessageAutoDeleteTimerChanged(const QJsonObject& json_object) {
	json_object.contains("message_auto_delete_time") ? message_auto_delete_time = json_object["message_auto_delete_time"].toInt() : message_auto_delete_time = 0;
}

QJsonObject Telegram::MessageAutoDeleteTimerChanged::toObject() const {
	if (isEmpty()) return {};

	return { {"message_auto_delete_time", message_auto_delete_time} };
}

bool Telegram::MessageAutoDeleteTimerChanged::isEmpty() const {
	return message_auto_delete_time == 0;
}
