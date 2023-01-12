#ifndef TELEGRAM_TYPES_VOICE_H
#define TELEGRAM_TYPES_VOICE_H

#include <compare>
#include <optional>

#include "qstring.h"
#include "qjsonobject.h"

#include "PhotoSize.h"

namespace Telegram
{
    /**
     *
     * @brief This object represents a voice note
     *
     */

    struct Voice
    {
        /** @brief Default constructor. Constructs an empty Voice object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        Voice();

        /** @brief Constructs Voice object from parameters */
        Voice(const QString& file_id,
              const QString& file_unique_id,
              const qint32& duration,
              const std::optional<QString>& mime_type = std::nullopt,
              const std::optional<qint32>& file_size = std::nullopt);

        /** @brief JSON constructor. Constructs Voice object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has all key-value pairs related to Voice class fields. For example it should contain pairs such as "file_id" = "...",
         * "file_unique_id" = "..." and so on, otherwise fields related to missing pairs will be setted to some default values(0, "", std::nullopt) */
        Voice(const QJsonObject& json_object);


        /** @brief Returns Voice in form of JSON object. Returns empty QJsonObject if Voice is empty */
        QJsonObject toObject() const;

        /** @brief Returns true if Voice is empty */
        bool isEmpty() const;


        std::partial_ordering operator <=> (const Voice&) const = default;


//** Fields **//

        /** @brief Identifier for this file, which can be used to download or reuse the file */
        QString file_id;

        /** @brief Unique identifier for this file, which is supposed to be the same over timeand for different bots. Can't be used to download or reuse the file */
        QString file_unique_id;

        /** @brief Duration of the video in seconds as defined by sender */
        qint32 duration;

        /** @brief Optional. Mime type of a file as defined by sender */
        std::optional<QString> mime_type;

        /** @brief Optional. File size */
        std::optional<qint32> file_size;
    };
}

#endif // TELEGRAM_TYPES_VOICE_H

