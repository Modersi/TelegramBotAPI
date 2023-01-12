#include "Types/ChosenInlineResult.h"

#include "qjsonobject.h"

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

Telegram::ChosenInlineResult::ChosenInlineResult(const QJsonObject& json_object) {
	json_object.contains("result_id")			? result_id = json_object["result_id"].toString()				  : result_id = "";
	json_object.contains("from")				? from = User(json_object["from"].toObject())					  : from = User();
	json_object.contains("query")				? query = json_object["query"].toString()						  : query = "";
	json_object.contains("location")			? location = Location(json_object["location"].toObject())		  : location = std::nullopt;
	json_object.contains("inline_message_id")	? inline_message_id = json_object["inline_message_id"].toString() : inline_message_id = std::nullopt;
}

QJsonObject Telegram::ChosenInlineResult::toObject() const {
	if (isEmpty()) return {};

	QJsonObject chosen_inline_result_json_object{ {"result_id", result_id}, {"from", from.toObject()}, {"query", query}  };

	if (location.has_value())					chosen_inline_result_json_object.insert("location", location->toObject());
	if (inline_message_id.has_value())			chosen_inline_result_json_object.insert("inline_message_id", *inline_message_id);

	return chosen_inline_result_json_object;
}

bool Telegram::ChosenInlineResult::isEmpty() const {
	return result_id == ""
		   and from.isEmpty()
		   and query == ""
		   and location == std::nullopt
		   and inline_message_id == std::nullopt;
}
