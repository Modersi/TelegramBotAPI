#include "Types/ChatMemberMember.h"

Telegram::ChatMemberMember::ChatMemberMember() :
	user()
{}

Telegram::ChatMemberMember::ChatMemberMember(const User& user) :
	user(user)
{}

Telegram::ChatMemberMember::ChatMemberMember(const QJsonObject& json_object) {
	json_object.contains("user") ? user = User(json_object["user"].toObject()) : user = User();
}

QJsonObject Telegram::ChatMemberMember::toObject() const {
	if (isEmpty()) return {};

	return QJsonObject{ {"status", QString(QMetaEnum::fromType<decltype(status)>().valueToKey(static_cast<int>(status))).toLower()}, {"user", user.toObject()} };
}

bool Telegram::ChatMemberMember::isEmpty() const {
	return user.isEmpty();
}

Telegram::ChatMember::Status Telegram::ChatMemberMember::getStatus() const {
	return status;
}
