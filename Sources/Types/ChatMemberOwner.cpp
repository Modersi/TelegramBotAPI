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

Telegram::ChatMemberOwner::ChatMemberOwner(const QJsonObject& jsonObject)
{
	jsonObject.contains("user")			? user = User(jsonObject["user"].toObject())			: user = User();
	jsonObject.contains("is_anonymous") ? is_anonymous = jsonObject["is_anonymous"].toBool()	: is_anonymous = false;
	jsonObject.contains("custom_title") ? custom_title = jsonObject["custom_title"].toString()	: custom_title = std::nullopt;
}

QJsonObject Telegram::ChatMemberOwner::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	QJsonObject chatMemberOwnerJsonObject{ {"status", status}, {"user", user.toObject()}, {"is_anonymous", is_anonymous} };

	if (custom_title.has_value()) chatMemberOwnerJsonObject.insert("custom_title", *custom_title);

	return chatMemberOwnerJsonObject;
}

bool Telegram::ChatMemberOwner::isEmpty() const
{
	return user.isEmpty()
		   and is_anonymous == false
		   and custom_title == std::nullopt;
}
