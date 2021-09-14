#include "Types/VideoNote.h"

#include "qjsonobject.h"

Telegram::VideoNote::VideoNote() :
	file_id(""),
	file_unique_id(""),
	length(0),
	duration(0),
	thumb(std::nullopt),
	file_size(std::nullopt)
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

Telegram::VideoNote::VideoNote(const QJsonObject& jsonObject)
{
	jsonObject.contains("file_id")		  ? file_id = jsonObject["file_id"].toString()				 : file_id = "";
	jsonObject.contains("file_unique_id") ? file_unique_id = jsonObject["file_unique_id"].toString() : file_unique_id = "";
	jsonObject.contains("length")		  ? length = jsonObject["length"].toInt()					 : length = 0;
	jsonObject.contains("duration")		  ? duration = jsonObject["duration"].toInt()				 : duration = 0;
	jsonObject.contains("thumb")		  ? thumb = jsonObject["thumb"].toObject()					 : thumb = std::nullopt;
	jsonObject.contains("file_size")	  ? file_size = jsonObject["file_size"].toInt()				 : file_size = std::nullopt;
}

QJsonObject Telegram::VideoNote::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	QJsonObject videoNoteJsonObject{ {"file_id", file_id}, {"file_unique_id", file_unique_id}, {"length", length}, {"duration", duration} };

	if (thumb.has_value())		videoNoteJsonObject.insert("thumb", thumb->toObject());
	if (file_size.has_value())	videoNoteJsonObject.insert("file_size", *file_size);

	return videoNoteJsonObject;
}

bool Telegram::VideoNote::isEmpty() const
{
	return file_id == ""
		   and file_unique_id == ""
		   and length == 0
		   and duration == 0
		   and thumb == std::nullopt
		   and file_size == std::nullopt;
}
