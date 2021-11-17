#include "Types/InputContactMessageContent.h"

Telegram::InputContactMessageContent::InputContactMessageContent() :
	phone_number(),
	first_name(),
	last_name(),
	vcard()
{}

Telegram::InputContactMessageContent::InputContactMessageContent(const QString& phone_number,
																 const QString& first_name,
																 const std::optional<QString>& last_name,
																 const std::optional<QString>& vcard) :
	phone_number(phone_number),
	first_name(first_name),
	last_name(last_name),
	vcard(vcard)
{}

QJsonObject Telegram::InputContactMessageContent::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	QJsonObject inputContactMessageContentJsonObject{ {"phone_number", phone_number}, {"first_name", first_name} };

	if (last_name.has_value())	inputContactMessageContentJsonObject.insert("last_name", *last_name);
	if (vcard.has_value())		inputContactMessageContentJsonObject.insert("vcard", *vcard);

	return inputContactMessageContentJsonObject;
}

bool Telegram::InputContactMessageContent::isEmpty() const
{
	return phone_number == ""
		   and first_name == ""
		   and last_name == std::nullopt
		   and vcard == std::nullopt;
}
