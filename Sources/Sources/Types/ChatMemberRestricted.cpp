#include "Types/ChatMemberRestricted.h"

Telegram::ChatMemberRestricted::ChatMemberRestricted() :
	user(),
	is_member(),
	can_change_info(),
	can_invite_users(),
	can_pin_messages(),
	can_send_messages(),
	can_send_media_messages(),
	can_send_polls(),
	can_send_other_messages(),
	can_add_web_page_previews(),
	until_date()
{}

Telegram::ChatMemberRestricted::ChatMemberRestricted(const User& user,
													 const bool& is_member,
													 const bool& can_change_info,
													 const bool& can_invite_users,
													 const bool& can_pin_messages,
													 const bool& can_send_messages,
													 const bool& can_send_media_messages,
													 const bool& can_send_polls,
													 const bool& can_send_other_messages,
													 const bool& can_add_web_page_previews,
													 const qint32& until_date) :
	user(user),
	is_member(is_member),
	can_change_info(can_change_info),
	can_invite_users(can_invite_users),
	can_pin_messages(can_pin_messages),
	can_send_messages(can_send_messages),
	can_send_media_messages(can_send_media_messages),
	can_send_polls(can_send_polls),
	can_send_other_messages(can_send_other_messages),
	can_add_web_page_previews(can_add_web_page_previews),
	until_date(until_date)
{}

Telegram::ChatMemberRestricted::ChatMemberRestricted(const QJsonObject& json_object) {
	json_object.contains("user")					  ? user = User(json_object["user"].toObject())										: user = User();
	json_object.contains("is_member")				  ? is_member = json_object["is_member"].toBool()									: is_member = false;
	json_object.contains("can_change_info")			  ? can_change_info = json_object["can_change_info"].toBool()						: can_change_info = false;
	json_object.contains("can_invite_users")		  ? can_invite_users = json_object["can_invite_users"].toBool()						: can_invite_users = false;
	json_object.contains("can_pin_messages")		  ? can_pin_messages = json_object["can_pin_messages"].toBool()						: can_pin_messages = false;
	json_object.contains("can_send_messages")		  ? can_send_messages = json_object["can_send_messages"].toBool()					: can_send_messages = false;
	json_object.contains("can_send_media_messages")	  ? can_send_media_messages = json_object["can_send_media_messages"].toBool()		: can_send_media_messages = false;
	json_object.contains("can_send_polls")			  ? can_send_polls = json_object["can_send_polls"].toBool()							: can_send_polls = false;
	json_object.contains("can_send_other_messages")	  ? can_send_other_messages = json_object["can_send_other_messages"].toBool()		: can_send_other_messages = false;
	json_object.contains("can_add_web_page_previews") ? can_add_web_page_previews = json_object["can_add_web_page_previews"].toBool()	: can_add_web_page_previews = false;
	json_object.contains("until_date")				  ? until_date = json_object["until_date"].toInt()									: until_date = 0;
}

QJsonObject Telegram::ChatMemberRestricted::toObject() const {
	if (isEmpty()) return {};

	return QJsonObject{ {"status", QString(QMetaEnum::fromType<decltype(status)>().valueToKey(static_cast<int>(status))).toLower()}, {"user", user.toObject()}, {"is_member", is_member}, {"can_change_info", can_change_info}, {"can_invite_users", can_invite_users},
						{"can_pin_messages", can_pin_messages}, {"can_send_messages", can_send_messages}, {"can_send_media_messages", can_send_media_messages}, {"can_send_polls", can_send_polls},
						{"can_send_other_messages", can_send_other_messages}, {"can_add_web_page_previews", can_add_web_page_previews}, {"until_date", until_date} };
}

bool Telegram::ChatMemberRestricted::isEmpty() const {
	return user.isEmpty()
		   and is_member == false
		   and can_change_info == false
		   and can_invite_users == false
		   and can_pin_messages == false
		   and can_send_messages == false
		   and can_send_media_messages == false
		   and can_send_polls == false
		   and can_send_other_messages == false
		   and can_add_web_page_previews == false
		   and until_date == 0;
}

Telegram::ChatMember::Status Telegram::ChatMemberRestricted::getStatus() const {
	return status;
}
