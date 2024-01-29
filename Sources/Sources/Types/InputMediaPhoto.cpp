#include "Types/InputMediaPhoto.h"

#include "Internal/Utility/QJsonArrayInserter.h"
#include "Internal/Utility/QVectorInserter.h"

Telegram::InputMediaPhoto::InputMediaPhoto() :
	media(),
	caption(),
	parse_mode(),
	caption_entities()
{}

Telegram::InputMediaPhoto::InputMediaPhoto(const std::variant<QFile*, QString>& media,
										   const std::optional<QString>& caption,
										   const std::optional<QString>& parse_mode,
										   const std::optional<QVector<MessageEntity>>& caption_entities) :
	media(media),
	caption(caption),
	parse_mode(parse_mode),
	caption_entities(caption_entities)
{}

Telegram::InputMediaPhoto::InputMediaPhoto(const QJsonObject& json_object) {
	json_object.contains("media")				? media = json_object["media"].toString()																		: media = nullptr;
	json_object.contains("caption")				? caption = json_object["caption"].toString()																	: caption = std::nullopt;
	json_object.contains("parse_mode")			? parse_mode = json_object["parse_mode"].toString()																: parse_mode = std::nullopt;
	json_object.contains("caption_entities")	? caption_entities = Utility::QVectorInserter<MessageEntity>::make(json_object["caption_entities"].toArray())   : caption_entities = std::nullopt;
}

QJsonObject Telegram::InputMediaPhoto::toObject() const {
	if (isEmpty()) return {};

	QJsonObject input_media_photo_json_object{ {"type", QString(QMetaEnum::fromType<decltype(type)>().valueToKey(static_cast<int>(type))).toLower()} };

	if (std::holds_alternative<QFile*>(media))  input_media_photo_json_object.insert("media", QString("attach://%1").arg(std::get<QFile*>(media)->fileName()));
	if (std::holds_alternative<QString>(media)) input_media_photo_json_object.insert("media", std::get<QString>(media));

	if (caption.has_value())			input_media_photo_json_object.insert("caption", *caption);
	if (parse_mode.has_value())			input_media_photo_json_object.insert("parse_mode", *parse_mode);
	if (caption_entities.has_value())	input_media_photo_json_object.insert("caption_entities", Utility::QJsonArrayInserter::make(*caption_entities));

	return input_media_photo_json_object;
}

bool Telegram::InputMediaPhoto::isEmpty() const {
	bool contains_media(false);
	if (std::holds_alternative<QFile*>(media))
		if (std::get<QFile*>(media) != nullptr) contains_media = true;

	if (std::holds_alternative<QString>(media))
		if (std::get<QString>(media) != "") contains_media = true;

	return contains_media == false
		   and caption == std::nullopt
		   and parse_mode == std::nullopt
		   and caption_entities == std::nullopt;
}

Telegram::InputMedia::Type Telegram::InputMediaPhoto::getType() const {
	return type;
}
