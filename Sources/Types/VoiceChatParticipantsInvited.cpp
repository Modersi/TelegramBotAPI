#include "Types/VoiceChatParticipantsInvited.h"
#include "Internal/ConversionFunctions.h"

#include "qjsonobject.h"
#include "qjsonarray.h"

Telegram::VoiceChatParticipantsInvited::VoiceChatParticipantsInvited() :
	users()
{}

Telegram::VoiceChatParticipantsInvited::VoiceChatParticipantsInvited(const QVector<User>& users) :
	users(users)
{}

Telegram::VoiceChatParticipantsInvited::VoiceChatParticipantsInvited(const QJsonObject& jsonObject)
{
	jsonObject.contains("users") ? users = QJsonArrayToQVector<User>(jsonObject["message_id"].toArray()) : users = QVector<User>();
}

QJsonObject Telegram::VoiceChatParticipantsInvited::toObject() const
{
	if(isEmpty())
		return QJsonObject();

	return QJsonObject{ {"users", QVectorToQJsonArray(users)} };
}

bool Telegram::VoiceChatParticipantsInvited::isEmpty() const
{
	return users.isEmpty();
}
