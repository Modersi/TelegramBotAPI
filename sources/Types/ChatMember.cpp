#include "Types/ChatMember.h"

#include "qjsonobject.h"

Telegram::ChatMember::ChatMember() :
	user(User()),
	status(Status::UNINITIALIZED_VALUE),
	custom_title(std::nullopt),
	is_anonymous(std::nullopt),
	can_be_edited(std::nullopt),
	can_manage_chat(std::nullopt),
	can_post_messages(std::nullopt),
	can_edit_messages(std::nullopt),
	can_delete_messages(std::nullopt),
	can_manage_voice_chats(std::nullopt),
	can_restrict_members(std::nullopt),
	can_promote_members(std::nullopt),
	can_change_info(std::nullopt),
	can_invite_users(std::nullopt),
	can_pin_messages(std::nullopt),
	is_member(std::nullopt),
	can_send_messages(std::nullopt),
	can_send_media_messages(std::nullopt),
	can_send_polls(std::nullopt),
	can_send_other_messages(std::nullopt),
	can_add_web_page_previews(std::nullopt),
	until_date(std::nullopt)
{}

Telegram::ChatMember::ChatMember(const User& user,
								 const Status& status,
								 const std::optional<QString>&custom_title,
								 const std::optional<bool>& is_anonymous,
								 const std::optional<bool>& can_be_edited,
								 const std::optional<bool>& can_manage_chat,
								 const std::optional<bool>& can_post_messages,
								 const std::optional<bool>& can_edit_messages,
								 const std::optional<bool>& can_delete_messages,
								 const std::optional<bool>& can_manage_voice_chats,
								 const std::optional<bool>& can_restrict_members,
								 const std::optional<bool>& can_promote_members,
								 const std::optional<bool>& can_change_info,
								 const std::optional<bool>& can_invite_users,
								 const std::optional<bool>& can_pin_messages,
								 const std::optional<bool>& is_member,
								 const std::optional<bool>& can_send_messages,
								 const std::optional<bool>& can_send_media_messages,
								 const std::optional<bool>& can_send_polls,
								 const std::optional<bool>& can_send_other_messages,
								 const std::optional<bool>& can_add_web_page_previews,
								 const std::optional<qint32>& until_date) :
	user(user),
	status(status),
	custom_title(custom_title),
	is_anonymous(is_anonymous),
	can_be_edited(can_be_edited),
	can_manage_chat(can_manage_chat),
	can_post_messages(can_post_messages),
	can_edit_messages(can_edit_messages),
	can_delete_messages(can_delete_messages),
	can_manage_voice_chats(can_manage_voice_chats),
	can_restrict_members(can_restrict_members),
	can_promote_members(can_promote_members),
	can_change_info(can_change_info),
	can_invite_users(can_invite_users),
	can_pin_messages(can_pin_messages),
	is_member(is_member),
	can_send_messages(can_send_messages),
	can_send_media_messages(can_send_media_messages),
	can_send_polls(can_send_polls),
	can_send_other_messages(can_send_other_messages),
	can_add_web_page_previews(can_add_web_page_previews),
	until_date(until_date)
{}

Telegram::ChatMember::ChatMember(const QJsonObject& jsonObject)
{
	auto GetChatMemberStatus = [](const QJsonValue& chatMemberStatus) -> ChatMember::Status
								{
									if (chatMemberStatus == "creator") return Status::CREATOR;
									if (chatMemberStatus == "administrator") return Status::ADMINISTRARTOR;
									if (chatMemberStatus == "member") return Status::MEMBER;
									if (chatMemberStatus == "restricted") return Status::RESTRICTED;
									if (chatMemberStatus == "left") return Status::LEFT;
									if (chatMemberStatus == "kicked") return Status::KICKED;
									else return Status::UNINITIALIZED_VALUE;
								};

	jsonObject.contains("user")						 ? user = User(jsonObject["user"].toObject())									: user = User();
	jsonObject.contains("status")					 ? status = GetChatMemberStatus(jsonObject["status"])							: status = Status::UNINITIALIZED_VALUE;
	jsonObject.contains("custom_title")				 ? custom_title = jsonObject["custom_title"].toString()							: custom_title = std::nullopt;
	jsonObject.contains("is_anonymous")				 ? is_anonymous = jsonObject["is_anonymous"].toBool()							: is_anonymous = std::nullopt;
	jsonObject.contains("can_be_edited")			 ? can_be_edited = jsonObject["can_be_edited"].toBool()							: can_be_edited = std::nullopt;
	jsonObject.contains("can_manage_chat")			 ? can_manage_chat = jsonObject["can_manage_chat"].toBool()						: can_manage_chat = std::nullopt;
	jsonObject.contains("can_post_messages")		 ? can_post_messages = jsonObject["can_post_messages"].toBool()					: can_post_messages = std::nullopt;
	jsonObject.contains("can_edit_messages")		 ? can_edit_messages = jsonObject["can_edit_messages"].toBool()					: can_edit_messages = std::nullopt;
	jsonObject.contains("can_delete_messages")		 ? can_delete_messages = jsonObject["can_delete_messages"].toBool()				: can_delete_messages = std::nullopt;
	jsonObject.contains("can_manage_voice_chats")	 ? can_manage_voice_chats = jsonObject["can_manage_voice_chats"].toBool()		: can_manage_voice_chats = std::nullopt;
	jsonObject.contains("can_restrict_members")		 ? can_restrict_members = jsonObject["can_restrict_members"].toBool()			: can_restrict_members = std::nullopt;
	jsonObject.contains("can_promote_members")		 ? can_promote_members = jsonObject["can_promote_members"].toBool()				: can_promote_members = std::nullopt;
	jsonObject.contains("can_change_info")			 ? can_change_info = jsonObject["can_change_info"].toBool()						: can_change_info = std::nullopt;
	jsonObject.contains("can_invite_users")			 ? can_invite_users = jsonObject["can_invite_users"].toBool()					: can_invite_users = std::nullopt;
	jsonObject.contains("can_pin_messages")			 ? can_pin_messages = jsonObject["can_pin_messages"].toBool()					: can_pin_messages = std::nullopt;
	jsonObject.contains("is_member")				 ? is_member = jsonObject["is_member"].toBool()									: is_member = std::nullopt;
	jsonObject.contains("can_send_messages")		 ? can_send_messages = jsonObject["can_send_messages"].toBool()					: can_send_messages = std::nullopt;
	jsonObject.contains("can_send_media_messages")   ? can_send_media_messages = jsonObject["can_send_media_messages"].toBool()		: can_send_media_messages = std::nullopt;
	jsonObject.contains("can_send_polls")			 ? can_send_polls = jsonObject["can_send_polls"].toBool()						: can_send_polls = std::nullopt;
	jsonObject.contains("can_send_other_messages")	 ? can_send_other_messages = jsonObject["can_send_other_messages"].toBool()		: can_send_other_messages = std::nullopt;
	jsonObject.contains("can_add_web_page_previews") ? can_add_web_page_previews = jsonObject["can_add_web_page_previews"].toBool() : can_add_web_page_previews = std::nullopt;
	jsonObject.contains("until_date")				 ? until_date = jsonObject["until_date"].toInt()								: until_date = std::nullopt;

}

QJsonObject Telegram::ChatMember::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	auto GetChatMemberStatus = [](const ChatMember::Status& chatMemberStatus) -> QString
								{
									if (chatMemberStatus == Status::CREATOR) return "creator";
									if (chatMemberStatus == Status::ADMINISTRARTOR) return "administrator";
									if (chatMemberStatus == Status::MEMBER) return "member";
									if (chatMemberStatus == Status::RESTRICTED) return "restricted";
									if (chatMemberStatus == Status::LEFT) return "left";
									if (chatMemberStatus == Status::KICKED) return "kicked";
									else return "";
								};

	QJsonObject chatMemberJsonObject{ {"user", user.toObject()}, {"status", GetChatMemberStatus(status)} };

	if (custom_title.has_value())				chatMemberJsonObject.insert("custom_title", *custom_title);
	if (is_anonymous.has_value())				chatMemberJsonObject.insert("is_anonymous", *is_anonymous);
	if (can_be_edited.has_value())				chatMemberJsonObject.insert("can_be_edited", *can_be_edited);
	if (can_manage_chat.has_value())			chatMemberJsonObject.insert("can_manage_chat", *can_manage_chat);
	if (can_post_messages.has_value())			chatMemberJsonObject.insert("can_post_messages", *can_post_messages);
	if (can_edit_messages.has_value())			chatMemberJsonObject.insert("can_edit_messages", *can_edit_messages);
	if (can_delete_messages.has_value())		chatMemberJsonObject.insert("can_delete_messages", *can_delete_messages);
	if (can_manage_voice_chats.has_value())		chatMemberJsonObject.insert("can_manage_voice_chats", *can_manage_voice_chats);
	if (can_restrict_members.has_value())		chatMemberJsonObject.insert("can_restrict_members", *can_restrict_members);
	if (can_promote_members.has_value())		chatMemberJsonObject.insert("can_promote_members", *can_promote_members);
	if (can_change_info.has_value())			chatMemberJsonObject.insert("can_change_info", *can_change_info);
	if (can_invite_users.has_value())			chatMemberJsonObject.insert("can_invite_users", *can_invite_users);
	if (can_pin_messages.has_value())			chatMemberJsonObject.insert("can_pin_messages", *can_pin_messages);
	if (is_member.has_value())					chatMemberJsonObject.insert("is_member", *is_member);
	if (can_send_messages.has_value())			chatMemberJsonObject.insert("can_send_messages", *can_send_messages);
	if (can_send_media_messages.has_value())	chatMemberJsonObject.insert("can_send_media_messages", *can_send_media_messages);
	if (can_send_polls.has_value())				chatMemberJsonObject.insert("can_send_polls", *can_send_polls);
	if (can_send_other_messages.has_value())	chatMemberJsonObject.insert("can_send_other_messages", *can_send_other_messages);
	if (can_add_web_page_previews.has_value())	chatMemberJsonObject.insert("can_add_web_page_previews", *can_add_web_page_previews);
	if (until_date.has_value())					chatMemberJsonObject.insert("until_date", *until_date);

	return chatMemberJsonObject;
}

bool Telegram::ChatMember::isEmpty() const
{
	return user.isEmpty()
		   and status == Status::UNINITIALIZED_VALUE
		   and custom_title == std::nullopt
		   and is_anonymous == std::nullopt
		   and can_be_edited == std::nullopt
		   and can_manage_chat == std::nullopt
		   and can_post_messages == std::nullopt
		   and can_edit_messages == std::nullopt
		   and can_delete_messages == std::nullopt
		   and can_manage_voice_chats == std::nullopt
		   and can_restrict_members == std::nullopt
		   and can_promote_members == std::nullopt
		   and can_change_info == std::nullopt
		   and can_invite_users == std::nullopt
		   and can_pin_messages == std::nullopt
		   and is_member == std::nullopt
		   and can_send_messages == std::nullopt
		   and can_send_media_messages == std::nullopt
		   and can_send_polls == std::nullopt
		   and can_send_other_messages == std::nullopt
		   and can_add_web_page_previews == std::nullopt
		   and until_date == std::nullopt;
}
