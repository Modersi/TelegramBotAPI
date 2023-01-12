#include "Types/File.h"

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

Telegram::File::File(const QJsonObject& json_object) {
	json_object.contains("file_id")		   ? file_id = json_object["file_id"].toString()				 : file_id = "";
	json_object.contains("file_unique_id") ? file_unique_id = json_object["file_unique_id"].toString()   : file_unique_id = "";
	json_object.contains("file_size")	   ? file_size = json_object["file_size"].toInt()				 : file_size = std::nullopt;
	json_object.contains("file_path")      ? file_path = json_object["file_path"].toString()			 : file_path = std::nullopt;
}

QJsonObject Telegram::File::toObject() const {
	if (isEmpty()) return {};

	QJsonObject file_json_object{ {"file_id", file_id}, {"file_unique_id", file_unique_id} };

	if (file_size.has_value())	file_json_object.insert("file_size", *file_size);
	if (file_path.has_value())	file_json_object.insert("file_path", *file_path);

	return file_json_object;
}

bool Telegram::File::isEmpty() const {
	return file_id == ""
		   and file_unique_id == ""
		   and file_size == std::nullopt
		   and file_path == std::nullopt;
}
