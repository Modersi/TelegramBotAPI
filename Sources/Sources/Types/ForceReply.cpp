#include "Types/ForceReply.h"

Telegram::ForceReply::ForceReply(const std::optional<QString>& input_field_placeholder,
								 const std::optional<bool>& selective) :
	input_field_placeholder(input_field_placeholder),
	selective(selective)
{}

Telegram::ForceReply::ForceReply(const QJsonObject& json_object) {
	json_object.contains("input_field_placeholder") ? input_field_placeholder = json_object["input_field_placeholder"].toString() : input_field_placeholder = std::nullopt;
	json_object.contains("selective")			    ? selective = json_object["selective"].toBool()								  : selective = std::nullopt;
}

QJsonObject Telegram::ForceReply::toObject() const {
	if (isEmpty()) return {};

	QJsonObject force_reply_json_object{ {"force_reply", true} };

	if (input_field_placeholder.has_value()) force_reply_json_object.insert("input_field_placeholder", *input_field_placeholder);
	if (selective.has_value())				 force_reply_json_object.insert("selective", *selective);

	return force_reply_json_object;
}

bool Telegram::ForceReply::isEmpty() const {
	return input_field_placeholder.has_value() and selective.has_value();
}
