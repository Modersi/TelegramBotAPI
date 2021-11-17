#include "Types/File.h"

#include "qjsonobject.h"

Telegram::File::File() :
	file_id(),
	file_unique_id(),
	file_size(),
	file_path()
{}

Telegram::File::File(const QString& file_id,
	                 const QString& file_unique_id,
	                 const std::optional<qint32>& file_size,
	                 const std::optional<QString>& file_path) :
	file_id(file_id),
	file_unique_id(file_unique_id),
	file_size(file_size),
	file_path(file_path)
{}

Telegram::File::File(const QJsonObject& jsonObject)
{
	jsonObject.contains("file_id")		  ? file_id = jsonObject["file_id"].toString()				 : file_id = "";
	jsonObject.contains("file_unique_id") ? file_unique_id = jsonObject["file_unique_id"].toString() : file_unique_id = "";
	jsonObject.contains("file_size")	  ? file_size = jsonObject["file_size"].toInt()				 : file_size = std::nullopt;
	jsonObject.contains("file_path")      ? file_path = jsonObject["file_path"].toString()			 : file_path = std::nullopt;
}

QJsonObject Telegram::File::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	QJsonObject fileJsonObject{ {"file_id", file_id}, {"file_unique_id", file_unique_id} };

	if (file_size.has_value())	fileJsonObject.insert("file_size", *file_size);
	if (file_path.has_value())	fileJsonObject.insert("file_path", *file_path);

	return fileJsonObject;
}

bool Telegram::File::isEmpty() const
{
	return file_id == ""
		   and file_unique_id == ""
		   and file_size == std::nullopt
		   and file_path == std::nullopt;
}
