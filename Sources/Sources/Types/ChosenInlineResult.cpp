#include "..\..\Headers\Types\ChosenInlineResult.h"

Telegram::ChosenInlineResult::ChosenInlineResult() :
	result_id(),
	from(),
	query(),
	location(),
	inline_message_id()
{}

Telegram::ChosenInlineResult::ChosenInlineResult(const QString& result_id,
												 const User& from,
												 const QString& query,
												 const std::optional<Location>& location,
												 const std::optional<QString>& inline_message_id) :
	result_id(result_id),
	from(from),
	query(query),
	location(location),
	inline_message_id(inline_message_id)
{}

Telegram::ChosenInlineResult::ChosenInlineResult(const QJsonObject& jsonObject)
{
	jsonObject.contains("result_id")		 ? result_id = jsonObject["result_id"].toString()				: result_id = "";
	jsonObject.contains("from")				 ? from = User(jsonObject["from"].toObject())					: from = User();
	jsonObject.contains("query")			 ? query = jsonObject["query"].toString()						: query = "";
	jsonObject.contains("location")			 ? location = Location(jsonObject["location"].toObject())		: location = std::nullopt;
	jsonObject.contains("inline_message_id") ? inline_message_id = jsonObject["inline_message_id"].toBool() : inline_message_id = std::nullopt;
}

QJsonObject Telegram::ChosenInlineResult::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	QJsonObject chosenInlineResultJsonObject{ {"result_id", result_id}, {"from", from.toObject()}, {"query", query}  };

	if (location.has_value())					chosenInlineResultJsonObject.insert("location", location->toObject());
	if (inline_message_id.has_value())			chosenInlineResultJsonObject.insert("inline_message_id", *inline_message_id);

	return chosenInlineResultJsonObject;
}

bool Telegram::ChosenInlineResult::isEmpty() const
{
	return result_id == ""
		   and from.isEmpty()
		   and query == ""
		   and location == std::nullopt
		   and inline_message_id == std::nullopt;
}
