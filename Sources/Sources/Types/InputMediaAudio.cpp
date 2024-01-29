#include "Types/InputMediaAudio.h"

#include "Internal/Utility/QJsonArrayInserter.h"
#include "Internal/Utility/QVectorInserter.h"

Telegram::InputMediaAudio::InputMediaAudio() :
	media(),
	thumb(),
	caption(),
	parse_mode(),
	caption_entities(),
	duration(),
	performer(),
	title()
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

Telegram::InputMediaAudio::InputMediaAudio(const QJsonObject& json_object) {
	json_object.contains("media")			 ? media = json_object["media"].toString()																		: media = nullptr;
	json_object.contains("thumb")			 ? thumb = json_object["thumb"].toString()																		: thumb = std::nullopt;
	json_object.contains("caption")			 ? caption = json_object["caption"].toString()																	: caption = std::nullopt;
	json_object.contains("parse_mode")		 ? parse_mode = json_object["parse_mode"].toString()															: parse_mode = std::nullopt;
	json_object.contains("caption_entities") ? caption_entities = Utility::QVectorInserter<MessageEntity>::make(json_object["caption_entities"].toArray())	: caption_entities = std::nullopt;
	json_object.contains("duration")		 ? duration = json_object["duration"].toInt()																	: duration = std::nullopt;
	json_object.contains("performer")		 ? performer = json_object["performer"].toString()																: performer = std::nullopt;
	json_object.contains("title")			 ? title = json_object["title"].toString()																		: title = std::nullopt;
}

QJsonObject Telegram::InputMediaAudio::toObject() const {
	if (isEmpty()) return {};

	QJsonObject input_media_audio_json_object{ {"type", QString(QMetaEnum::fromType<decltype(type)>().valueToKey(static_cast<int>(type))).toLower()} };

	if (std::holds_alternative<QFile*>(media))  input_media_audio_json_object.insert("media", QString("attach://%1").arg(std::get<QFile*>(media)->fileName()));
	if (std::holds_alternative<QString>(media)) input_media_audio_json_object.insert("media", std::get<QString>(media));

	if (thumb.has_value())
	{
		if (std::holds_alternative<QFile*>(*thumb))  input_media_audio_json_object.insert("thumb", QString("attach://%1").arg(std::get<QFile*>(*thumb)->fileName()));
		if (std::holds_alternative<QString>(*thumb)) input_media_audio_json_object.insert("thumb", std::get<QString>(*thumb));
	}
	
	if (caption.has_value())			input_media_audio_json_object.insert("caption", *caption);
	if (parse_mode.has_value())			input_media_audio_json_object.insert("parse_mode", *parse_mode);
	if (caption_entities.has_value())	input_media_audio_json_object.insert("caption_entities", Utility::QJsonArrayInserter::make(*caption_entities));
	if (duration.has_value())			input_media_audio_json_object.insert("duration", *duration);
	if (performer.has_value())			input_media_audio_json_object.insert("performer", *performer);
	if (title.has_value())				input_media_audio_json_object.insert("title", *title);

	return input_media_audio_json_object;
}

bool Telegram::InputMediaAudio::isEmpty() const {
	bool contains_media(false);
	if (std::holds_alternative<QFile*>(media))
		if (std::get<QFile*>(media) != nullptr) contains_media = true;

	if (std::holds_alternative<QString>(media))
		if (std::get<QString>(media) != "") contains_media = true;

	return contains_media == false
		   and thumb == std::nullopt
		   and caption == std::nullopt
		   and parse_mode == std::nullopt
		   and caption_entities == std::nullopt
		   and duration == std::nullopt
		   and performer == std::nullopt
		   and title == std::nullopt;
}

Telegram::InputMedia::Type Telegram::InputMediaAudio::getType() const {
	return type;
}


