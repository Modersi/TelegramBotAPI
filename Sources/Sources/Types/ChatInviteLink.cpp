#include "Types/ChatInviteLink.h"

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

Telegram::ChatInviteLink::ChatInviteLink(const QJsonObject& json_object)
{
	json_object.contains("invite_link")	? invite_link = json_object["invite_link"].toString() : invite_link = "";
	json_object.contains("creator")		? creator = User(json_object["creator"].toObject())   : creator = User();
	json_object.contains("is_primary")	? is_primary = json_object["is_primary"].toBool()	 : is_primary = false;
	json_object.contains("is_revoked")	? is_revoked = json_object["is_revoked"].toBool()	 : is_revoked = false;
	json_object.contains("expire_date")	? expire_date = json_object["expire_date"].toInt()	 : expire_date = std::nullopt;
	json_object.contains("member_limit") ? member_limit = json_object["member_limit"].toInt()  : member_limit = std::nullopt;
}

QJsonObject Telegram::ChatInviteLink::toObject() const {
	if (isEmpty()) return {};

	QJsonObject chat_invite_link_json_object{ {"invite_link", invite_link}, {"creator", creator.toObject()}, {"is_primary", is_primary}, {"is_revoked", is_revoked} };

	if (expire_date.has_value())	chat_invite_link_json_object.insert("expire_date", *expire_date);
	if (member_limit.has_value())	chat_invite_link_json_object.insert("member_limit", *member_limit);

	return chat_invite_link_json_object;
}

bool Telegram::ChatInviteLink::isEmpty() const {
	return invite_link == ""
		   and creator.isEmpty()
		   and is_primary == false
		   and is_revoked == false
		   and expire_date == std::nullopt
		   and member_limit == std::nullopt;
}
