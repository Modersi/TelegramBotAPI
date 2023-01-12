#include "Types/ResponseParameters.h"

Telegram::ResponseParameters::ResponseParameters(const std::optional<qint64>& migrate_to_chat_id,
												 const std::optional<qint32>& retry_after) :
	migrate_to_chat_id(migrate_to_chat_id),
	retry_after(retry_after)
{}

Telegram::ResponseParameters::ResponseParameters(const QJsonObject& json_object) {
	json_object.contains("migrate_to_chat_id")	? migrate_to_chat_id = json_object["migrate_to_chat_id"].toInteger()	: migrate_to_chat_id = std::nullopt;
	json_object.contains("retry_after")			? retry_after = json_object["retry_after"].toInt()						: retry_after = std::nullopt;
}

QJsonObject Telegram::ResponseParameters::toObject() const {
	if (isEmpty()) return {};

	QJsonObject response_parameters_json_object;

	if (migrate_to_chat_id.has_value())		response_parameters_json_object.insert("migrate_to_chat_id", *migrate_to_chat_id);
	if (retry_after.has_value())			response_parameters_json_object.insert("retry_after", *retry_after);

	return response_parameters_json_object;
}

bool Telegram::ResponseParameters::isEmpty() const {
	return migrate_to_chat_id == std::nullopt and retry_after == std::nullopt;
}
