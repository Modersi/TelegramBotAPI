#include "Types/ChatMemberAdministrator.h"

Telegram::ChatMemberAdministrator::ChatMemberAdministrator() :
	user(),
	can_be_edited(),
	is_anonymous(),
	can_manage_chat(),
	can_delete_messages(),
	can_manage_voice_chats(),
	can_restrict_members(),
	can_promote_members(),
	can_change_info(),
	can_invite_users(),
	can_post_messages(),
	can_edit_messages(),
	can_pin_messages(),
	custom_title()
{}

Telegram::ChatMemberAdministrator::ChatMemberAdministrator(const User& user,
														   const bool& can_be_edited,
														   const bool& is_anonymous,
														   const bool& can_manage_chat,
														   const bool& can_delete_messages,
														   const bool& can_manage_voice_chats,
														   const bool& can_restrict_members,
														   const bool& can_promote_members,
														   const bool& can_change_info,
														   const bool& can_invite_users,
														   const std::optional<bool>& can_post_messages,
														   const std::optional<bool>& can_edit_messages,
														   const std::optional<bool>& can_pin_messages,
														   const std::optional<QString>& custom_title) :
	user(user),
	can_be_edited(can_be_edited),
	is_anonymous(is_anonymous),
	can_manage_chat(can_manage_chat),
	can_delete_messages(can_delete_messages),
	can_manage_voice_chats(can_manage_voice_chats),
	can_restrict_members(can_restrict_members),
	can_promote_members(can_promote_members),
	can_change_info(can_change_info),
	can_invite_users(can_invite_users),
	can_post_messages(can_post_messages),
	can_edit_messages(can_edit_messages),
	can_pin_messages(can_pin_messages),
	custom_title(custom_title)
{}

Telegram::ChatMemberAdministrator::ChatMemberAdministrator(const QJsonObject& json_object) {
	json_object.contains("user")					? user = User(json_object["user"].toObject())								: user = User();
	json_object.contains("can_be_edited")			? can_be_edited = json_object["can_be_edited"].toBool()						: can_be_edited = false;
	json_object.contains("is_anonymous")			? is_anonymous = json_object["is_anonymous"].toBool()						: is_anonymous = false;
	json_object.contains("can_manage_chat")			? can_manage_chat = json_object["can_manage_chat"].toBool()					: can_manage_chat = false;
	json_object.contains("can_delete_messages")		? can_delete_messages = json_object["can_delete_messages"].toBool()			: can_delete_messages = false;
	json_object.contains("can_manage_voice_chats")	? can_manage_voice_chats = json_object["can_manage_voice_chats"].toBool()	: can_manage_voice_chats = false;
	json_object.contains("can_restrict_members")	? can_restrict_members = json_object["can_restrict_members"].toBool()		: can_restrict_members = false;
	json_object.contains("can_promote_members")		? can_promote_members = json_object["can_promote_members"].toBool()			: can_promote_members = false;
	json_object.contains("can_change_info")			? can_change_info = json_object["can_change_info"].toBool()					: can_change_info = false;
	json_object.contains("can_invite_users")		? can_invite_users = json_object["can_invite_users"].toBool()				: can_invite_users = false;
	json_object.contains("can_post_messages")		? can_post_messages = json_object["can_post_messages"].toBool()				: can_post_messages = std::nullopt;
	json_object.contains("can_edit_messages")		? can_edit_messages = json_object["can_edit_messages"].toBool()				: can_edit_messages = std::nullopt;
	json_object.contains("can_pin_messages")		? can_pin_messages = json_object["can_pin_messages"].toBool()				: can_pin_messages = std::nullopt;
	json_object.contains("custom_title")			? custom_title = json_object["custom_title"].toString()						: custom_title = std::nullopt;
}

QJsonObject Telegram::ChatMemberAdministrator::toObject() const {
	if (isEmpty()) return {};

	QJsonObject chat_member_administrator_json_object{ {"status", QString(QMetaEnum::fromType<decltype(status)>().valueToKey(static_cast<int>(status))).toLower()}, {"user", user.toObject()}, {"can_be_edited", can_be_edited}, {"is_anonymous", is_anonymous}, {"can_manage_chat", can_manage_chat}, {"can_delete_messages", can_delete_messages},
												       {"can_manage_voice_chats", can_manage_voice_chats}, {"can_restrict_members", can_restrict_members}, {"can_promote_members", can_promote_members}, {"can_change_info", can_change_info}, {"can_invite_users", can_invite_users} };

	if (can_post_messages.has_value())			chat_member_administrator_json_object.insert("can_post_messages", *can_post_messages);
	if (can_edit_messages.has_value())			chat_member_administrator_json_object.insert("can_edit_messages", *can_edit_messages);
	if (can_pin_messages.has_value())			chat_member_administrator_json_object.insert("can_pin_messages", *can_pin_messages);
	if (custom_title.has_value())				chat_member_administrator_json_object.insert("custom_title", *custom_title);

	return chat_member_administrator_json_object;
}

bool Telegram::ChatMemberAdministrator::isEmpty() const
{
	return user.isEmpty()
		   and can_be_edited == false
		   and is_anonymous == false
		   and can_manage_chat == false
		   and can_delete_messages == false
		   and can_manage_voice_chats == false
		   and can_restrict_members == false
		   and can_promote_members == false
		   and can_change_info == false
		   and can_invite_users == false
		   and can_post_messages == std::nullopt
		   and can_edit_messages == std::nullopt
		   and can_pin_messages == std::nullopt
		   and custom_title == std::nullopt;
}

Telegram::ChatMember::Status Telegram::ChatMemberAdministrator::getStatus() const {
	return status;
}
