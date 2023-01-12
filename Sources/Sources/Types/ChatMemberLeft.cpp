#include "Types/ChatMemberLeft.h"

Telegram::ChatMemberLeft::ChatMemberLeft() :
	user()
{}

Telegram::ChatMemberLeft::ChatMemberLeft(const User& user) :
	user(user)
{}

Telegram::ChatMemberLeft::ChatMemberLeft(const QJsonObject& json_object) {
	json_object.contains("user") ? user = User(json_object["user"].toObject()) : user = User();
}

QJsonObject Telegram::ChatMemberLeft::toObject() const {
	if (isEmpty()) return {};

	return QJsonObject{ {"status", QString(QMetaEnum::fromType<decltype(status)>().valueToKey(static_cast<int>(status))).toLower()}, {"user", user.toObject()} };
}

bool Telegram::ChatMemberLeft::isEmpty() const {
	return user.isEmpty();
}

Telegram::ChatMember::Status Telegram::ChatMemberLeft::getStatus() const {
	return status;
}
