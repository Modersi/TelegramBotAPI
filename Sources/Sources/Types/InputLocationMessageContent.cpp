#include "Types/InputLocationMessageContent.h"

Telegram::InputLocationMessageContent::InputLocationMessageContent() :
	latitude(),
	longitude(),
	horizontal_accuracy(),
	live_period(),
	heading(),
	proximity_alert_radius()
{}

Telegram::InputLocationMessageContent::InputLocationMessageContent(const float& latitude,
																   const float& longitude,
																   const std::optional<float>& horizontal_accuracy,
																   const std::optional<qint32>& live_period,
																   const std::optional<qint32>& heading,
																   const std::optional<qint32>& proximity_alert_radius) :
	latitude(latitude),
	longitude(longitude),
	horizontal_accuracy(horizontal_accuracy),
	live_period(live_period),
	heading(heading),
	proximity_alert_radius(proximity_alert_radius)
{}

QJsonObject Telegram::InputLocationMessageContent::toObject() const {
	if (isEmpty()) return {};

	QJsonObject input_location_message_content_json_object{ {"latitude", latitude}, {"longitude", longitude} };

	if (horizontal_accuracy.has_value())	input_location_message_content_json_object.insert("horizontal_accuracy", *horizontal_accuracy);
	if (live_period.has_value())			input_location_message_content_json_object.insert("live_period", *live_period);
	if (heading.has_value())				input_location_message_content_json_object.insert("heading", *heading);
	if (proximity_alert_radius.has_value())	input_location_message_content_json_object.insert("proximity_alert_radius", *proximity_alert_radius);


	return input_location_message_content_json_object;
}

bool Telegram::InputLocationMessageContent::isEmpty() const {
	return latitude == 0.0
		   and longitude == 0.0
		   and horizontal_accuracy == std::nullopt
		   and live_period == std::nullopt
		   and heading == std::nullopt
		   and proximity_alert_radius == std::nullopt;
}
