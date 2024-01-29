#include "Types/StickerSet.h"

#include "Internal/Utility/QJsonArrayInserter.h"
#include "Internal/Utility/QVectorInserter.h"

Telegram::StickerSet::StickerSet() :
	name(),
	title(),
	is_animated(),
	contains_masks(),
	stickers(),
	thumb()
{}

Telegram::StickerSet::StickerSet(const QString& name,
								 const QString& title,
								 const bool& is_animated,
								 const bool& contains_masks,
								 const QVector<Sticker>& stickers,
								 const std::optional<PhotoSize>& thumb) :
	name(name),
	title(title),
	is_animated(is_animated),
	contains_masks(contains_masks),
	stickers(stickers),
	thumb(thumb)
{}

Telegram::StickerSet::StickerSet(const QJsonObject& json_object) {
	json_object.contains("name")			? name = json_object["name"].toString()											: name = "";
	json_object.contains("title")			? title = json_object["title"].toString()										: title = "";
	json_object.contains("is_animated")		? is_animated = json_object["is_animated"].toBool()								: is_animated = false;
	json_object.contains("contains_masks")	? contains_masks = json_object["contains_masks"].toBool()						: contains_masks = false;
	json_object.contains("stickers")		? stickers = Utility::QVectorInserter<Sticker>::make(json_object["stickers"].toArray())	: stickers = QVector<Sticker>();
	json_object.contains("thumb")			? thumb = PhotoSize(json_object["thumb"].toObject())							: thumb = std::nullopt;
}

QJsonObject Telegram::StickerSet::toObject() const {
	if (isEmpty()) return {};

	QJsonObject sticker_set_json_object{ {"name", name}, {"title", title}, {"is_animated", is_animated}, {"contains_masks", contains_masks}, {"stickers", Utility::QJsonArrayInserter::make(stickers)} };

	if (thumb.has_value()) sticker_set_json_object.insert("thumb", thumb->toObject());

	return sticker_set_json_object;
}

bool Telegram::StickerSet::isEmpty() const {
	return name == ""
		   and title == ""
		   and is_animated == false
		   and contains_masks == false
		   and stickers.isEmpty()
		   and thumb == std::nullopt;
}
