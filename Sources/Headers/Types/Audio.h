#ifndef TELEGRAM_TYPES_AUDIO_H
#define TELEGRAM_TYPES_AUDIO_H

#include <compare>

#include "qstring.h"
#include "qjsonobject.h"

#include "PhotoSize.h"

namespace Telegram 
{
    /**
     *
     * @brief This structure represents an Audio file to be treated as music by the Telegram clients
     *
     */

    struct Audio
    {
        /** @brief Default constructor. Constructs an empty Audio object
         *
         * All fields setted to 0, "", etc... All optional members setted to std::nullopt */
        Audio();

        /** @brief Constructs Audio object from parameters */
        Audio(const QString& file_id,
              const QString& file_unique_id,
              const qint32& duration,
              const std::optional<QString>& performer = std::nullopt,
              const std::optional<QString>& title = std::nullopt,
              const std::optional<QString>& file_name = std::nullopt,
              const std::optional<QString>& mime_type = std::nullopt,
              const std::optional<qint32>& file_size = std::nullopt,
              const std::optional<PhotoSize>& thumb = std::nullopt);

        /** @brief JSON constructor. Constructs Audio object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has all key-value pairs related to Audio class fields. For example it should contain pairs such as "file_id" = "...",
         * "file_unique_id" = "..." and so on, otherwise fields related to missing pairs will be setted to some default values(0, "", std::nullopt) */
        Audio(const QJsonObject& json_object);


        /** @brief Returns Audio in form of JSON object. Returns empty QJsonObject if Audio is empty */
        QJsonObject toObject() const;

        /** @brief Returns true if Audio is empty */
        bool isEmpty() const;


        std::partial_ordering operator <=> (const Audio&) const = default;


//** Fields **//

        /** @brief Identifier for this file, which can be used to download or reuse the file */
        QString file_id;

        /** @brief Unique identifier for this file, which is supposed to be the same over time and for different bots. Can't be used to download or reuse the file */
        QString file_unique_id;
        
        /** @brief Duration of the audio in seconds as defined by sender */
        qint32 duration;

        /** @brief Optional. Performer of the audio as defined by sender or by audio tags */
        std::optional<QString> performer;
        
        /** @brief Optional. Title of the audio as defined by sender or by audio tags */
        std::optional<QString> title;
        
        /** @brief Optional. Original filename as defined by sender */
        std::optional<QString> file_name;
        
        /** @brief Optional. [MIME](https://en.wikipedia.org/wiki/Media_type) type of the file as defined by sender */
        std::optional<QString> mime_type;
        
        /** @brief Optional. File size */
        std::optional<qint32> file_size;

        /** @brief Optional. Thumbnail of the album cover to which the music file belongs */
        std::optional<PhotoSize> thumb;
    };
}

#endif // TELEGRAM_TYPES_AUDIO_H
