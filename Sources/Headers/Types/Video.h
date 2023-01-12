#ifndef TELEGRAM_TYPES_VIDEO_H
#define TELEGRAM_TYPES_VIDEO_H

#include <compare>
#include <optional>

#include "qstring.h"
#include "qjsonobject.h"

#include "PhotoSize.h"

namespace Telegram
{
    /**
     *
     * @brief This struct represents a video file
     *
     */

    struct Video
    {
        /** @brief Default constructor. Constructs an empty Video object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        Video();

        /** @brief Constructs Video object from parameters */
        Video(const QString& file_id,
              const QString& file_unique_id,
              const qint32& width,
              const qint32& height,
              const qint32& duration,
              const std::optional<PhotoSize>& thumb = std::nullopt,
              const std::optional<QString>& file_name = std::nullopt,
              const std::optional<QString>& mime_type = std::nullopt,
              const std::optional<qint32>& file_size = std::nullopt);

        /** @brief JSON constructor. Constructs Video object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has all key-value pairs related to Video class fields. For example it should contain pairs such as "file_id" = "...",
         * "file_unique_id" = "..." and so on, otherwise fields related to missing pairs will be setted to some default values(0, "", std::nullopt) */
        Video(const QJsonObject& json_object);


        /* @brief Returns Video in form of JSON object. Returns empty QJsonObject if Video is empty */
        QJsonObject toObject() const;

        /* @brief Returns true if Video is empty */
        bool isEmpty() const;


        std::partial_ordering operator <=> (const Video&) const = default;


//** Fields **//

        /** @brief Identifier for this file, which can be used to download or reuse the file*/
        QString file_id;
        
        /** @brief Unique identifier for this file, which is supposed to be the same over timeand for different bots.Can't be used to download or reuse the file */
        QString file_unique_id;
        
        /** @brief Video width as defined by sender */
        qint32 width;
        
        /** @brief Video height as defined by sender */
        qint32 height;
        
        /** @brief Duration of the video in seconds as defined by sender */
        qint32 duration;
        
        /** @brief Optional. Video thumbnail */
        std::optional<PhotoSize> thumb;
        
        /** @brief Optional. Original filename as defined by sender */
        std::optional<QString> file_name;
        
        /** @brief Optional. Mime type of a file as defined by sender */
        std::optional<QString> mime_type;
        
        /** @brief Optional. File size */
        std::optional<qint32> file_size;
    };
}

#endif // TELEGRAM_TYPES_VIDEO_H
