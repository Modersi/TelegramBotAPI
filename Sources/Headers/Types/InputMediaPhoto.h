#ifndef TELEGRAM_TYPES_INPUTMEDIAPHOTO_H
#define TELEGRAM_TYPES_INPUTMEDIAPHOTO_H

#include <variant>

class QJsonObject;
#include "qvector.h"

#include "InputMedia.h"
#include "MessageEntity.h"

namespace Telegram
{
    /**
     *
     * @brief Represents a photo to be sent
     *
     */

    struct InputMediaPhoto : public InputMedia
    {
        /** @brief Default constructor. Constructs an empty InputMediaPhoto object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        InputMediaPhoto();

        /** @brief Constructs InputMediaPhoto object from parameters */
        InputMediaPhoto(const std::variant<QFile*, QString>& media,
                        const std::optional<QString>& caption = std::nullopt,
                        const std::optional<QString>& parse_mode = std::nullopt,
                        const std::optional<QVector<MessageEntity>>& caption_entities = std::nullopt);

        /** @brief JSON constructor. Constructs InputMediaPhoto object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has all key-value pairs related to InputMediaPhoto class fields. For example it should contain pairs such as "type" = "...",
         * "media" = "..." and so on, otherwise fields related to missing pairs will be setted to some default values(0, "", std::nullopt) */
        InputMediaPhoto(const QJsonObject& jsonObject);

        /* @brief Returns InputMediaPhoto in form of JSON object. Returns empty QJsonObject if InputMediaPhoto is empty */
        virtual QJsonObject toObject() const override;

        /* @brief Returns true if InputMediaPhoto is empty */
        virtual bool isEmpty() const override;

//** Fields **//

        /** @brief Type of the input media. Must be "photo" */
        const QString type = "photo";

        /** @brief Photo to send
         *
         * Pass a file_id to send a photo that exists on the Telegram servers, pass an HTTP URL for Telegram to get a photo from the Internet, or pass QFile* to upload a new one */
        std::variant<QFile*, QString> media;

        /** @brief Optional. Caption of the photo to be sent, 0-1024 characters after entities parsing */
        std::optional<QString> caption;

        /** @brief Optional. Mode for parsing entities in the photo caption */
        std::optional<QString> parse_mode;

        /** @brief Optional. List of special entities that appear in the caption, which can be specified instead of parse_mode */
        std::optional<QVector<MessageEntity>> caption_entities;
    };
}

#endif // TELEGRAM_TYPES_INPUTMEDIAPHOTO_H