#include "Types/Sticker.h"

Telegram::Sticker::Sticker() :
	file_id(),
	file_unique_id(),
	width(),
	height(),
	is_animated(),
	thumb(),
	emoji(),
	set_name(),
	mask_position(),
	file_size()
{}

Telegram::Sticker::Sticker(const QString& file_id,
						   const QString& file_unique_id,
						   const qint32& width,
						   const qint32& height,
						   const bool& is_animated,
						   const std::optional<PhotoSize>& thumb,
						   const std::optional<QString>& emoji,
						   const std::optional<QString>& set_name,
						   const std::optional<MaskPosition>& mask_position,
						   const std::optional<qint32>& file_size) :
	file_id(file_id),
	file_unique_id(file_unique_id),
	width(width),
	height(height),
	is_animated(is_animated),
	thumb(thumb),
	emoji(emoji),
	set_name(set_name),
	mask_position(mask_position),
	file_size(file_size)
{}

Telegram::Sticker::Sticker(const QJsonObject& json_object) {
	json_object.contains("file_id")			? file_id = json_object["file_id"].toString()							: file_id = "";
	json_object.contains("file_unique_id")	? file_unique_id = json_object["file_unique_id"].toString()				: file_unique_id = "";
	json_object.contains("width")			? width = json_object["width"].toInt()									: width = 0;
	json_object.contains("height")			? height = json_object["height"].toInt()								: height = 0;
	json_object.contains("is_animated")		? is_animated = json_object["is_animated"].toBool()						: is_animated = false;
	json_object.contains("thumb")			? thumb = PhotoSize(json_object["thumb"].toObject())					: thumb = std::nullopt;
	json_object.contains("emoji")			? emoji = json_object["emoji"].toString()								: emoji = std::nullopt;
	json_object.contains("set_name")		? set_name = json_object["set_name"].toString()							: set_name = std::nullopt;
	json_object.contains("mask_position")	? mask_position = MaskPosition(json_object["mask_position"].toObject())	: mask_position = std::nullopt;
	json_object.contains("file_size")		? file_size = json_object["file_size"].toInt()							: file_size = std::nullopt;
}

QJsonObject Telegram::Sticker::toObject() const {
	if (isEmpty()) return {};

	QJsonObject sticker_json_object{ {"file_id", file_id}, {"file_unique_id", file_unique_id}, {"width", width}, {"height", height}, {"is_animated", is_animated} };

	if (thumb.has_value())			sticker_json_object.insert("thumb", thumb->toObject());
	if (emoji.has_value())			sticker_json_object.insert("emoji", *emoji);
	if (set_name.has_value())		sticker_json_object.insert("set_name", *set_name);
	if (mask_position.has_value())	sticker_json_object.insert("mask_position", mask_position->toObject());
	if (file_size.has_value())		sticker_json_object.insert("file_size", *file_size);

	return sticker_json_object;
}

bool Telegram::Sticker::isEmpty() const {
	return file_id == ""
		   and file_unique_id == ""
		   and width == 0
		   and height == 0
		   and is_animated == false
		   and thumb == std::nullopt
		   and emoji == std::nullopt
		   and set_name == std::nullopt
		   and mask_position == std::nullopt
		   and file_size == std::nullopt;
}
