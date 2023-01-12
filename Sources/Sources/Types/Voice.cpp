#include "Types/Voice.h"

Telegram::Voice::Voice() :
	file_id(),
	file_unique_id(),
	duration(),
	mime_type(),
	file_size()
{}

Telegram::Voice::Voice(const QString& file_id,
					   const QString& file_unique_id,
					   const qint32& duration,
					   const std::optional<QString>& mime_type,
					   const std::optional<qint32>& file_size) :
	file_id(file_id),
	file_unique_id(file_unique_id),
	duration(duration),
	mime_type(mime_type),
	file_size(file_size)
{}

Telegram::Voice::Voice(const QJsonObject& json_object) {
	json_object.contains("file_id")			? file_id = json_object["file_id"].toString()				 : file_id = "";
	json_object.contains("file_unique_id")	? file_unique_id = json_object["file_unique_id"].toString()  : file_unique_id = "";
	json_object.contains("duration")		? duration = json_object["duration"].toInt()				 : duration = 0;
	json_object.contains("mime_type")		? mime_type = json_object["mime_type"].toString()			 : mime_type = std::nullopt;
	json_object.contains("file_size")		? file_size = json_object["file_size"].toInt()				 : file_size = std::nullopt;
}

QJsonObject Telegram::Voice::toObject() const {
	if (isEmpty()) return {};

	QJsonObject voice_json_object{ {"file_id", file_id}, {"file_unique_id", file_unique_id}, {"duration", duration} };

	if (mime_type.has_value())	voice_json_object.insert("mime_type", *mime_type);
	if (file_size.has_value())	voice_json_object.insert("file_size", *file_size);

	return voice_json_object;
}

bool Telegram::Voice::isEmpty() const {
	return file_id == ""
		   and file_unique_id == ""
		   and duration == 0
		   and mime_type == std::nullopt
		   and file_size == std::nullopt;
}
