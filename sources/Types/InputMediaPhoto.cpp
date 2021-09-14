#include "Types/InputMediaPhoto.h"
#include "Internal/ConversionFunctions.h"

#include "qjsonobject.h"
#include "qjsonarray.h"

Telegram::InputMediaPhoto::InputMediaPhoto() :
	media(nullptr),
	caption(std::nullopt),
	parse_mode(std::nullopt),
	caption_entities(std::nullopt)
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

Telegram::InputMediaPhoto::InputMediaPhoto(const QJsonObject& jsonObject)
{
	jsonObject.contains("media")			? media = jsonObject["media"].toString()															: media = nullptr;
	jsonObject.contains("caption")			? caption = jsonObject["caption"].toString()														: caption = std::nullopt;
	jsonObject.contains("parse_mode")		? parse_mode = jsonObject["parse_mode"].toString()													: parse_mode = std::nullopt;
	jsonObject.contains("caption_entities")	? caption_entities = QJsonArrayToQVector<MessageEntity>(jsonObject["caption_entities"].toArray())   : caption_entities = std::nullopt;
}

QJsonObject Telegram::InputMediaPhoto::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	QJsonObject inputMediaPhotoJsonObject{ {"type", type} };

	if (std::holds_alternative<QFile*>(media))  inputMediaPhotoJsonObject.insert("media", QString("attach://%1").arg(std::get<QFile*>(media)->fileName()));
	if (std::holds_alternative<QString>(media)) inputMediaPhotoJsonObject.insert("media", std::get<QString>(media));

	if (caption.has_value())			inputMediaPhotoJsonObject.insert("caption", *caption);
	if (parse_mode.has_value())			inputMediaPhotoJsonObject.insert("parse_mode", *parse_mode);
	if (caption_entities.has_value())	inputMediaPhotoJsonObject.insert("caption_entities", QVectorToQJsonArray(*caption_entities));

	return inputMediaPhotoJsonObject;
}

bool Telegram::InputMediaPhoto::isEmpty() const
{
	/* Check if std::variant<QFile*, QString> media contains any value */
	bool holdsMedia(false);
	if (std::holds_alternative<QFile*>(media))
		if (std::get<QFile*>(media) != nullptr) holdsMedia = true;

	if (std::holds_alternative<QString>(media))
		if (std::get<QString>(media) != "") holdsMedia = true;

	return holdsMedia == false
		   and caption == std::nullopt
		   and parse_mode == std::nullopt
		   and caption_entities == std::nullopt;
}
