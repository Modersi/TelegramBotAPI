#include "Types/InlineQueryResultVenue.h"

Telegram::InlineQueryResultVenue::InlineQueryResultVenue() :
	id(),
	latitude(),
	longitude(),
	title(),
	address(),
	foursquare_id(),
	foursquare_type(),
	google_place_id(),
	google_place_type(),
	reply_markup(),
	input_message_content(),
	thumb_url(),
	thumb_width(),
	thumb_height()
{}

Telegram::InlineQueryResultVenue::InlineQueryResultVenue(const QString& id,
														 const float& latitude,
														 const float& longitude,
														 const QString& title,
														 const QString& address,
														 const std::optional<QString>& foursquare_id,
														 const std::optional<QString>& foursquare_type,
														 const std::optional<QString>& google_place_id,
														 const std::optional<QString>& google_place_type,
														 const std::optional<InlineKeyboardMarkup>& reply_markup,
														 const std::optional<std::shared_ptr<InputMessageContent>>& input_message_content,
														 const std::optional<QString>& thumb_url,
														 const std::optional<qint32>& thumb_width,
														 const std::optional<qint32>& thumb_height) :
	id(id),
	latitude(latitude),
	longitude(longitude),
	title(title),
	address(address),
	foursquare_id(foursquare_id),
	foursquare_type(foursquare_type),
	google_place_id(google_place_id),
	google_place_type(google_place_type),
	reply_markup(reply_markup),
	input_message_content(input_message_content),
	thumb_url(thumb_url),
	thumb_width(thumb_width),
	thumb_height(thumb_height)
{}

QJsonObject Telegram::InlineQueryResultVenue::toObject() const {
	if (isEmpty()) return {};

	QJsonObject inline_query_result_venue_json_object{ {"type", QString(QMetaEnum::fromType<decltype(type)>().valueToKey(static_cast<int>(type))).toLower()}, {"id", id}, {"latitude", latitude}, {"longitude", longitude}, {"title", title} , { "address", address } };

	if (foursquare_id.has_value())			inline_query_result_venue_json_object.insert("foursquare_id", *foursquare_id);
	if (foursquare_type.has_value())		inline_query_result_venue_json_object.insert("foursquare_type", *foursquare_type);
	if (google_place_id.has_value())		inline_query_result_venue_json_object.insert("google_place_id", *google_place_id);
	if (google_place_type.has_value())		inline_query_result_venue_json_object.insert("google_place_type", *google_place_type);
	if (reply_markup.has_value())			inline_query_result_venue_json_object.insert("reply_markup", reply_markup->toObject());
	if (input_message_content.has_value())	inline_query_result_venue_json_object.insert("input_message_content", (**input_message_content).toObject());
	if (thumb_url.has_value())				inline_query_result_venue_json_object.insert("thumb_url", *thumb_url);
	if (thumb_width.has_value())			inline_query_result_venue_json_object.insert("thumb_width", *thumb_width);
	if (thumb_height.has_value())			inline_query_result_venue_json_object.insert("thumb_height", *thumb_height);

	return inline_query_result_venue_json_object;
}

bool Telegram::InlineQueryResultVenue::isEmpty() const {
	return id == ""
		   and latitude == 0.0
		   and longitude == 0.0
		   and title == ""
		   and address == ""
		   and foursquare_id == std::nullopt
		   and foursquare_type == std::nullopt
		   and google_place_id == std::nullopt
		   and google_place_type == std::nullopt
		   and reply_markup == std::nullopt
		   and input_message_content == std::nullopt
		   and thumb_url == std::nullopt
		   and thumb_width == std::nullopt
		   and thumb_height == std::nullopt;
}

Telegram::InlineQueryResult::Type Telegram::InlineQueryResultVenue::getType() const {
	return type;
}
