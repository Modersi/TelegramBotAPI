#include "Types/ChatMemberLeft.h"

Telegram::ChatMemberLeft::ChatMemberLeft() :
	user()
{}

Telegram::ChatMemberLeft::ChatMemberLeft(const User& user) :
	user(user)
{}

Telegram::ChatMemberLeft::ChatMemberLeft(const QJsonObject& jsonObject)
{
	jsonObject.contains("user") ? user = User(jsonObject["user"].toObject()) : user = User();
}

QJsonObject Telegram::ChatMemberLeft::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	return QJsonObject{ {"status", status}, {"user", user.toObject()} };
}

bool Telegram::ChatMemberLeft::isEmpty() const
{
	return user.isEmpty();
}
