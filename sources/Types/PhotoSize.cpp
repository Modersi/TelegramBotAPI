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

Telegram::PhotoSize::PhotoSize(const QJsonObject& jsonObject)
{
	jsonObject.contains("file_id")		  ? file_id = jsonObject["file_id"].toString()				 : file_id = "";
	jsonObject.contains("file_unique_id") ? file_unique_id = jsonObject["file_unique_id"].toString() : file_unique_id = "";
	jsonObject.contains("width")		  ? width = jsonObject["width"].toInt()						 : width = 0;
	jsonObject.contains("height")		  ? height = jsonObject["height"].toInt()					 : height = 0;
	jsonObject.contains("file_size")	  ? file_size = jsonObject["file_size"].toInt()				 : file_size = std::nullopt;
}

QJsonObject Telegram::PhotoSize::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	QJsonObject photoSizeJsonObject{ {"file_id", file_id}, {"file_unique_id", file_unique_id}, {"width", width}, {"height", height}, };

	if (file_size.has_value())	photoSizeJsonObject.insert("file_size", *file_size);

	return photoSizeJsonObject;
}

bool Telegram::PhotoSize::isEmpty() const
{
	return file_id == ""
		   and file_unique_id == ""
		   and width == 0
		   and height == 0
		   and file_size == std::nullopt;
}
