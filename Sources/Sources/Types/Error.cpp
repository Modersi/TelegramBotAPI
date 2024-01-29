#include "Types/Error.h"

Telegram::Error::Error() :
	description(),
	error_code()
{}

Telegram::Error::Error(const QString& description, const qint32& error_code) :
	description(description),
	error_code(error_code)
{}

Telegram::Error::Error(const QJsonObject& json_object) {
	json_object.contains("description") ? description = json_object["description"].toString()	: description = "";
	json_object.contains("error_code")  ? error_code = json_object["error_code"].toInt()		: error_code = 0;
}

QJsonObject Telegram::Error::toObject() const {
	if (isEmpty()) return {};

	return QJsonObject{ {"description", description}, {"error_code", error_code} };
}

bool Telegram::Error::isEmpty() const {
	return description == "" and error_code == 0;
}
