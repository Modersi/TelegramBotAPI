#include "Types/ChatPermissions.h"

#include "qjsonobject.h"

Telegram::ChatPermissions::ChatPermissions(const std::optional<bool>& can_send_messages,
										   const std::optional<bool>& can_send_media_messages,
										   const std::optional<bool>& can_send_polls,
										   const std::optional<bool>& can_send_other_messages,
										   const std::optional<bool>& can_add_web_page_previews,
										   const std::optional<bool>& can_change_info,
										   const std::optional<bool>& can_invite_users,
										   const std::optional<bool>& can_pin_messages) :
	can_send_messages(can_send_messages),
	can_send_media_messages(can_send_media_messages),
	can_send_polls(can_send_polls),
	can_send_other_messages(can_send_other_messages),
	can_add_web_page_previews(can_add_web_page_previews),
	can_change_info(can_change_info),
	can_invite_users(can_invite_users),
	can_pin_messages(can_pin_messages)
{}

Telegram::ChatPermissions::ChatPermissions(const QJsonObject& jsonObject)
{
	jsonObject.contains("can_send_messages")         ? can_send_messages = jsonObject["can_send_messages"].toBool()					: can_send_messages = std::nullopt;
	jsonObject.contains("can_send_media_messages")   ? can_send_media_messages = jsonObject["can_send_media_messages"].toBool()		: can_send_media_messages = std::nullopt;
	jsonObject.contains("can_send_polls")			 ? can_send_polls = jsonObject["can_send_polls"].toBool()						: can_send_polls = std::nullopt;
	jsonObject.contains("can_send_other_messages")	 ? can_send_other_messages = jsonObject["can_send_other_messages"].toBool()		: can_send_other_messages = std::nullopt;
	jsonObject.contains("can_add_web_page_previews") ? can_add_web_page_previews = jsonObject["can_add_web_page_previews"].toBool() : can_add_web_page_previews = std::nullopt;
	jsonObject.contains("can_change_info")			 ? can_change_info = jsonObject["can_change_info"].toBool()						: can_change_info = std::nullopt;
	jsonObject.contains("can_invite_users")			 ? can_invite_users = jsonObject["can_invite_users"].toBool()					: can_invite_users = std::nullopt;
	jsonObject.contains("can_pin_messages")			 ? can_pin_messages = jsonObject["can_pin_messages"].toBool()					: can_pin_messages = std::nullopt;
}

QJsonObject Telegram::ChatPermissions::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	QJsonObject chatPermissionsJsonObject;

	if (can_send_messages.has_value())			chatPermissionsJsonObject.insert("can_send_messages", *can_send_messages);
	if (can_send_media_messages.has_value())	chatPermissionsJsonObject.insert("can_send_media_messages", *can_send_media_messages);
	if (can_send_polls.has_value())				chatPermissionsJsonObject.insert("can_send_polls", *can_send_polls);
	if (can_send_other_messages.has_value())	chatPermissionsJsonObject.insert("can_send_other_messages", *can_send_other_messages);
	if (can_add_web_page_previews.has_value())	chatPermissionsJsonObject.insert("can_add_web_page_previews", *can_add_web_page_previews);
	if (can_change_info.has_value())			chatPermissionsJsonObject.insert("can_change_info", *can_change_info);
	if (can_invite_users.has_value())			chatPermissionsJsonObject.insert("can_invite_users", *can_invite_users);
	if (can_pin_messages.has_value())			chatPermissionsJsonObject.insert("can_pin_messages", *can_pin_messages);

	return chatPermissionsJsonObject;
}

bool Telegram::ChatPermissions::isEmpty() const
{
	return can_send_messages == std::nullopt
		   and can_send_media_messages == std::nullopt
		   and can_send_polls == std::nullopt
		   and can_send_other_messages == std::nullopt
		   and can_add_web_page_previews == std::nullopt
		   and can_change_info == std::nullopt
		   and can_invite_users == std::nullopt
		   and can_pin_messages == std::nullopt;
}
