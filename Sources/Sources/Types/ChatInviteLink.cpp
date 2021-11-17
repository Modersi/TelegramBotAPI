#include "Types/ChatInviteLink.h"

#include "qjsonobject.h"

Telegram::ChatInviteLink::ChatInviteLink() :
	invite_link(),
	creator(),
	is_primary(),
	is_revoked(),
	expire_date(),
	member_limit()
{}

Telegram::ChatInviteLink::ChatInviteLink(const QString& invite_link,
										 const User& creator,
										 const bool& is_primary,
										 const bool& is_revoked,
										 const std::optional<qint32>& expire_date,
										 const std::optional<qint32>& member_limit) :
	invite_link(invite_link),
	creator(creator),
	is_primary(is_primary),
	is_revoked(is_revoked),
	expire_date(expire_date),
	member_limit(member_limit)
{}

Telegram::ChatInviteLink::ChatInviteLink(const QJsonObject& jsonObject)
{
	jsonObject.contains("invite_link")	? invite_link = jsonObject["invite_link"].toString() : invite_link = "";
	jsonObject.contains("creator")		? creator = User(jsonObject["creator"].toObject())   : creator = User();
	jsonObject.contains("is_primary")	? is_primary = jsonObject["is_primary"].toBool()	 : is_primary = false;
	jsonObject.contains("is_revoked")	? is_revoked = jsonObject["is_revoked"].toBool()	 : is_revoked = false;
	jsonObject.contains("expire_date")	? expire_date = jsonObject["expire_date"].toInt()	 : expire_date = std::nullopt;
	jsonObject.contains("member_limit") ? member_limit = jsonObject["member_limit"].toInt()  : member_limit = std::nullopt;
}

QJsonObject Telegram::ChatInviteLink::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	QJsonObject chatInviteLinkJsonObject{ {"invite_link", invite_link}, {"creator", creator.toObject()}, {"is_primary", is_primary}, {"is_revoked", is_revoked} };

	if (expire_date.has_value())	chatInviteLinkJsonObject.insert("expire_date", *expire_date);
	if (member_limit.has_value())	chatInviteLinkJsonObject.insert("member_limit", *member_limit);

	return chatInviteLinkJsonObject;
}

bool Telegram::ChatInviteLink::isEmpty() const
{
	return invite_link == ""
		   and creator.isEmpty()
		   and is_primary == false
		   and is_revoked == false
		   and expire_date == std::nullopt
		   and member_limit == std::nullopt;
}
