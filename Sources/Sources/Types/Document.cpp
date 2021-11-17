#include "Types/Document.h"

#include "qjsonobject.h"

Telegram::Document::Document() : 
	file_id(),
	file_unique_id(),
	thumb(),
	file_name(),
	mime_type(),
	file_size()
{}

Telegram::Document::Document(const QString& file_id,
							 const QString& file_unique_id,
							 const std::optional<PhotoSize>& thumb,
							 const std::optional<QString>& file_name,
							 const std::optional<QString>& mime_type,
							 const std::optional<qint32>& file_size) :
	file_id(file_id),
	file_unique_id(file_unique_id),
	thumb(thumb),
	file_name(file_name),
	mime_type(mime_type),
	file_size(file_size)
{}


Telegram::Document::Document(const QJsonObject& jsonObject)
{
	jsonObject.contains("file_id")		  ? file_id = jsonObject["file_id"].toString()				 : file_id = "";
	jsonObject.contains("file_unique_id") ? file_unique_id = jsonObject["file_unique_id"].toString() : file_unique_id = "";
	jsonObject.contains("thumb")		  ? thumb = PhotoSize(jsonObject["thumb"].toObject())		 : thumb = std::nullopt;
	jsonObject.contains("file_name")	  ? file_name = jsonObject["file_name"].toString()			 : file_name = std::nullopt;
	jsonObject.contains("mime_type")	  ? mime_type = jsonObject["mime_type"].toString()			 : mime_type = std::nullopt;
	jsonObject.contains("file_size")	  ? file_size = jsonObject["file_size"].toInt()				 : file_size = std::nullopt;
}

QJsonObject Telegram::Document::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	QJsonObject documentJsonObject{ {"file_id", file_id}, {"file_unique_id", file_unique_id} };

	if (thumb.has_value())		documentJsonObject.insert("thumb", thumb->toObject());
	if (file_name.has_value())	documentJsonObject.insert("file_name", *file_name);
	if (mime_type.has_value())	documentJsonObject.insert("mime_type", *mime_type);
	if (file_size.has_value())	documentJsonObject.insert("file_size", *file_size);

	return documentJsonObject;
}

bool Telegram::Document::isEmpty() const
{
	return file_id == ""
		   and file_unique_id == ""
		   and thumb == std::nullopt
		   and file_name == std::nullopt
		   and mime_type == std::nullopt
		   and file_size == std::nullopt;
}
