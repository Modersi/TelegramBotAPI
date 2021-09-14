#include "Types/Error.h"

#include "qjsonobject.h"

Telegram::Error::Error() :
	description(""),
	error_code(0)
{}

Telegram::Error::Error(const QString& description, const qint32& error_code) :
	description(description),
	error_code(error_code)
{}

Telegram::Error::Error(const QJsonObject& jsonObject)
{
	jsonObject.contains("description") ? description = jsonObject["description"].toString() : description = "";
	jsonObject.contains("error_code")  ? error_code = jsonObject["error_code"].toInt()		: error_code = 0;
}

QJsonObject Telegram::Error::toObject() const
{
	if(isEmpty())
		return QJsonObject();

	return QJsonObject{ {"description", description}, {"error_code", error_code} };
}

bool Telegram::Error::isEmpty() const
{
	return description == "" and error_code == 0;
}
