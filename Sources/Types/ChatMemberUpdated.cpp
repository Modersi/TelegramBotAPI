#include "Types/ChatMemberUpdated.h"

#include "qjsonobject.h"

Telegram::ChatMemberUpdated::ChatMemberUpdated() :
	chat(Chat()),
	from(User()),
	date(0),
	old_chat_member(ChatMember()),
	new_chat_member(ChatMember()),
	invite_link(std::nullopt)
{}

Telegram::ChatMemberUpdated::ChatMemberUpdated(const Chat& chat,
											   const User& from,
											   const qint32& date,
											   const ChatMember& old_chat_member,
											   const ChatMember& new_chat_member,
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
	jsonObject.contains("chat")			   ? chat = Chat(jsonObject["chat"].toObject())								: chat = Chat();
	jsonObject.contains("from")			   ? from = User(jsonObject["from"].toObject())								: from = User();
	jsonObject.contains("date")			   ? date = jsonObject["date"].toInt()										: date = 0;
	jsonObject.contains("old_chat_member") ? old_chat_member = ChatMember(jsonObject["old_chat_member"].toObject()) : old_chat_member = ChatMember();
	jsonObject.contains("new_chat_member") ? new_chat_member = ChatMember(jsonObject["new_chat_member"].toObject()) : new_chat_member = ChatMember();
	jsonObject.contains("invite_link")	   ? invite_link = ChatInviteLink(jsonObject["invite_link"].toObject())		: invite_link = std::nullopt;
}

QJsonObject Telegram::ChatMemberUpdated::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	QJsonObject chatMemberUpdatedJsonObject{ {"chat", chat.toObject()}, {"from", from.toObject()}, {"date", date}, {"old_chat_member", old_chat_member.toObject()}, {"status", new_chat_member.toObject()} };

	if (invite_link.has_value()) chatMemberUpdatedJsonObject.insert("invite_link", invite_link->toObject());

	return chatMemberUpdatedJsonObject;
}

bool Telegram::ChatMemberUpdated::isEmpty() const
{
	return chat.isEmpty()
		   and from.isEmpty()
		   and date == 0
		   and old_chat_member.isEmpty()
		   and new_chat_member.isEmpty()
		   and invite_link == std::nullopt;
}
