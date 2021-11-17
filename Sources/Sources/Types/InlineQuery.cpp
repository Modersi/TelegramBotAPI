#include "Types/InlineQuery.h"

#include "qjsonobject.h"

Telegram::InlineQuery::InlineQuery() :
	id(),
	from(),
	query(),
	offset(),
	chat_type(),
	location()
{}

Telegram::InlineQuery::InlineQuery(const QString& id,
								   const User& from,
								   const QString& query,
								   const QString& offset,
								   const std::optional<ChatType>& chat_type,
								   const std::optional<Location>& location) :
	id(id),
	from(from),
	query(query),
	offset(offset),
	chat_type(chat_type),
	location(location)
{}

Telegram::InlineQuery::InlineQuery(const QJsonObject& jsonObject)
{
	auto GetChatType = [](const QJsonValue& chatType) -> InlineQuery::ChatType
	{
		if (chatType == "sender")		   return ChatType::SENDER;
		else if (chatType == "private")	   return ChatType::PRIVATE;
		else if (chatType == "group")	   return ChatType::GROUP;
		else if (chatType == "supergroup") return ChatType::SUPERGROUP;
		else if (chatType == "channel")	   return ChatType::CHANNEL;
		else return ChatType::UNINITIALIZED_VALUE;
	};

	jsonObject.contains("id")		 ? id = jsonObject["id"].toString()						  : id = "";
	jsonObject.contains("from")		 ? from = User(jsonObject["from"].toObject())			  : from = User();
	jsonObject.contains("query")	 ? query = jsonObject["query"].toString()				  : query = "";
	jsonObject.contains("offset")	 ? offset = jsonObject["offset"].toString()				  : offset = "";
	jsonObject.contains("chat_type") ? chat_type = GetChatType(jsonObject["chat_type"])		  : chat_type = std::nullopt;
	jsonObject.contains("location")  ? location = Location(jsonObject["location"].toObject()) : location = std::nullopt;
}

QJsonObject Telegram::InlineQuery::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	auto GetChatTypeInString = [](const InlineQuery::ChatType& chatType) -> QString
	{
		if (chatType == ChatType::SENDER)		   return "sender";
		else if (chatType == ChatType::PRIVATE)	   return "private";
		else if (chatType == ChatType::GROUP)	   return "group";
		else if (chatType == ChatType::SUPERGROUP) return "supergroup";
		else if (chatType == ChatType::CHANNEL)	   return "channel";
		else return "";
	};

	QJsonObject inlineQueryJsonObject{ {"id", id}, {"from", from.toObject()}, {"query", query}, {"offset", offset} };

	if (chat_type.has_value())	inlineQueryJsonObject.insert("chat_type", GetChatTypeInString(*chat_type));
	if (location.has_value())	inlineQueryJsonObject.insert("location", location->toObject());

	return inlineQueryJsonObject;
}

bool Telegram::InlineQuery::isEmpty() const
{
	return id == ""
		   and from.isEmpty()
		   and query == ""
		   and offset == ""
		   and chat_type == std::nullopt
		   and location == std::nullopt;
}
