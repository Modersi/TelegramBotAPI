#include "Types/Sticker.h"

#include "qjsonobject.h"

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

Telegram::Sticker::Sticker(const QJsonObject& jsonObject)
{
	jsonObject.contains("file_id")			? file_id = jsonObject["file_id"].toString()							: file_id = "";
	jsonObject.contains("file_unique_id")	? file_unique_id = jsonObject["file_unique_id"].toString()				: file_unique_id = "";
	jsonObject.contains("width")			? width = jsonObject["width"].toInt()									: width = 0;
	jsonObject.contains("height")			? height = jsonObject["height"].toInt()									: height = 0;
	jsonObject.contains("is_animated")		? is_animated = jsonObject["is_animated"].toBool()						: is_animated = false;
	jsonObject.contains("thumb")			? thumb = PhotoSize(jsonObject["thumb"].toObject())						: thumb = std::nullopt;
	jsonObject.contains("emoji")			? emoji = jsonObject["emoji"].toString()								: emoji = std::nullopt;
	jsonObject.contains("set_name")			? set_name = jsonObject["set_name"].toString()							: set_name = std::nullopt;
	jsonObject.contains("mask_position")	? mask_position = MaskPosition(jsonObject["mask_position"].toObject())	: mask_position = std::nullopt;
	jsonObject.contains("file_size")		? file_size = jsonObject["file_size"].toInt()							: file_size = std::nullopt;
}

QJsonObject Telegram::Sticker::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	QJsonObject stickerJsonObject{ {"file_id", file_id}, {"file_unique_id", file_unique_id}, {"width", width}, {"height", height}, {"is_animated", is_animated} };

	if (thumb.has_value())			stickerJsonObject.insert("thumb", thumb->toObject());
	if (emoji.has_value())			stickerJsonObject.insert("emoji", *emoji);
	if (set_name.has_value())		stickerJsonObject.insert("set_name", *set_name);
	if (mask_position.has_value())	stickerJsonObject.insert("mask_position", mask_position->toObject());
	if (file_size.has_value())		stickerJsonObject.insert("file_size", *file_size);

	return stickerJsonObject;
}

bool Telegram::Sticker::isEmpty() const
{
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
