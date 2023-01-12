#include "Types/VideoNote.h"

Telegram::VideoNote::VideoNote() :
	file_id(),
	file_unique_id(),
	length(),
	duration(),
	thumb(),
	file_size()
{}

Telegram::VideoNote::VideoNote(const QString& file_id,
							   const QString& file_unique_id,
							   const qint32& length,
							   const qint32& duration,
							   const std::optional<PhotoSize>& thumb,
							   const std::optional<qint32>& file_size) :
	file_id(file_id),
	file_unique_id(file_unique_id),
	length(length),
	duration(duration),
	thumb(thumb),
	file_size(file_size)
{}

Telegram::VideoNote::VideoNote(const QJsonObject& json_object) {
	json_object.contains("file_id")		   ? file_id = json_object["file_id"].toString()				 : file_id = "";
	json_object.contains("file_unique_id") ? file_unique_id = json_object["file_unique_id"].toString()   : file_unique_id = "";
	json_object.contains("length")		   ? length = json_object["length"].toInt()						 : length = 0;
	json_object.contains("duration")	   ? duration = json_object["duration"].toInt()					 : duration = 0;
	json_object.contains("thumb")		   ? thumb = json_object["thumb"].toObject()					 : thumb = std::nullopt;
	json_object.contains("file_size")	   ? file_size = json_object["file_size"].toInt()				 : file_size = std::nullopt;
}

QJsonObject Telegram::VideoNote::toObject() const {
	if (isEmpty()) return {};

	QJsonObject video_note_json_object{ {"file_id", file_id}, {"file_unique_id", file_unique_id}, {"length", length}, {"duration", duration} };

	if (thumb.has_value())		video_note_json_object.insert("thumb", thumb->toObject());
	if (file_size.has_value())	video_note_json_object.insert("file_size", *file_size);

	return video_note_json_object;
}

bool Telegram::VideoNote::isEmpty() const {
	return file_id == ""
		   and file_unique_id == ""
		   and length == 0
		   and duration == 0
		   and thumb == std::nullopt
		   and file_size == std::nullopt;
}
