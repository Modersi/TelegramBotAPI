#include "Types/InputMediaDocument.h"
#include "Internal/ConversionFunctions.h"

#include "qjsonobject.h"
#include "qjsonarray.h"

Telegram::InputMediaDocument::InputMediaDocument() :
	media(nullptr),
	thumb(std::nullopt),
	caption(std::nullopt),
	parse_mode(std::nullopt),
	caption_entities(std::nullopt),
	disable_content_type_detection(std::nullopt)
{}

Telegram::InputMediaDocument::InputMediaDocument(const std::variant<QFile*, QString>& media,
												 const std::optional<std::variant<QFile*, QString>>& thumb,
												 const std::optional<QString>& caption,
												 const std::optional<QString>& parse_mode,
												 const std::optional<QVector<MessageEntity>>& caption_entities,
												 const std::optional<bool>& disable_content_type_detection) :
	media(media),
	thumb(thumb),
	caption(caption),
	parse_mode(parse_mode),
	caption_entities(caption_entities),
	disable_content_type_detection(disable_content_type_detection)
{}

Telegram::InputMediaDocument::InputMediaDocument(const QJsonObject& jsonObject)
{
	jsonObject.contains("media")						  ? media = jsonObject["media"].toString()															: media = nullptr;
	jsonObject.contains("thumb")						  ? thumb = jsonObject["thumb"].toString()															: thumb = std::nullopt;
	jsonObject.contains("caption")						  ? caption = jsonObject["caption"].toString()														: caption = std::nullopt;
	jsonObject.contains("parse_mode")					  ? parse_mode = jsonObject["parse_mode"].toString()												: parse_mode = std::nullopt;
	jsonObject.contains("caption_entities")				  ? caption_entities = QJsonArrayToQVector<MessageEntity>(jsonObject["caption_entities"].toArray()) : caption_entities = std::nullopt;
	jsonObject.contains("disable_content_type_detection") ? disable_content_type_detection = jsonObject["disable_content_type_detection"].toBool()			: disable_content_type_detection = std::nullopt;
}

QJsonObject Telegram::InputMediaDocument::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	QJsonObject inputMediaDocumentJsonObject{ {"type", type} };

	if (std::holds_alternative<QFile*>(media))  inputMediaDocumentJsonObject.insert("media", QString("attach://%1").arg(std::get<QFile*>(media)->fileName()));
	if (std::holds_alternative<QString>(media)) inputMediaDocumentJsonObject.insert("media", std::get<QString>(media));

	if (thumb.has_value())
	{
		if (std::holds_alternative<QFile*>(*thumb))  inputMediaDocumentJsonObject.insert("thumb", QString("attach://%1").arg(std::get<QFile*>(*thumb)->fileName()));
		if (std::holds_alternative<QString>(*thumb)) inputMediaDocumentJsonObject.insert("thumb", std::get<QString>(*thumb));
	}

	if (caption.has_value())							inputMediaDocumentJsonObject.insert("caption", *caption);
	if (parse_mode.has_value())							inputMediaDocumentJsonObject.insert("parse_mode", *parse_mode);
	if (caption_entities.has_value())					inputMediaDocumentJsonObject.insert("caption_entities", QVectorToQJsonArray(*caption_entities));
	if (disable_content_type_detection.has_value())		inputMediaDocumentJsonObject.insert("disable_content_type_detection", *disable_content_type_detection);

	return inputMediaDocumentJsonObject;
}

bool Telegram::InputMediaDocument::isEmpty() const
{
	/* Check if std::variant<QFile*, QString> media contains any value */
	bool holdsMedia(false);
	if (std::holds_alternative<QFile*>(media))
		if (std::get<QFile*>(media) != nullptr) holdsMedia = true;

	if (std::holds_alternative<QString>(media))
		if (std::get<QString>(media) != "") holdsMedia = true;

	return holdsMedia == false
		   and thumb == std::nullopt
		   and caption == std::nullopt
		   and parse_mode == std::nullopt
		   and caption_entities == std::nullopt
		   and disable_content_type_detection == std::nullopt;
}
