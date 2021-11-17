#include "Types/Audio.h"

#include "qjsonobject.h"

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

Telegram::Audio::Audio(const QJsonObject& jsonObject)
{
	jsonObject.contains("file_id")        ? file_id = jsonObject["file_id"].toString()                : file_id = "";
	jsonObject.contains("file_unique_id") ? file_unique_id = jsonObject["file_unique_id"].toString()  : file_unique_id = "";
	jsonObject.contains("duration")       ? duration = jsonObject["duration"].toInt()                 : duration = 0;
	jsonObject.contains("performer")      ? performer = jsonObject["performer"].toString()            : performer = std::nullopt;
	jsonObject.contains("title")          ? title = jsonObject["title"].toString()                    : title = std::nullopt;
	jsonObject.contains("file_name")      ? file_name = jsonObject["file_name"].toString()            : file_name = std::nullopt;
	jsonObject.contains("mime_type")      ? mime_type = jsonObject["mime_type"].toString()            : mime_type = std::nullopt;
	jsonObject.contains("file_size")      ? file_size =jsonObject["file_size"].toInt()                : file_size = std::nullopt;
	jsonObject.contains("thumb")          ? thumb = PhotoSize(jsonObject["thumb"].toObject())         : thumb = std::nullopt;
}

QJsonObject Telegram::Audio::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	QJsonObject audioJsonObject{ {"file_id", file_id}, {"file_unique_id", file_unique_id}, {"duration", duration} };

	if (performer.has_value())	audioJsonObject.insert("performer", *performer);
	if (title.has_value())		audioJsonObject.insert("title", *title);
	if (file_name.has_value())	audioJsonObject.insert("file_name", *file_name);
	if (mime_type.has_value())	audioJsonObject.insert("mime_type", *mime_type);
	if (file_size.has_value())	audioJsonObject.insert("file_size", *file_size);
	if (thumb.has_value())		audioJsonObject.insert("thumb", thumb->toObject());

	return audioJsonObject;
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
