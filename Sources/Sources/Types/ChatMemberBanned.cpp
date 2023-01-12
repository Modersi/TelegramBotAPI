#include "Types/ChatMemberBanned.h"

Telegram::ChatMemberBanned::ChatMemberBanned() :
	user(),
	until_date()
{}

Telegram::ChatMemberBanned::ChatMemberBanned(const User& user, const qint32& until_date) :
	user(user),
	until_date(until_date)
{}

Telegram::ChatMemberBanned::ChatMemberBanned(const QJsonObject& json_object)
{
	json_object.contains("user")		? user = User(json_object["user"].toObject())		: user = User();
	json_object.contains("until_date")	? until_date = json_object["until_date"].toInt()	: until_date = 0;
}

QJsonObject Telegram::ChatMemberBanned::toObject() const {
	if (isEmpty()) return {};

	return QJsonObject { {"status", QString(QMetaEnum::fromType<decltype(status)>().valueToKey(static_cast<int>(status))).toLower()}, {"user", user.toObject()}, {"until_date", until_date} };
}

bool Telegram::ChatMemberBanned::isEmpty() const {
	return user.isEmpty() and until_date == 0;
}

Telegram::ChatMember::Status Telegram::ChatMemberBanned::getStatus() const {
	return status;
}
