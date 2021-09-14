#include "Types/Contact.h"

#include "qjsonobject.h"

Telegram::Contact::Contact() :
	phone_number(""),
	first_name(""),
	last_name(std::nullopt),
	user_id(std::nullopt),
	vcard(std::nullopt)
{}

Telegram::Contact::Contact(const QString& phone_number,
						   const QString& first_name,
						   const std::optional<QString>& last_name,
						   const std::optional<qint64>& user_id,
						   const std::optional<QString>& vcard) :
	phone_number(phone_number),
	first_name(first_name),
	last_name(last_name),
	user_id(user_id),
	vcard(vcard)
{}

Telegram::Contact::Contact(const QJsonObject& jsonObject)
{
	jsonObject.contains("phone_number") ? phone_number = jsonObject["phone_number"].toString() : phone_number = "";
	jsonObject.contains("first_name")	? first_name = jsonObject["first_name"].toString()	   : first_name = "";
	jsonObject.contains("last_name")	? last_name = jsonObject["last_name"].toString()	   : last_name = std::nullopt;
	jsonObject.contains("user_id")		? user_id = jsonObject["user_id"].toInt()			   : user_id = std::nullopt;
	jsonObject.contains("vcard")		? vcard = jsonObject["vcard"].toString()			   : vcard = std::nullopt;
}

QJsonObject Telegram::Contact::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	QJsonObject conctactJsonObject{ {"phone_number", phone_number}, {"first_name", first_name} };

	if (last_name.has_value())	conctactJsonObject.insert("last_name", *last_name);
	if (user_id.has_value())	conctactJsonObject.insert("user_id", *user_id);
	if (vcard.has_value())		conctactJsonObject.insert("vcard", *vcard);

	return conctactJsonObject;
}

bool Telegram::Contact::isEmpty() const
{
	return phone_number == ""
		   and first_name == ""
		   and last_name == std::nullopt
		   and user_id == std::nullopt
		   and vcard == std::nullopt;
}
