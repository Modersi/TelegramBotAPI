#ifndef TELEGRAM_TYPES_STICKERSET_H
#define TELEGRAM_TYPES_STICKERSET_H

#include <compare>
#include <optional>

#include "qvector.h"
#include "qstring.h"
#include "qjsonobject.h"

#include "Sticker.h"
#include "PhotoSize.h"

namespace Telegram
{
    /**
     *
     * @brief This structure represents a sticker set
     *
     */

    struct StickerSet
    {
        /** @brief Default constructor. Constructs an empty StickerSet object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        StickerSet();

        /** @brief Constructs StickerSet object from parameters */
        StickerSet(const QString& name,
                   const QString& title,
                   const bool& is_animated,
                   const bool& contains_masks,
                   const QVector<Sticker>& stickers,
                   const std::optional<PhotoSize>& thumb = std::nullopt);

        /** @brief JSON constructor. Constructs StickerSet object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has all key-value pairs related to StickerSet class fields. For example it should contain pairs such as "name" = "...",
         * "title" = "..." and so on, otherwise fields related to missing pairs will be setted to some default values(0, "", std::nullopt) */
        StickerSet(const QJsonObject& json_object);


        /** @brief Returns StickerSet in form of JSON object. Returns empty QJsonObject if StickerSet is empty */
        QJsonObject toObject() const;

        /** @brief Returns true if StickerSet is empty */
        bool isEmpty() const;


        std::partial_ordering operator <=> (const StickerSet&) const = default;


//** Fields **//

        /** @brief Sticker set name */
        QString name;

        /** @brief Sticker set title */
        QString title;

        /** @brief True, if the sticker set contains animated stickers */
        bool is_animated;

        /** @brief True, if the sticker set contains masks */
        bool contains_masks;

        /** @brief List of all set stickers */
        QVector<Sticker> stickers;

        /** @brief Optional. Sticker set thumbnail in the .WEBP or .TGS format */
        std::optional<PhotoSize> thumb;
    };
}

#endif // TELEGRAM_TYPES_STICKERSET_H
