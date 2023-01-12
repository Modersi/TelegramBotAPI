#include "Types/ChatPermissions.h"

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

Telegram::ChatPermissions::ChatPermissions(const QJsonObject& json_object)
{
	json_object.contains("can_send_messages")			? can_send_messages = json_object["can_send_messages"].toBool()					: can_send_messages = std::nullopt;
	json_object.contains("can_send_media_messages")		? can_send_media_messages = json_object["can_send_media_messages"].toBool()		: can_send_media_messages = std::nullopt;
	json_object.contains("can_send_polls")				? can_send_polls = json_object["can_send_polls"].toBool()						: can_send_polls = std::nullopt;
	json_object.contains("can_send_other_messages")		? can_send_other_messages = json_object["can_send_other_messages"].toBool()		: can_send_other_messages = std::nullopt;
	json_object.contains("can_add_web_page_previews")	? can_add_web_page_previews = json_object["can_add_web_page_previews"].toBool() : can_add_web_page_previews = std::nullopt;
	json_object.contains("can_change_info")				? can_change_info = json_object["can_change_info"].toBool()						: can_change_info = std::nullopt;
	json_object.contains("can_invite_users")			? can_invite_users = json_object["can_invite_users"].toBool()					: can_invite_users = std::nullopt;
	json_object.contains("can_pin_messages")			? can_pin_messages = json_object["can_pin_messages"].toBool()					: can_pin_messages = std::nullopt;
}

QJsonObject Telegram::ChatPermissions::toObject() const {
	if (isEmpty()) return {};

	QJsonObject chat_permissions_json_object;

	if (can_send_messages.has_value())			chat_permissions_json_object.insert("can_send_messages", *can_send_messages);
	if (can_send_media_messages.has_value())	chat_permissions_json_object.insert("can_send_media_messages", *can_send_media_messages);
	if (can_send_polls.has_value())				chat_permissions_json_object.insert("can_send_polls", *can_send_polls);
	if (can_send_other_messages.has_value())	chat_permissions_json_object.insert("can_send_other_messages", *can_send_other_messages);
	if (can_add_web_page_previews.has_value())	chat_permissions_json_object.insert("can_add_web_page_previews", *can_add_web_page_previews);
	if (can_change_info.has_value())			chat_permissions_json_object.insert("can_change_info", *can_change_info);
	if (can_invite_users.has_value())			chat_permissions_json_object.insert("can_invite_users", *can_invite_users);
	if (can_pin_messages.has_value())			chat_permissions_json_object.insert("can_pin_messages", *can_pin_messages);

	return chat_permissions_json_object;
}

bool Telegram::ChatPermissions::isEmpty() const {
	return can_send_messages == std::nullopt
		   and can_send_media_messages == std::nullopt
		   and can_send_polls == std::nullopt
		   and can_send_other_messages == std::nullopt
		   and can_add_web_page_previews == std::nullopt
		   and can_change_info == std::nullopt
		   and can_invite_users == std::nullopt
		   and can_pin_messages == std::nullopt;
}
