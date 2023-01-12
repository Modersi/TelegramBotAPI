#include "Types/PhotoSize.h"

#include "qjsonobject.h"

Telegram::PhotoSize::PhotoSize() :
	file_id(),
	file_unique_id(),
	width(),
	height(),
	file_size()
{}

Telegram::PhotoSize::PhotoSize(const QString& file_id,
							   const QString& file_unique_id,
							   const qint32& width,
							   const qint32& height,
							   const std::optional<qint32>& file_size) :
	file_id(file_id),
	file_unique_id(file_unique_id),
	width(width),
	height(height),
	file_size(file_size)
{
}

Telegram::PhotoSize::PhotoSize(const QJsonObject& json_object) {
	json_object.contains("file_id")			? file_id = json_object["file_id"].toString()				: file_id = "";
	json_object.contains("file_unique_id")	? file_unique_id = json_object["file_unique_id"].toString() : file_unique_id = "";
	json_object.contains("width")			? width = json_object["width"].toInt()						: width = 0;
	json_object.contains("height")			? height = json_object["height"].toInt()					: height = 0;
	json_object.contains("file_size")		? file_size = json_object["file_size"].toInt()				: file_size = std::nullopt;
}

QJsonObject Telegram::PhotoSize::toObject() const {
	if (isEmpty()) return {};

	QJsonObject photo_size_json_object{ {"file_id", file_id}, {"file_unique_id", file_unique_id}, {"width", width}, {"height", height}, };

	if (file_size.has_value())	photo_size_json_object.insert("file_size", *file_size);

	return photo_size_json_object;
}

bool Telegram::PhotoSize::isEmpty() const {
	return file_id == ""
		   and file_unique_id == ""
		   and width == 0
		   and height == 0
		   and file_size == std::nullopt;
}
