#include "Types/ResponseParameters.h"

#include "qjsonobject.h"

Telegram::ResponseParameters::ResponseParameters(const std::optional<qint64>& migrate_to_chat_id,
												 const std::optional<qint32>& retry_after) :
	migrate_to_chat_id(migrate_to_chat_id),
	retry_after(retry_after)
{}

Telegram::ResponseParameters::ResponseParameters(const QJsonObject& jsonObject)
{
	jsonObject.contains("migrate_to_chat_id") ? migrate_to_chat_id = jsonObject["migrate_to_chat_id"].toInt() : migrate_to_chat_id = std::nullopt;
	jsonObject.contains("retry_after")		  ? retry_after = jsonObject["retry_after"].toInt()				  : retry_after = std::nullopt;
}

QJsonObject Telegram::ResponseParameters::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	QJsonObject responseParametersJsonObject;

	if (migrate_to_chat_id.has_value())		responseParametersJsonObject.insert("migrate_to_chat_id", *migrate_to_chat_id);
	if (retry_after.has_value())			responseParametersJsonObject.insert("retry_after", *retry_after);

	return responseParametersJsonObject;
}

bool Telegram::ResponseParameters::isEmpty() const
{
	return migrate_to_chat_id == std::nullopt and retry_after == std::nullopt;
}
