#include "Types/ChatLocation.h"

Telegram::ChatLocation::ChatLocation() :
	location(),
	address()
{}

Telegram::ChatLocation::ChatLocation(const Location& location,
									 const QString& address) :
	location(location),
	address(address)
{}

Telegram::ChatLocation::ChatLocation(const QJsonObject& jsonObject)
{
	jsonObject.contains("location") ? location = Location(jsonObject["location"].toObject()) : location = Location();
	jsonObject.contains("address")	? address = jsonObject["address"].toString()			 : address = "";
}

QJsonObject Telegram::ChatLocation::toObject() const {
	if (isEmpty()) return {};

	return QJsonObject{ {"location", location.toObject()}, {"address", address} };
}

bool Telegram::ChatLocation::isEmpty() const {
	return location.isEmpty() and address == "";
}
