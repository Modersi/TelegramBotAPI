#include "Types/StickerSet.h"

#include "qjsonobject.h"

#include "Internal/ConversionFunctions.h"

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

Telegram::StickerSet::StickerSet(const QJsonObject& jsonObject)
{
	jsonObject.contains("name")			  ? name = jsonObject["name"].toString()									  : name = "";
	jsonObject.contains("title")		  ? title = jsonObject["title"].toString()									  : title = "";
	jsonObject.contains("is_animated")	  ? is_animated = jsonObject["is_animated"].toBool()						  : is_animated = false;
	jsonObject.contains("contains_masks") ? contains_masks = jsonObject["contains_masks"].toBool()					  : contains_masks = false;
	jsonObject.contains("stickers")		  ? stickers = QJsonArrayToQVector<Sticker>(jsonObject["stickers"].toArray()) : stickers = QVector<Sticker>();
	jsonObject.contains("thumb")		  ? thumb = PhotoSize(jsonObject["thumb"].toObject())						  : thumb = std::nullopt;
}

QJsonObject Telegram::StickerSet::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	QJsonObject stickerSetJsonObject{ {"name", name}, {"title", title}, {"is_animated", is_animated}, {"contains_masks", contains_masks}, {"stickers", QVectorToQJsonArray(stickers)} };

	if (thumb.has_value()) stickerSetJsonObject.insert("thumb", thumb->toObject());

	return stickerSetJsonObject;
}

bool Telegram::StickerSet::isEmpty() const
{
	return name == ""
		   and title == ""
		   and is_animated == false
		   and contains_masks == false
		   and stickers.isEmpty()
		   and thumb == std::nullopt;
}
