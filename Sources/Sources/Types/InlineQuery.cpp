#include "Types/InlineQuery.h"

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

Telegram::InlineQuery::InlineQuery(const QJsonObject& json_object) {
	json_object.contains("id")			? id = json_object["id"].toString()																										: id = "";
	json_object.contains("from")		? from = User(json_object["from"].toObject())																							: from = User();
	json_object.contains("query")		? query = json_object["query"].toString()																								: query = "";
	json_object.contains("offset")		? offset = json_object["offset"].toString()																								: offset = "";
	json_object.contains("chat_type")	? chat_type = static_cast<ChatType>(QMetaEnum::fromType<ChatType>().keyToValue(json_object["chat_type"].toString().toUpper().toUtf8())) : chat_type = std::nullopt;
	json_object.contains("location")	? location = Location(json_object["location"].toObject())																				: location = std::nullopt;
}

QJsonObject Telegram::InlineQuery::toObject() const {
	if (isEmpty()) return {};

	QJsonObject inline_query_json_object{ {"id", id}, {"from", from.toObject()}, {"query", query}, {"offset", offset} };

	if (chat_type.has_value())	inline_query_json_object.insert("chat_type", QString(QMetaEnum::fromType<ChatType>().valueToKey(static_cast<int>(*chat_type))).toLower());
	if (location.has_value())	inline_query_json_object.insert("location", location->toObject());

	return inline_query_json_object;
}

bool Telegram::InlineQuery::isEmpty() const {
	return id == ""
		   and from.isEmpty()
		   and query == ""
		   and offset == ""
		   and chat_type == std::nullopt
		   and location == std::nullopt;
}
