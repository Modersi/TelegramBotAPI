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

Telegram::ChatMemberAdministrator::ChatMemberAdministrator(const QJsonObject& jsonObject)
{
	jsonObject.contains("user")					  ? user = User(jsonObject["user"].toObject())								: user = User();
	jsonObject.contains("can_be_edited")		  ? can_be_edited = jsonObject["can_be_edited"].toBool()					: can_be_edited = false;
	jsonObject.contains("is_anonymous")			  ? is_anonymous = jsonObject["is_anonymous"].toBool()						: is_anonymous = false;
	jsonObject.contains("can_manage_chat")		  ? can_manage_chat = jsonObject["can_manage_chat"].toBool()				: can_manage_chat = false;
	jsonObject.contains("can_delete_messages")	  ? can_delete_messages = jsonObject["can_delete_messages"].toBool()		: can_delete_messages = false;
	jsonObject.contains("can_manage_voice_chats") ? can_manage_voice_chats = jsonObject["can_manage_voice_chats"].toBool()	: can_manage_voice_chats = false;
	jsonObject.contains("can_restrict_members")   ? can_restrict_members = jsonObject["can_restrict_members"].toBool()		: can_restrict_members = false;
	jsonObject.contains("can_promote_members")	  ? can_promote_members = jsonObject["can_promote_members"].toBool()		: can_promote_members = false;
	jsonObject.contains("can_change_info")		  ? can_change_info = jsonObject["can_change_info"].toBool()				: can_change_info = false;
	jsonObject.contains("can_invite_users")		  ? can_invite_users = jsonObject["can_invite_users"].toBool()				: can_invite_users = false;
	jsonObject.contains("can_post_messages")	  ? can_post_messages = jsonObject["can_post_messages"].toBool()			: can_post_messages = std::nullopt;
	jsonObject.contains("can_edit_messages")	  ? can_edit_messages = jsonObject["can_edit_messages"].toBool()			: can_edit_messages = std::nullopt;
	jsonObject.contains("can_pin_messages")		  ? can_pin_messages = jsonObject["can_pin_messages"].toBool()				: can_pin_messages = std::nullopt;
	jsonObject.contains("custom_title")			  ? custom_title = jsonObject["custom_title"].toString()					: custom_title = std::nullopt;
}

QJsonObject Telegram::ChatMemberAdministrator::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	QJsonObject chatMemberAdministratorJsonObject{ {"status", status}, {"user", user.toObject()}, {"can_be_edited", can_be_edited}, {"is_anonymous", is_anonymous}, {"can_manage_chat", can_manage_chat}, {"can_delete_messages", can_delete_messages},
												   {"can_manage_voice_chats", can_manage_voice_chats}, {"can_restrict_members", can_restrict_members}, {"can_promote_members", can_promote_members}, {"can_change_info", can_change_info}, {"can_invite_users", can_invite_users} };

	if (can_post_messages.has_value())			chatMemberAdministratorJsonObject.insert("can_post_messages", *can_post_messages);
	if (can_edit_messages.has_value())			chatMemberAdministratorJsonObject.insert("can_edit_messages", *can_edit_messages);
	if (can_pin_messages.has_value())			chatMemberAdministratorJsonObject.insert("can_pin_messages", *can_pin_messages);
	if (custom_title.has_value())				chatMemberAdministratorJsonObject.insert("custom_title", *custom_title);

	return chatMemberAdministratorJsonObject;
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
