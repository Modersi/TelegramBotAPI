#include "Types/Venue.h"

#include "qjsonobject.h"

Telegram::Venue::Venue() :
	location(Location()),
	title(""),
	address(""),
	foursquare_id(std::nullopt),
	foursquare_type(std::nullopt),
	google_place_id(std::nullopt),
	google_place_type(std::nullopt)
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

Telegram::Venue::Venue(const QJsonObject& jsonObject)
{
	jsonObject.contains("location")			 ? location = Location(jsonObject["location"].toObject())	      : location = Location();
	jsonObject.contains("title")			 ? title = jsonObject["title"].toString()						  : title = "";
	jsonObject.contains("address")			 ? address = jsonObject["address"].toString()					  : address = "";
	jsonObject.contains("foursquare_id")	 ? foursquare_id = jsonObject["foursquare_id"].toString()		  : foursquare_id = std::nullopt;
	jsonObject.contains("foursquare_type")	 ? foursquare_type = jsonObject["foursquare_type"].toString()	  : foursquare_type = std::nullopt;
	jsonObject.contains("google_place_id")	 ? google_place_id = jsonObject["google_place_id"].toString()	  : google_place_id = std::nullopt;
	jsonObject.contains("google_place_type") ? google_place_type = jsonObject["google_place_type"].toString() : google_place_type = std::nullopt;
}

QJsonObject Telegram::Venue::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	QJsonObject venueJsonObject{ {"location", location.toObject()}, {"title", title}, {"address", address} };

	if (foursquare_id.has_value())		venueJsonObject.insert("foursquare_id", *foursquare_id);
	if (foursquare_type.has_value())	venueJsonObject.insert("foursquare_type", *foursquare_type);
	if (google_place_id.has_value())	venueJsonObject.insert("google_place_id", *google_place_id);
	if (google_place_type.has_value())	venueJsonObject.insert("google_place_type", *google_place_type);

	return venueJsonObject;
}

bool Telegram::Venue::isEmpty() const
{
	return location.isEmpty()
		   and title == ""
		   and address == ""
		   and foursquare_id == std::nullopt
		   and foursquare_type == std::nullopt
		   and google_place_id == std::nullopt
		   and google_place_type == std::nullopt;
}
