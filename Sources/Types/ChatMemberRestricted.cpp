#include "Types\ChatMemberRestricted.h"

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

Telegram::ChatMemberRestricted::ChatMemberRestricted(const QJsonObject& jsonObject)
{
	jsonObject.contains("user")						 ? user = User(jsonObject["user"].toObject())									: user = User();
	jsonObject.contains("is_member")				 ? is_member = jsonObject["is_member"].toBool()									: is_member = false;
	jsonObject.contains("can_change_info")			 ? can_change_info = jsonObject["can_change_info"].toBool()						: can_change_info = false;
	jsonObject.contains("can_invite_users")			 ? can_invite_users = jsonObject["can_invite_users"].toBool()					: can_invite_users = false;
	jsonObject.contains("can_pin_messages")			 ? can_pin_messages = jsonObject["can_pin_messages"].toBool()					: can_pin_messages = false;
	jsonObject.contains("can_send_messages")		 ? can_send_messages = jsonObject["can_send_messages"].toBool()					: can_send_messages = false;
	jsonObject.contains("can_send_media_messages")	 ? can_send_media_messages = jsonObject["can_send_media_messages"].toBool()		: can_send_media_messages = false;
	jsonObject.contains("can_send_polls")			 ? can_send_polls = jsonObject["can_send_polls"].toBool()						: can_send_polls = false;
	jsonObject.contains("can_send_other_messages")	 ? can_send_other_messages = jsonObject["can_send_other_messages"].toBool()		: can_send_other_messages = false;
	jsonObject.contains("can_add_web_page_previews") ? can_add_web_page_previews = jsonObject["can_add_web_page_previews"].toBool() : can_add_web_page_previews = false;
	jsonObject.contains("until_date")				 ? until_date = jsonObject["until_date"].toInt()								: until_date = 0;
}

QJsonObject Telegram::ChatMemberRestricted::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	return QJsonObject{ {"status", status}, {"user", user.toObject()}, {"is_member", is_member}, {"can_change_info", can_change_info}, {"can_invite_users", can_invite_users},
						{"can_pin_messages", can_pin_messages}, {"can_send_messages", can_send_messages}, {"can_send_media_messages", can_send_media_messages}, {"can_send_polls", can_send_polls},
						{"can_send_other_messages", can_send_other_messages}, {"can_add_web_page_previews", can_add_web_page_previews}, {"until_date", until_date} };
}

bool Telegram::ChatMemberRestricted::isEmpty() const
{
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
