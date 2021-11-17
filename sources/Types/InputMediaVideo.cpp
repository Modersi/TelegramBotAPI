#include "Types/InputMediaVideo.h"

#include "qjsonobject.h"

#include "Internal/ConversionFunctions.h"

Telegram::InputMediaVideo::InputMediaVideo() :
	media(),
	thumb(),
	caption(),
	parse_mode(),
	caption_entities(),
	width(),
	height(),
	duration(),
	supports_streaming()
{}

Telegram::InputMediaVideo::InputMediaVideo(const std::variant<QFile*, QString>& media,
										   const std::optional<std::variant<QFile*, QString>>& thumb,
										   const std::optional<QString>& caption,
										   const std::optional<QString>& parse_mode,
										   const std::optional<QVector<MessageEntity>>& caption_entities,
										   const std::optional<qint32>& width,
										   const std::optional<qint32>& height,
										   const std::optional<qint32>& duration,
										   const std::optional<bool>& supports_streaming) :
	media(media),
	thumb(thumb),
	caption(caption),
	parse_mode(parse_mode),
	caption_entities(caption_entities),
	width(width),
	height(height),
	duration(duration),
	supports_streaming(supports_streaming)
{}

Telegram::InputMediaVideo::InputMediaVideo(const QJsonObject& jsonObject)
{
	jsonObject.contains("media")			  ? media = jsonObject["media"].toString()															: media = nullptr;
	jsonObject.contains("thumb")			  ? thumb = jsonObject["thumb"].toString()															: thumb = std::nullopt;
	jsonObject.contains("caption")			  ? caption = jsonObject["caption"].toString()														: caption = std::nullopt;
	jsonObject.contains("parse_mode")		  ? parse_mode = jsonObject["parse_mode"].toString()												: parse_mode = std::nullopt;									  																   
	jsonObject.contains("caption_entities")   ? caption_entities = QJsonArrayToQVector<MessageEntity>(jsonObject["caption_entities"].toArray()) : caption_entities = std::nullopt;
	jsonObject.contains("width")			  ? width = jsonObject["width"].toInt()																: width = std::nullopt;
	jsonObject.contains("height")			  ? height = jsonObject["height"].toInt()															: height = std::nullopt;
	jsonObject.contains("duration")			  ? duration = jsonObject["duration"].toInt()														: duration = std::nullopt;
	jsonObject.contains("supports_streaming") ? supports_streaming = jsonObject["supports_streaming"].toBool()									: supports_streaming = std::nullopt;
}

QJsonObject Telegram::InputMediaVideo::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	QJsonObject inputMediaVideoJsonObject{ {"type", type} };

	if (std::holds_alternative<QFile*>(media))  inputMediaVideoJsonObject.insert("media", QString("attach://%1").arg(std::get<QFile*>(media)->fileName()));
	if (std::holds_alternative<QString>(media)) inputMediaVideoJsonObject.insert("media", std::get<QString>(media));

	if (thumb.has_value())
	{
		if (std::holds_alternative<QFile*>(*thumb))  inputMediaVideoJsonObject.insert("thumb", QString("attach://%1").arg(std::get<QFile*>(*thumb)->fileName()));
		if (std::holds_alternative<QString>(*thumb)) inputMediaVideoJsonObject.insert("thumb", std::get<QString>(*thumb));
	}

	if (caption.has_value())			inputMediaVideoJsonObject.insert("caption", *caption);
	if (parse_mode.has_value())			inputMediaVideoJsonObject.insert("parse_mode", *parse_mode);
	if (caption_entities.has_value())	inputMediaVideoJsonObject.insert("caption_entities", QVectorToQJsonArray(*caption_entities));
	if (width.has_value())				inputMediaVideoJsonObject.insert("width", *width);
	if (height.has_value())				inputMediaVideoJsonObject.insert("height", *height);
	if (duration.has_value())			inputMediaVideoJsonObject.insert("duration", *duration);
	if (supports_streaming.has_value())	inputMediaVideoJsonObject.insert("supports_streaming", *supports_streaming);

	return inputMediaVideoJsonObject;
}

bool Telegram::InputMediaVideo::isEmpty() const
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
		   and width == std::nullopt
		   and height == std::nullopt
		   and duration == std::nullopt
		   and supports_streaming == std::nullopt;
}
