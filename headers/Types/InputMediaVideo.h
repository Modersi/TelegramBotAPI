#ifndef TELEGRAM_TYPES_INPUTMEDIAVIDEO_H
#define TELEGRAM_TYPES_INPUTMEDIAVIDEO_H

#include "MessageEntity.h"

#include <variant>

#include "qvector.h"

namespace Telegram
{
    /**
     *
     * @brief Represents a video to be sent
     *
     */

    struct InputMediaVideo
    {
        /** @brief Default constructor. Constructs an empty InputMediaVideo object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        InputMediaVideo();

        /** @brief Constructs InputMediaVideo object from parameters */
        InputMediaVideo(const std::variant<QFile*, QString>& media,
                        const std::optional<std::variant<QFile*, QString>>& thumb  = std::nullopt,
                        const std::optional<QString>& caption = std::nullopt,
                        const std::optional<QString>& parse_mode = std::nullopt,
                        const std::optional<QVector<MessageEntity>>& caption_entities = std::nullopt,
                        const std::optional<qint32>& width = std::nullopt,
                        const std::optional<qint32>& height = std::nullopt,
                        const std::optional<qint32>& duration = std::nullopt,
                        const std::optional<bool>& supports_streaming = std::nullopt);

        /** @brief JSON constructor. Constructs InputMediaVideo object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has all key-value pairs related to InputMediaVideo class fields. For example it should contain pairs such as "type" = "...",
         * "media" = "..." and so on, otherwise fields related to missing pairs will be setted to some default values(0, "", std::nullopt) */
        InputMediaVideo(const QJsonObject& jsonObject);

        /* @brief Returns InputMediaVideo in form of JSON object. Returns empty QJsonObject if InputMediaVideo is empty */
        QJsonObject toObject() const;

        /* @brief Returns true if InputMediaVideo is empty */
        bool isEmpty() const;

//** Fields **//

        /** @brief Type of the result, must be animation */
        const QString type = "video";

        /** @brief File to send
         *
         * Pass a file_id to send a file that exists on the Telegram servers, pass an HTTP URL for Telegram to get a file from the Internet, or pass QFile* to upload a new one */
        std::variant<QFile*, QString> media;

        /** @brief Optional. Thumbnail of the file sent
         *
         * Сan be ignored if thumbnail generation for the file is supported server-side. The thumbnail should be in JPEG format and less than 200 kB in size. A thumbnail's width and height should not exceed 320. Thumbnails can't be reused with file_id and can be only uploaded as a new file via QFile* */
        std::optional<std::variant<QFile*, QString>> thumb;

        /** @brief Optional. Caption of the animation to be sent, 0-1024 characters after entities parsing */
        std::optional<QString> caption;

        /** @brief Optional. Mode for parsing entities in the animation caption. See formatting options for more details. */
        std::optional<QString> parse_mode;

        /** @brief Optional. List of special entities that appear in the caption, which can be specified instead of parse_mode */
        std::optional<QVector<MessageEntity>> caption_entities;

        /** @brief Optional. Animation width */
        std::optional<qint32> width;

        /** @brief Optional. Animation height */
        std::optional<qint32> height;

        /** @brief Optional. Animation duration */
        std::optional<qint32> duration;

        /** @brief Optional. Optional. Pass True, if the uploaded video is suitable for streaming*/
        std::optional<bool> supports_streaming;
    };
}

#endif // TELEGRAM_TYPES_INPUTMEDIAVIDEO_H
