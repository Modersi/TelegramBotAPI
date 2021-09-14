#include "Types/Voice.h"

#include "qjsonobject.h"

Telegram::Voice::Voice() :
	file_id(""),
	file_unique_id(""),
	duration(0),
	mime_type(std::nullopt),
	file_size(std::nullopt)
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

Telegram::Voice::Voice(const QJsonObject& jsonObject)
{
	jsonObject.contains("file_id")		  ? file_id = jsonObject["file_id"].toString()				 : file_id = "";
	jsonObject.contains("file_unique_id") ? file_unique_id = jsonObject["file_unique_id"].toString() : file_unique_id = "";
	jsonObject.contains("duration")		  ? duration = jsonObject["duration"].toInt()				 : duration = 0;
	jsonObject.contains("mime_type")	  ? mime_type = jsonObject["mime_type"].toString()			 : mime_type = std::nullopt;
	jsonObject.contains("file_size")	  ? file_size = jsonObject["file_size"].toInt()				 : file_size = std::nullopt;
}

QJsonObject Telegram::Voice::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	QJsonObject videoJsonObject{ {"file_id", file_id}, {"file_unique_id", file_unique_id}, {"duration", duration} };

	if (mime_type.has_value())	videoJsonObject.insert("mime_type", *mime_type);
	if (file_size.has_value())	videoJsonObject.insert("file_size", *file_size);

	return videoJsonObject;
}

bool Telegram::Voice::isEmpty() const
{
	return file_id == ""
		   and file_unique_id == ""
		   and duration == 0
		   and mime_type == std::nullopt
		   and file_size == std::nullopt;
}
