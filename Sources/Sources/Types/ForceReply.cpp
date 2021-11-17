#include "Types\ForceReply.h"

#include "qjsonobject.h"

Telegram::ForceReply::ForceReply(const std::optional<QString>& input_field_placeholder,
								 const std::optional<bool>& selective) :
	input_field_placeholder(input_field_placeholder),
	selective(selective)
{}

Telegram::ForceReply::ForceReply(const QJsonObject& jsonObject)
{
	jsonObject.contains("input_field_placeholder") ? input_field_placeholder = jsonObject["input_field_placeholder"].toString() : input_field_placeholder = std::nullopt;
	jsonObject.contains("selective")			   ? selective = jsonObject["selective"].toBool()								: selective = std::nullopt;
}

QJsonObject Telegram::ForceReply::toObject() const
{
	QJsonObject forceReplyJsonObject{ {"force_reply", true} };

	if (input_field_placeholder.has_value()) forceReplyJsonObject.insert("input_field_placeholder", *input_field_placeholder);
	if (selective.has_value())				 forceReplyJsonObject.insert("selective", *selective);

	return forceReplyJsonObject;
}
