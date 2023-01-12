#ifndef TELEGRAM_TYPES_PHOTOSIZE_H
#define TELEGRAM_TYPES_PHOTOSIZE_H

#include <compare>
#include <optional>

#include "qstring.h"
class QJsonObject;

namespace Telegram
{
    /**
     *
     * @brief This object represents one size of a photo or a file/sticker thumbnail
     *
     */

    struct PhotoSize
    {
        /** @brief Default constructor. Constructs an empty PhotoSize object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        PhotoSize();

        /** @brief Constructs PhotoSize object from parameters */
        PhotoSize(const QString& file_id,
                  const QString& file_unique_id,
                  const qint32&  width,
                  const qint32&  height,
                  const std::optional<qint32>& file_size = std::nullopt);

        /** @brief JSON constructor. Constructs PhotoSize object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has all key-value pairs related to PhotoSize class fields. For example it should contain pairs such as "file_id" = "...",
         * "file_unique_id" = "..." and so on, otherwise fields related to missing pairs will be setted to some default values(0, "", std::nullopt) */
        PhotoSize(const QJsonObject& json_object);

        /* @brief Returns PhotoSize in form of JSON object. Returns empty QJsonObject if PhotoSize is empty */
        QJsonObject toObject() const;

        /* @brief Returns true if PhotoSize is empty */
        bool isEmpty() const;

        std::partial_ordering operator <=> (const PhotoSize&) const = default;

//** Fields **//

        /** @brief Identifier for this file, which can be used to download or reuse the file */
        QString file_id;
        
        /** @brief Unique identifier for this file, which is supposed to be the same over time and for different bots. Can't be used to download or reuse the file */
        QString file_unique_id;
        
        /** @brief Photo width */
        qint32 width;
        
        /** @brief Photo height */
        qint32 height;
        
        /** @brief Optional. File size */
        std::optional<qint32> file_size;
    };
}

#endif // TELEGRAM_TYPES_PHOTOSIZE_H
