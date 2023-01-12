#include "Types/ChatMemberUpdated.h"
#include "Types/ChatMemberAdministrator.h"
#include "Types/ChatMemberBanned.h"
#include "Types/ChatMemberLeft.h"
#include "Types/ChatMemberMember.h"
#include "Types/ChatMemberOwner.h"
#include "Types/ChatMemberRestricted.h"

Telegram::ChatMemberUpdated::ChatMemberUpdated() :
	chat(),
	from(),
	date(),
	old_chat_member(),
	new_chat_member(),
	invite_link()
{}

Telegram::ChatMemberUpdated::ChatMemberUpdated(const Chat& chat,
											   const User& from,
											   const qint32& date,
											   const std::shared_ptr<ChatMember>& old_chat_member,
											   const std::shared_ptr<ChatMember>& new_chat_member,
											   const std::optional<ChatInviteLink>& invite_link) :
	chat(chat),
	from(from),
	date(date),
	old_chat_member(old_chat_member),
	new_chat_member(new_chat_member),
	invite_link(invite_link)
{}

Telegram::ChatMemberUpdated::ChatMemberUpdated(const QJsonObject& json_object)
{
	json_object.contains("chat")	? chat = Chat(json_object["chat"].toObject()) : chat = Chat();
	json_object.contains("from")	? from = User(json_object["from"].toObject()) : from = User();
	json_object.contains("date")	? date = json_object["date"].toInt()		  : date = 0;

	if (json_object.contains("old_chat_member"))
	{
		if (json_object["old_chat_member"].toObject()["status"] == "administrator")	  old_chat_member = std::make_shared<ChatMemberAdministrator>(json_object["old_chat_member"].toObject());
		else if (json_object["old_chat_member"].toObject()["status"] == "kicked")	  old_chat_member = std::make_shared<ChatMemberBanned>(json_object["old_chat_member"].toObject());
		else if (json_object["old_chat_member"].toObject()["status"] == "left")		  old_chat_member = std::make_shared<ChatMemberLeft>(json_object["old_chat_member"].toObject());
		else if (json_object["old_chat_member"].toObject()["status"] == "member")	  old_chat_member = std::make_shared<ChatMemberMember>(json_object["old_chat_member"].toObject());
		else if (json_object["old_chat_member"].toObject()["status"] == "creator")	  old_chat_member = std::make_shared<ChatMemberOwner>(json_object["old_chat_member"].toObject());
		else if (json_object["old_chat_member"].toObject()["status"] == "restricted") old_chat_member = std::make_shared<ChatMemberRestricted>(json_object["old_chat_member"].toObject());
	}
	else old_chat_member = nullptr;

	if (json_object.contains("new_chat_member"))
	{
		if (json_object["new_chat_member"].toObject()["status"] == "administrator")	  new_chat_member = std::make_shared<ChatMemberAdministrator>(json_object["new_chat_member"].toObject());
		else if (json_object["new_chat_member"].toObject()["status"] == "kicked")	  new_chat_member = std::make_shared<ChatMemberBanned>(json_object["new_chat_member"].toObject());
		else if (json_object["new_chat_member"].toObject()["status"] == "left")		  new_chat_member = std::make_shared<ChatMemberLeft>(json_object["new_chat_member"].toObject());
		else if (json_object["new_chat_member"].toObject()["status"] == "member")	  new_chat_member = std::make_shared<ChatMemberMember>(json_object["new_chat_member"].toObject());
		else if (json_object["new_chat_member"].toObject()["status"] == "creator")	  new_chat_member = std::make_shared<ChatMemberOwner>(json_object["new_chat_member"].toObject());
		else if (json_object["new_chat_member"].toObject()["status"] == "restricted") new_chat_member = std::make_shared<ChatMemberRestricted>(json_object["new_chat_member"].toObject());
	}
	else new_chat_member = nullptr;

	json_object.contains("invite_link") ? invite_link = ChatInviteLink(json_object["invite_link"].toObject()) : invite_link = std::nullopt;
}

QJsonObject Telegram::ChatMemberUpdated::toObject() const {
	if (isEmpty()) return {};

	QJsonObject chat_member_updated_json_object{ {"chat", chat.toObject()}, {"from", from.toObject()}, {"date", date}, {"old_chat_member", old_chat_member->toObject()}, {"status", new_chat_member->toObject()} };

	if (invite_link.has_value()) chat_member_updated_json_object.insert("invite_link", invite_link->toObject());

	return chat_member_updated_json_object;
}

bool Telegram::ChatMemberUpdated::isEmpty() const {
	return chat.isEmpty()
		   and from.isEmpty()
		   and date == 0
		   and old_chat_member->isEmpty()
		   and new_chat_member->isEmpty()
		   and invite_link == std::nullopt;
}
