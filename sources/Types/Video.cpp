#include "Types/Video.h"

#include "qjsonobject.h"

Telegram::Video::Video() :
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

Telegram::Video::Video(const QString& file_id,
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

Telegram::Video::Video(const QJsonObject& jsonObject)
{
	jsonObject.contains("file_id")		  ? file_id = jsonObject["file_id"].toString()				 : file_id = "";
	jsonObject.contains("file_unique_id") ? file_unique_id = jsonObject["file_unique_id"].toString() : file_unique_id = "";
	jsonObject.contains("width")		  ? width = jsonObject["width"].toInt()						 : width = 0;
	jsonObject.contains("height")		  ? height = jsonObject["height"].toInt()					 : height = 0;
	jsonObject.contains("duration")		  ? duration = jsonObject["duration"].toInt()				 : duration = 0;
	jsonObject.contains("thumb")		  ? thumb = PhotoSize(jsonObject["thumb"].toObject())		 : thumb = std::nullopt;
	jsonObject.contains("file_name")	  ? file_name = jsonObject["file_name"].toString()			 : file_name = std::nullopt;
	jsonObject.contains("mime_type")	  ? mime_type = jsonObject["mime_type"].toString()			 : mime_type = std::nullopt;
	jsonObject.contains("file_size")	  ? file_size = jsonObject["file_size"].toInt()				 : file_size = std::nullopt;
}

QJsonObject Telegram::Video::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	QJsonObject videoJsonObject{ {"file_id", file_id}, {"file_unique_id", file_unique_id}, {"width", width}, {"height", height}, {"duration", duration} };

	if (thumb.has_value())		videoJsonObject.insert("thumb", thumb->toObject());
	if (file_name.has_value())	videoJsonObject.insert("file_name", *file_name);
	if (mime_type.has_value())	videoJsonObject.insert("mime_type", *mime_type);
	if (file_size.has_value())	videoJsonObject.insert("file_size", *file_size);

	return videoJsonObject;
}

bool Telegram::Video::isEmpty() const
{
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
