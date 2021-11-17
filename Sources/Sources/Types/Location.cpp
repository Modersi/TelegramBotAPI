#include "Types/Location.h"

#include "qjsonobject.h"

Telegram::Location::Location() :
	longitude(),
	latitude(),
	horizontal_accuracy(),
	live_period(),
	heading(),
	proximity_alert_radius()
{}

Telegram::Location::Location(const double& longitude,
							 const double& latitude,
							 const std::optional<double>& horizontal_accuracy,
							 const std::optional<int>& live_period,
							 const std::optional<int>& heading,
							 const std::optional<int>& proximity_alert_radius) :
	longitude(longitude),
	latitude(latitude),
	horizontal_accuracy(horizontal_accuracy),
	live_period(live_period),
	heading(heading),
	proximity_alert_radius(proximity_alert_radius)
{}

Telegram::Location::Location(const QJsonObject& jsonObject)
{
	jsonObject.contains("longitude")			  ? longitude = jsonObject["longitude"].toDouble()						  : longitude = 0.0;
	jsonObject.contains("latitude")				  ? latitude = jsonObject["latitude"].toDouble()						  : latitude = 0.0;
	jsonObject.contains("horizontal_accuracy")	  ? horizontal_accuracy = jsonObject["horizontal_accuracy"].toDouble()    : horizontal_accuracy = std::nullopt;
	jsonObject.contains("live_period")			  ? live_period = jsonObject["live_period"].toInt()						  : live_period = std::nullopt;
	jsonObject.contains("heading")				  ? heading = jsonObject["heading"].toInt()								  : heading = std::nullopt;
	jsonObject.contains("proximity_alert_radius") ? proximity_alert_radius = jsonObject["proximity_alert_radius"].toInt() : proximity_alert_radius = std::nullopt;
}

QJsonObject Telegram::Location::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	QJsonObject locationJsonObject{ {"longitude", longitude}, {"latitude", latitude} };

	if (horizontal_accuracy.has_value())	locationJsonObject.insert("horizontal_accuracy", *horizontal_accuracy);
	if (live_period.has_value())			locationJsonObject.insert("live_period", *live_period);
	if (heading.has_value())				locationJsonObject.insert("heading", *heading);
	if (proximity_alert_radius.has_value())	locationJsonObject.insert("proximity_alert_radius", *proximity_alert_radius);

	return locationJsonObject;
}

bool Telegram::Location::isEmpty() const
{
	return longitude == 0.0
		   and latitude == 0.0
		   and horizontal_accuracy == std::nullopt
		   and live_period == std::nullopt
		   and heading == std::nullopt
		   and proximity_alert_radius == std::nullopt;
}
