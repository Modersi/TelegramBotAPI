#include "Types/Contact.h"

Telegram::Contact::Contact() :
	phone_number(),
	first_name(),
	last_name(),
	user_id(),
	vcard()
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

Telegram::Contact::Contact(const QJsonObject& json_object) {
	json_object.contains("phone_number") ? phone_number = json_object["phone_number"].toString() : phone_number = "";
	json_object.contains("first_name")	 ? first_name = json_object["first_name"].toString()	 : first_name = "";
	json_object.contains("last_name")	 ? last_name = json_object["last_name"].toString()	     : last_name = std::nullopt;
	json_object.contains("user_id")		 ? user_id = json_object["user_id"].toInteger()			 : user_id = std::nullopt;
	json_object.contains("vcard")		 ? vcard = json_object["vcard"].toString()			     : vcard = std::nullopt;
}

QJsonObject Telegram::Contact::toObject() const {
	if (isEmpty()) return {};

	QJsonObject conctact_json_object{ {"phone_number", phone_number}, {"first_name", first_name} };

	if (last_name.has_value())	conctact_json_object.insert("last_name", *last_name);
	if (user_id.has_value())	conctact_json_object.insert("user_id", *user_id);
	if (vcard.has_value())		conctact_json_object.insert("vcard", *vcard);

	return conctact_json_object;
}

bool Telegram::Contact::isEmpty() const {
	return phone_number == ""
		   and first_name == ""
		   and last_name == std::nullopt
		   and user_id == std::nullopt
		   and vcard == std::nullopt;
}
