#include "Types/Audio.h"

Telegram::Audio::Audio() :
	file_id(),
	file_unique_id(),
	duration(),
	performer(),
	title(),
	file_name(),
	mime_type(),
	file_size(),
	thumb()
{}

Telegram::Audio::Audio(const QString& file_id,
					   const QString& file_unique_id,
					   const qint32& duration,
					   const std::optional<QString>& performer,
					   const std::optional<QString>& title,
					   const std::optional<QString>& file_name,
					   const std::optional<QString>& mime_type,
					   const std::optional<qint32>& file_size,
					   const std::optional<PhotoSize>& thumb) : 
	file_id(file_id),
	file_unique_id(file_unique_id),
	duration(duration),
	performer(performer),
	title(title),
	file_name(file_name),
	mime_type(mime_type),
	file_size(file_size),
	thumb(thumb)
{
}

Telegram::Audio::Audio(const QJsonObject& json_object) {
	json_object.contains("file_id")        ? file_id = json_object["file_id"].toString()                : file_id = "";
	json_object.contains("file_unique_id") ? file_unique_id = json_object["file_unique_id"].toString()  : file_unique_id = "";
	json_object.contains("duration")       ? duration = json_object["duration"].toInt()                 : duration = 0;
	json_object.contains("performer")      ? performer = json_object["performer"].toString()            : performer = std::nullopt;
	json_object.contains("title")          ? title = json_object["title"].toString()                    : title = std::nullopt;
	json_object.contains("file_name")      ? file_name = json_object["file_name"].toString()            : file_name = std::nullopt;
	json_object.contains("mime_type")      ? mime_type = json_object["mime_type"].toString()            : mime_type = std::nullopt;
	json_object.contains("file_size")      ? file_size =json_object["file_size"].toInt()                : file_size = std::nullopt;
	json_object.contains("thumb")          ? thumb = PhotoSize(json_object["thumb"].toObject())         : thumb = std::nullopt;
}

QJsonObject Telegram::Audio::toObject() const {
	if (isEmpty()) return {};

	QJsonObject audio_json_object{ {"file_id", file_id}, {"file_unique_id", file_unique_id}, {"duration", duration} };
	if (performer.has_value())	audio_json_object.insert("performer", *performer);
	if (title.has_value())		audio_json_object.insert("title", *title);
	if (file_name.has_value())	audio_json_object.insert("file_name", *file_name);
	if (mime_type.has_value())	audio_json_object.insert("mime_type", *mime_type);
	if (file_size.has_value())	audio_json_object.insert("file_size", *file_size);
	if (thumb.has_value())		audio_json_object.insert("thumb", thumb->toObject());

	return audio_json_object;
}

bool Telegram::Audio::isEmpty() const
{
	return file_id == ""
		   and file_unique_id == ""
		   and duration == 0
		   and performer == std::nullopt
		   and title == std::nullopt
		   and file_name == std::nullopt
		   and mime_type == std::nullopt
		   and file_size == std::nullopt
		   and thumb == std::nullopt;
}
