#include "Types/Animation.h"

Telegram::Animation::Animation() :
	file_id(),
	file_unique_id(),
	width(),
	height(),
	duration(),
	thumb(),
	file_name(),
	mime_type(),
	file_size() 
{}

Telegram::Animation::Animation(const QString& file_id,
							   const QString& file_unique_id,
							   const qint32& width,
							   const qint32& height,
							   const qint32& duration,
							   const std::optional<PhotoSize>& thumb,
							   const std::optional<QString>& file_name,
							   const std::optional<QString>& mime_type,
							   const std::optional<qint32>& file_size) :
	file_id(file_id),
	file_unique_id(file_unique_id),
	width(width),
	height(height),
	duration(duration),
	thumb(thumb),
	file_name(file_name),
	mime_type(mime_type),
	file_size(file_size) 
{}

Telegram::Animation::Animation(const QJsonObject &json_object) {
    json_object.contains("file_id")        ? file_id = json_object["file_id"].toString()                : file_id = "";
    json_object.contains("file_unique_id") ? file_unique_id = json_object["file_unique_id"].toString()  : file_unique_id = "";
    json_object.contains("width")          ? width = json_object["width"].toInt()                       : width = 0;
    json_object.contains("height")         ? height = json_object["height"].toInt()                     : height = 0;
    json_object.contains("duration")       ? duration = json_object["duration"].toInt()                 : duration = 0;
    json_object.contains("thumb")          ? thumb = PhotoSize(json_object["thumb"].toObject())         : thumb = std::nullopt;
    json_object.contains("file_name")      ? file_name = json_object["file_name"].toString()            : file_name = std::nullopt;
    json_object.contains("mime_type")      ? mime_type = json_object["mime_type"].toString()            : mime_type = std::nullopt;
    json_object.contains("file_size")      ? file_size =json_object["file_size"].toInt()                : file_size = std::nullopt;
}

QJsonObject Telegram::Animation::toObject() const {
	if (isEmpty()) return {};

	QJsonObject animation_json_object{ {"file_id", file_id}, {"file_unique_id", file_unique_id}, {"width", width}, {"height", height}, {"duration", duration} };
	if (thumb.has_value())		animation_json_object.insert("thumb", thumb->toObject());
	if (file_name.has_value())	animation_json_object.insert("file_name", *file_name);
	if (mime_type.has_value())	animation_json_object.insert("mime_type", *mime_type);
	if (file_size.has_value())	animation_json_object.insert("file_size", *file_size);

	return animation_json_object;
}

bool Telegram::Animation::isEmpty() const {
	return file_id == ""
		   and file_unique_id == ""
		   and width == 0
		   and height == 0
		   and duration == 0
		   and thumb == std::nullopt
		   and file_name == std::nullopt
		   and mime_type == std::nullopt
		   and file_size == std::nullopt;
}


