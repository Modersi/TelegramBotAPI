#include "Types/VoiceChatParticipantsInvited.h"

#include "qjsonarray.h"

#include "Internal/ConversionFunctions.h"

Telegram::VoiceChatParticipantsInvited::VoiceChatParticipantsInvited() :
	users()
{}

Telegram::VoiceChatParticipantsInvited::VoiceChatParticipantsInvited(const QVector<User>& users) :
	users(users)
{}

Telegram::VoiceChatParticipantsInvited::VoiceChatParticipantsInvited(const QJsonObject& json_object) {
	json_object.contains("users") ? users = QJsonArrayToQVector<User>(json_object["message_id"].toArray()) : users = QVector<User>();
}

QJsonObject Telegram::VoiceChatParticipantsInvited::toObject() const {
	if (isEmpty()) return {};

	return { {"users", QVectorToQJsonArray(users)} };
}

bool Telegram::VoiceChatParticipantsInvited::isEmpty() const {
	return users.isEmpty();
}
