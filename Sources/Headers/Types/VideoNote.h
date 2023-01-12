#ifndef TELEGRAM_TYPES_VIDEONOTE_H
#define TELEGRAM_TYPES_VIDEONOTE_H

#include <compare>
#include <optional>

#include "qstring.h"
#include "qjsonobject.h"

#include "PhotoSize.h"

namespace Telegram
{
    /**
     *
     * @brief This object represents a video message (available in Telegram apps as of v.4.0)
     *
     */

    struct VideoNote
    {
        /** @brief Default constructor. Constructs an empty VideoNote object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        VideoNote();

        /** @brief Constructs VideoNote object from parameters */
        VideoNote(const QString& file_id,
                  const QString& file_unique_id,
                  const qint32& length,
                  const qint32& duration,
                  const std::optional<PhotoSize>& thumb = std::nullopt,
                  const std::optional<qint32>& file_size = std::nullopt);

        /** @brief JSON constructor. Constructs VideoNote object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has all key-value pairs related to VideoNote class fields. For example it should contain pairs such as "file_id" = "...",
         * "file_unique_id" = "..." and so on, otherwise fields related to missing pairs will be setted to some default values(0, "", std::nullopt) */
        VideoNote(const QJsonObject& json_object);


        /** @brief Returns VideoNote in form of JSON object. Returns empty QJsonObject if VideoNote is empty */
        QJsonObject toObject() const;

        /** @brief Returns true if VideoNote is empty */
        bool isEmpty() const;


        std::partial_ordering operator <=> (const VideoNote&) const = default;


//** Fields **//

        /** @brief Identifier for this file, which can be used to download or reuse the file */
        QString file_id;

        /** @brief Unique identifier for this file, which is supposed to be the same over timeand for different bots.Can't be used to download or reuse the file */
        QString file_unique_id;

        /** @brief Video width and height (diameter of the video message) as defined by sender */
        qint32 length;

        /** @brief Duration of the video in seconds as defined by sender */
        qint32 duration;

        /** @brief Optional. Video thumbnail */
        std::optional<PhotoSize> thumb;

        /** @brief Optional. File size */
        std::optional<qint32> file_size;
    };
}

#endif // TELEGRAM_TYPES_VIDEONOTE_H
