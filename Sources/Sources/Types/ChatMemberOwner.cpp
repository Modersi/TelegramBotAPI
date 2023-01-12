#include "Types/ChatMemberOwner.h"

Telegram::ChatMemberOwner::ChatMemberOwner() :
	user(),
	is_anonymous(),
	custom_title()
{}

Telegram::ChatMemberOwner::ChatMemberOwner(const User& user,
										   const bool& is_anonymous,
										   const std::optional<QString>& custom_title) :
	user(user),
	is_anonymous(is_anonymous),
	custom_title(custom_title)
{}

Telegram::ChatMemberOwner::ChatMemberOwner(const QJsonObject& json_object) {
	json_object.contains("user")		 ? user = User(json_object["user"].toObject())				: user = User();
	json_object.contains("is_anonymous") ? is_anonymous = json_object["is_anonymous"].toBool()		: is_anonymous = false;
	json_object.contains("custom_title") ? custom_title = json_object["custom_title"].toString()	: custom_title = std::nullopt;
}

QJsonObject Telegram::ChatMemberOwner::toObject() const {
	if (isEmpty()) return {};

	QJsonObject chat_member_owner_json_object{ {"status", QString(QMetaEnum::fromType<decltype(status)>().valueToKey(static_cast<int>(status))).toLower()}, {"user", user.toObject()}, {"is_anonymous", is_anonymous} };

	if (custom_title.has_value()) chat_member_owner_json_object.insert("custom_title", *custom_title);

	return chat_member_owner_json_object;
}

bool Telegram::ChatMemberOwner::isEmpty() const {
	return user.isEmpty()
		   and is_anonymous == false
		   and custom_title == std::nullopt;
}

Telegram::ChatMember::Status Telegram::ChatMemberOwner::getStatus() const {
	return status;
}
