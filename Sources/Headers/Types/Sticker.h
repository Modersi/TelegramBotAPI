#ifndef TELEGRAM_TYPES_STICKER_H
#define TELEGRAM_TYPES_STICKER_H

#include <compare>
#include <optional>

#include "qstring.h"
#include "qjsonobject.h"

#include "Types/PhotoSize.h"
#include "Types/MaskPosition.h"

namespace Telegram
{
    /**
     *
     * @brief This struct represents a sticker
     *
     */

    struct Sticker
    {
        /** @brief Default constructor. Constructs an empty Sticker object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        Sticker();

        /** @brief Constructs Sticker object from parameters */
        Sticker(const QString& file_id,
                const QString& file_unique_id,
                const qint32& width,
                const qint32& height,
                const bool& is_animated,
                const std::optional<PhotoSize>& thumb = std::nullopt,
                const std::optional<QString>& emoji = std::nullopt,
                const std::optional<QString>& set_name = std::nullopt,
                const std::optional<MaskPosition>& mask_position = std::nullopt,
                const std::optional<qint32>& file_size = std::nullopt);

        /** @brief JSON constructor. Constructs Sticker object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has key-value pairs such as "file_id" = "...", "file_unique_id" = "..." to construct correct Sticker
         * object, otherwise fields related to missing pairs will be setted to 0, "", std::nullopt */
        Sticker(const QJsonObject& json_object);


        /** @brief Returns Sticker in form of JSON object. Returns empty QJsonObject if Sticker is empty */
        QJsonObject toObject() const;

        /** @brief Returns true if Sticker is empty */
        bool isEmpty() const;


        std::partial_ordering operator <=> (const Sticker&) const = default;


//** Fields **//

        /** @brief Identifier for this sticker, which can be used to download or reuse the file */
        QString file_id;

        /** @brief Unique identifier for this file, which is supposed to be the same over time and for different bots. Can't be used to download or reuse the file */
        QString file_unique_id;

        /** @brief Sticker width */
        qint32 width;

        /** @brief Sticker height */
        qint32 height;

        /** @brief True, if the sticker is animated */
        bool is_animated;

        /** @brief Optional. Sticker thumbnail in the .WEBP or .JPG format */
        std::optional<PhotoSize> thumb;

        /** @brief Optional. Emoji associated with the sticker */
        std::optional<QString> emoji;

        /** @brief Optional. Name of the sticker set to which the sticker belongs */
        std::optional<QString> set_name;

        /** @brief Optional. For mask stickers, the position where the mask should be placed */
        std::optional<MaskPosition> mask_position;

        /** @brief Optional. File size */
        std::optional<qint32> file_size;
    };
}

#endif // TELEGRAM_TYPES_STICKER_H
