#include "Types/InlineQueryResultContact.h"

Telegram::InlineQueryResultContact::InlineQueryResultContact() :
	id(),
	phone_number(),
	first_name(),
	last_name(),
	vcard(),
	reply_markup(),
	input_message_content(),
	thumb_url(),
	thumb_width(),
	thumb_height()
{}

Telegram::InlineQueryResultContact::InlineQueryResultContact(const QString& id,
															 const QString& phone_number,
															 const QString& first_name,
															 const std::optional<QString>& last_name,
															 const std::optional<QString>& vcard,
															 const std::optional<InlineKeyboardMarkup>& reply_markup,
															 const std::optional<std::shared_ptr<InputMessageContent>>& input_message_content,
															 const std::optional<QString>& thumb_url,
															 const std::optional<qint32>& thumb_width, 
															 const std::optional<qint32>& thumb_height) :
	id(id),
	phone_number(phone_number),
	first_name(first_name),
	last_name(last_name),
	vcard(vcard),
	reply_markup(reply_markup),
	input_message_content(input_message_content),
	thumb_url(thumb_url),
	thumb_width(thumb_width),
	thumb_height(thumb_height)
{}

QJsonObject Telegram::InlineQueryResultContact::toObject() const {
	if (isEmpty()) return {};

	QJsonObject inline_query_result_contact_json_object{ {"type", QString(QMetaEnum::fromType<decltype(type)>().valueToKey(static_cast<int>(type))).toLower()}, {"id", id}, {"phone_number", phone_number}, {"first_name", first_name} };

	if (last_name.has_value())				inline_query_result_contact_json_object.insert("last_name", *last_name);
	if (vcard.has_value())					inline_query_result_contact_json_object.insert("vcard", *vcard);
	if (reply_markup.has_value())			inline_query_result_contact_json_object.insert("reply_markup", reply_markup->toObject());
	if (input_message_content.has_value())	inline_query_result_contact_json_object.insert("input_message_content", (**input_message_content).toObject());
	if (thumb_url.has_value())				inline_query_result_contact_json_object.insert("thumb_url", *thumb_url);
	if (thumb_width.has_value())			inline_query_result_contact_json_object.insert("thumb_width", *thumb_width);
	if (thumb_height.has_value())			inline_query_result_contact_json_object.insert("thumb_height", *thumb_height);

	return inline_query_result_contact_json_object;
}

bool Telegram::InlineQueryResultContact::isEmpty() const {
	return id == ""
		   and phone_number == ""
		   and first_name == ""
		   and last_name == std::nullopt
		   and vcard == std::nullopt
		   and reply_markup == std::nullopt
		   and input_message_content == std::nullopt
		   and thumb_url == std::nullopt
		   and thumb_width == std::nullopt
		   and thumb_height == std::nullopt;
}

Telegram::InlineQueryResult::Type Telegram::InlineQueryResultContact::getType() const {
	return type;
}
