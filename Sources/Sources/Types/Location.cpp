#include "Types/Location.h"

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

Telegram::Location::Location(const QJsonObject& json_object) {
	json_object.contains("longitude")			   ? longitude = json_object["longitude"].toDouble()						: longitude = 0.0;
	json_object.contains("latitude")			   ? latitude = json_object["latitude"].toDouble()							: latitude = 0.0;
	json_object.contains("horizontal_accuracy")	   ? horizontal_accuracy = json_object["horizontal_accuracy"].toDouble()    : horizontal_accuracy = std::nullopt;
	json_object.contains("live_period")			   ? live_period = json_object["live_period"].toInt()						: live_period = std::nullopt;
	json_object.contains("heading")				   ? heading = json_object["heading"].toInt()								: heading = std::nullopt;
	json_object.contains("proximity_alert_radius") ? proximity_alert_radius = json_object["proximity_alert_radius"].toInt() : proximity_alert_radius = std::nullopt;
}

QJsonObject Telegram::Location::toObject() const {
	if (isEmpty()) return {};

	QJsonObject location_json_object{ {"longitude", longitude}, {"latitude", latitude} };

	if (horizontal_accuracy.has_value())	location_json_object.insert("horizontal_accuracy", *horizontal_accuracy);
	if (live_period.has_value())			location_json_object.insert("live_period", *live_period);
	if (heading.has_value())				location_json_object.insert("heading", *heading);
	if (proximity_alert_radius.has_value())	location_json_object.insert("proximity_alert_radius", *proximity_alert_radius);

	return location_json_object;
}

bool Telegram::Location::isEmpty() const {
	return longitude == 0.0
		   and latitude == 0.0
		   and horizontal_accuracy == std::nullopt
		   and live_period == std::nullopt
		   and heading == std::nullopt
		   and proximity_alert_radius == std::nullopt;
}
