#include "Types/Venue.h"

Telegram::Venue::Venue() :
	location(),
	title(),
	address(),
	foursquare_id(),
	foursquare_type(),
	google_place_id(),
	google_place_type()
{}

Telegram::Venue::Venue(const Location& location,
					   const QString& title,
					   const QString& address,
					   const std::optional<QString>& foursquare_id,
					   const std::optional<QString>& foursquare_type,
					   const std::optional<QString>& google_place_id,
					   const std::optional<QString>& google_place_type) :
	location(location),
	title(title),
	address(address),
	foursquare_id(foursquare_id),
	foursquare_type(foursquare_type),
	google_place_id(google_place_id),
	google_place_type(google_place_type)
{
}

Telegram::Venue::Venue(const QJsonObject& json_object) {
	json_object.contains("location")			? location = Location(json_object["location"].toObject())	      : location = Location();
	json_object.contains("title")				? title = json_object["title"].toString()						  : title = "";
	json_object.contains("address")				? address = json_object["address"].toString()					  : address = "";
	json_object.contains("foursquare_id")		? foursquare_id = json_object["foursquare_id"].toString()		  : foursquare_id = std::nullopt;
	json_object.contains("foursquare_type")		? foursquare_type = json_object["foursquare_type"].toString()	  : foursquare_type = std::nullopt;
	json_object.contains("google_place_id")		? google_place_id = json_object["google_place_id"].toString()	  : google_place_id = std::nullopt;
	json_object.contains("google_place_type")	? google_place_type = json_object["google_place_type"].toString() : google_place_type = std::nullopt;
}

QJsonObject Telegram::Venue::toObject() const {
	if (isEmpty()) return {};

	QJsonObject venue_json_object{ {"location", location.toObject()}, {"title", title}, {"address", address} };

	if (foursquare_id.has_value())		venue_json_object.insert("foursquare_id", *foursquare_id);
	if (foursquare_type.has_value())	venue_json_object.insert("foursquare_type", *foursquare_type);
	if (google_place_id.has_value())	venue_json_object.insert("google_place_id", *google_place_id);
	if (google_place_type.has_value())	venue_json_object.insert("google_place_type", *google_place_type);

	return venue_json_object;
}

bool Telegram::Venue::isEmpty() const {
	return location.isEmpty()
		   and title == ""
		   and address == ""
		   and foursquare_id == std::nullopt
		   and foursquare_type == std::nullopt
		   and google_place_id == std::nullopt
		   and google_place_type == std::nullopt;
}
