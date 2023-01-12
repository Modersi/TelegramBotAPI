#ifndef TELEGRAM_TYPES_DOCUMENT_H
#define TELEGRAM_TYPES_DOCUMENT_H

#include <compare>
#include <optional>

#include "qstring.h"
#include "qjsonobject.h"

#include "PhotoSize.h"

namespace Telegram
{
    /**
     *
     * @brief This struct represents a general file (as opposed to photos, voice messages and audio files)
     *
     */

    struct Document
    {
        /** @brief Default constructor. Constructs an empty Document object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        Document();

        /** @brief Constructs Document object from parameters */
        Document(const QString& file_id,
                 const QString& file_unique_id,
                 const std::optional<PhotoSize>& thumb = std::nullopt,
                 const std::optional<QString>& file_name = std::nullopt,
                 const std::optional<QString>& mime_type = std::nullopt,
                 const std::optional<qint32>& file_size = std::nullopt);

        /** @brief JSON constructor. Constructs Document object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has all key-value pairs related to Document class fields. For example it should contain pairs such as "file_id" = "...",
         * "file_unique_id" = "..." and so on, otherwise fields related to missing pairs will be setted to some default values(0, "", std::nullopt) */
        Document(const QJsonObject& json_object);


        /* @brief Returns Document in form of JSON object. Returns empty QJsonObject if Document is empty */
        QJsonObject toObject() const;

        /* @brief Returns true if Document is empty */
        bool isEmpty() const;


        std::partial_ordering operator <=> (const Document&) const = default;


//** Fields **//

        /** @brief Identifier for this file, which can be used to download or reuse the file */
        QString file_id;
        
        /** @brief Unique identifier for this file, which is supposed to be the same over timeand for different bots. Can't be used to download or reuse the file */
        QString file_unique_id;
        
        /** @brief Optional. Document thumbnail as defined by sender */
        std::optional<PhotoSize> thumb;
        
        /** @brief Optional. Original filename as defined by sender */
        std::optional<QString> file_name;
        
        /** @brief Optional. [MIME](https://en.wikipedia.org/wiki/Media_type) type of the file as defined by sender */
        std::optional<QString> mime_type;
        
        /** @brief Optional. File size */
        std::optional<qint32> file_size;
    };
}

#endif // TELEGRAM_TYPES_DOCUMENT_H
