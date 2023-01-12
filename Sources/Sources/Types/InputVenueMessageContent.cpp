#include "Types/InputVenueMessageContent.h"

Telegram::InputVenueMessageContent::InputVenueMessageContent() :
	latitude(),
	longitude(),
	title(),
	address(),
	foursquare_id(),
	foursquare_type(),
	google_place_id(),
	google_place_type()
{}

Telegram::InputVenueMessageContent::InputVenueMessageContent(const float& latitude,
															 const float& longitude,
															 const QString& title,
															 const QString& address,
															 const std::optional<QString>& foursquare_id,
															 const std::optional<QString>& foursquare_type,
															 const std::optional<QString>& google_place_id,
															 const std::optional<QString>& google_place_type) :
	latitude(latitude),
	longitude(longitude),
	title(title),
	address(address),
	foursquare_id(foursquare_id),
	foursquare_type(foursquare_type),
	google_place_id(google_place_id),
	google_place_type(google_place_type)
{}

QJsonObject Telegram::InputVenueMessageContent::toObject() const {
	if (isEmpty()) return {};

	QJsonObject input_venue_message_content_json_object{ {"latitude", latitude}, {"longitude", longitude}, {"title", title}, {"address", address} };

	if (foursquare_id.has_value())		input_venue_message_content_json_object.insert("foursquare_id", *foursquare_id);
	if (foursquare_type.has_value())	input_venue_message_content_json_object.insert("foursquare_type", *foursquare_type);
	if (google_place_id.has_value())	input_venue_message_content_json_object.insert("google_place_id", *google_place_id);
	if (google_place_type.has_value())	input_venue_message_content_json_object.insert("google_place_type", *google_place_type);

	return input_venue_message_content_json_object;
}

bool Telegram::InputVenueMessageContent::isEmpty() const {
	return latitude == 0.0
		and longitude == 0.0
		and title == ""
		and address == ""
		and foursquare_id == std::nullopt
		and foursquare_type == std::nullopt
		and google_place_id == std::nullopt
		and google_place_type == std::nullopt;
}
