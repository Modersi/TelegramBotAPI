#include "Types/InputMediaAudio.h"
#include "Internal/ConversionFunctions.h"

#include "qjsonobject.h"
#include "qjsonarray.h"

Telegram::InputMediaAudio::InputMediaAudio() :
	media(nullptr),
	thumb(std::nullopt),
	caption(std::nullopt),
	parse_mode(std::nullopt),
	caption_entities(std::nullopt),
	duration(std::nullopt),
	performer(std::nullopt),
	title(std::nullopt)
{}

Telegram::InputMediaAudio::InputMediaAudio(const std::variant<QFile*, QString>& media,
										   const std::optional<std::variant<QFile*, QString>>& thumb,
										   const std::optional<QString>& caption,
										   const std::optional<QString>& parse_mode,
										   const std::optional<QVector<MessageEntity>>& caption_entities,
										   const std::optional<qint32>& duration,
										   const std::optional<QString>& performer,
										   const std::optional<QString>& title) :
	media(media),
	thumb(thumb),
	caption(caption),
	parse_mode(parse_mode),
	caption_entities(caption_entities),
	duration(duration),
	performer(performer),
	title(title)
{}

Telegram::InputMediaAudio::InputMediaAudio(const QJsonObject& jsonObject)
{
	jsonObject.contains("media")			? media = jsonObject["media"].toString()														  : media = nullptr;
	jsonObject.contains("thumb")			? thumb = jsonObject["thumb"].toString()														  : thumb = std::nullopt;
	jsonObject.contains("caption")			? caption = jsonObject["caption"].toString()													  : caption = std::nullopt;
	jsonObject.contains("parse_mode")		? parse_mode = jsonObject["parse_mode"].toString()												  : parse_mode = std::nullopt;
	jsonObject.contains("caption_entities") ? caption_entities = QJsonArrayToQVector<MessageEntity>(jsonObject["caption_entities"].toArray()) : caption_entities = std::nullopt;
	jsonObject.contains("duration")			? duration = jsonObject["duration"].toInt()														  : duration = std::nullopt;
	jsonObject.contains("performer")		? performer = jsonObject["performer"].toString()												  : performer = std::nullopt;
	jsonObject.contains("title")			? title = jsonObject["title"].toString()														  : title = std::nullopt;
}

QJsonObject Telegram::InputMediaAudio::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	QJsonObject inputMediaAudioJsonObject{ {"type", type} };

	if (std::holds_alternative<QFile*>(media))  inputMediaAudioJsonObject.insert("media", QString("attach://%1").arg(std::get<QFile*>(media)->fileName()));
	if (std::holds_alternative<QString>(media)) inputMediaAudioJsonObject.insert("media", std::get<QString>(media));

	if (thumb.has_value())
	{
		if (std::holds_alternative<QFile*>(*thumb))  inputMediaAudioJsonObject.insert("thumb", QString("attach://%1").arg(std::get<QFile*>(*thumb)->fileName()));
		if (std::holds_alternative<QString>(*thumb)) inputMediaAudioJsonObject.insert("thumb", std::get<QString>(*thumb));
	}
	
	if (caption.has_value())			inputMediaAudioJsonObject.insert("caption", *caption);
	if (parse_mode.has_value())			inputMediaAudioJsonObject.insert("parse_mode", *parse_mode);
	if (caption_entities.has_value())	inputMediaAudioJsonObject.insert("caption_entities", QVectorToQJsonArray(*caption_entities));
	if (duration.has_value())			inputMediaAudioJsonObject.insert("duration", *duration);
	if (performer.has_value())			inputMediaAudioJsonObject.insert("performer", *performer);
	if (title.has_value())				inputMediaAudioJsonObject.insert("title", *title);

	return inputMediaAudioJsonObject;
}

bool Telegram::InputMediaAudio::isEmpty() const
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
		   and duration == std::nullopt
		   and performer == std::nullopt
		   and title == std::nullopt;
}


