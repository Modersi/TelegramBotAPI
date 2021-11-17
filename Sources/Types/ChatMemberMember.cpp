#include "Types/ChatMemberMember.h"

Telegram::ChatMemberMember::ChatMemberMember() :
	user()
{}

Telegram::ChatMemberMember::ChatMemberMember(const User& user) :
	user(user)
{}

Telegram::ChatMemberMember::ChatMemberMember(const QJsonObject& jsonObject)
{
	jsonObject.contains("user") ? user = User(jsonObject["user"].toObject()) : user = User();
}

QJsonObject Telegram::ChatMemberMember::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	return QJsonObject{ {"status", status}, {"user", user.toObject()} };
}

bool Telegram::ChatMemberMember::isEmpty() const
{
	return user.isEmpty();
}
