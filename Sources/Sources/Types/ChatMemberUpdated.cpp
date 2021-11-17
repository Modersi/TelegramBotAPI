#include "Types/ChatMemberUpdated.h"
#include "Types/ChatMemberAdministrator.h"
#include "Types/ChatMemberBanned.h"
#include "Types/ChatMemberLeft.h"
#include "Types/ChatMemberMember.h"
#include "Types/ChatMemberOwner.h"
#include "Types/ChatMemberRestricted.h"

#include "qjsonobject.h"

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

Telegram::ChatMemberUpdated::ChatMemberUpdated(const QJsonObject& jsonObject)
{
	jsonObject.contains("chat")	? chat = Chat(jsonObject["chat"].toObject()) : chat = Chat();
	jsonObject.contains("from")	? from = User(jsonObject["from"].toObject()) : from = User();
	jsonObject.contains("date")	? date = jsonObject["date"].toInt()			 : date = 0;

	if (jsonObject.contains("old_chat_member"))
	{
		if (jsonObject["old_chat_member"].toObject()["status"] == "administrator")	 old_chat_member = std::make_shared<ChatMemberAdministrator>(jsonObject["old_chat_member"].toObject());
		else if (jsonObject["old_chat_member"].toObject()["status"] == "kicked")	 old_chat_member = std::make_shared<ChatMemberBanned>(jsonObject["old_chat_member"].toObject());
		else if (jsonObject["old_chat_member"].toObject()["status"] == "left")		 old_chat_member = std::make_shared<ChatMemberLeft>(jsonObject["old_chat_member"].toObject());
		else if (jsonObject["old_chat_member"].toObject()["status"] == "member")	 old_chat_member = std::make_shared<ChatMemberMember>(jsonObject["old_chat_member"].toObject());
		else if (jsonObject["old_chat_member"].toObject()["status"] == "creator")	 old_chat_member = std::make_shared<ChatMemberOwner>(jsonObject["old_chat_member"].toObject());
		else if (jsonObject["old_chat_member"].toObject()["status"] == "restricted") old_chat_member = std::make_shared<ChatMemberRestricted>(jsonObject["old_chat_member"].toObject());
	}
	else old_chat_member = nullptr;

	if (jsonObject.contains("new_chat_member"))
	{
		if (jsonObject["new_chat_member"].toObject()["status"] == "administrator")	 new_chat_member = std::make_shared<ChatMemberAdministrator>(jsonObject["new_chat_member"].toObject());
		else if (jsonObject["new_chat_member"].toObject()["status"] == "kicked")	 new_chat_member = std::make_shared<ChatMemberBanned>(jsonObject["new_chat_member"].toObject());
		else if (jsonObject["new_chat_member"].toObject()["status"] == "left")		 new_chat_member = std::make_shared<ChatMemberLeft>(jsonObject["new_chat_member"].toObject());
		else if (jsonObject["new_chat_member"].toObject()["status"] == "member")	 new_chat_member = std::make_shared<ChatMemberMember>(jsonObject["new_chat_member"].toObject());
		else if (jsonObject["new_chat_member"].toObject()["status"] == "creator")	 new_chat_member = std::make_shared<ChatMemberOwner>(jsonObject["new_chat_member"].toObject());
		else if (jsonObject["new_chat_member"].toObject()["status"] == "restricted") new_chat_member = std::make_shared<ChatMemberRestricted>(jsonObject["new_chat_member"].toObject());
	}
	else new_chat_member = nullptr;

	jsonObject.contains("invite_link") ? invite_link = ChatInviteLink(jsonObject["invite_link"].toObject())	: invite_link = std::nullopt;
}

QJsonObject Telegram::ChatMemberUpdated::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	QJsonObject chatMemberUpdatedJsonObject{ {"chat", chat.toObject()}, {"from", from.toObject()}, {"date", date}, {"old_chat_member", old_chat_member->toObject()}, {"status", new_chat_member->toObject()} };

	if (invite_link.has_value()) chatMemberUpdatedJsonObject.insert("invite_link", invite_link->toObject());

	return chatMemberUpdatedJsonObject;
}

bool Telegram::ChatMemberUpdated::isEmpty() const
{
	return chat.isEmpty()
		   and from.isEmpty()
		   and date == 0
		   and old_chat_member->isEmpty()
		   and new_chat_member->isEmpty()
		   and invite_link == std::nullopt;
}
