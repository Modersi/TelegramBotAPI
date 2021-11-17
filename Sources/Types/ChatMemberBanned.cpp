#include "Types/ChatMemberBanned.h"

Telegram::ChatMemberBanned::ChatMemberBanned() :
	user(),
	until_date()
{}

Telegram::ChatMemberBanned::ChatMemberBanned(const User& user, const qint32& until_date) :
	user(user),
	until_date(until_date)
{}

Telegram::ChatMemberBanned::ChatMemberBanned(const QJsonObject& jsonObject)
{
	jsonObject.contains("user")		  ? user = User(jsonObject["user"].toObject())	  : user = User();
	jsonObject.contains("until_date") ? until_date = jsonObject["until_date"].toInt() : until_date = 0;
}

QJsonObject Telegram::ChatMemberBanned::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	return QJsonObject { {"status", status}, {"user", user.toObject()}, {"until_date", until_date} };
}

bool Telegram::ChatMemberBanned::isEmpty() const
{
	return user.isEmpty() and until_date == 0;
}
