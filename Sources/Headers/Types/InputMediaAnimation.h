#ifndef TELEGRAM_TYPES_INPUTMEDIAANIMATION_H
#define TELEGRAM_TYPES_INPUTMEDIAANIMATION_H

#include <compare>
#include <optional>
#include <variant>

#include "qstring.h"
#include "qjsonobject.h"
#include "qvector.h"
#include "qfile.h"

#include "InputMedia.h"
#include "MessageEntity.h"

namespace Telegram
{
    /**
     *
     * @brief This struct represents an animation file to be sent
     *
     *  Animation can only be GIF or H.264/MPEG-4 AVC video without sound
     *
     */

    struct InputMediaAnimation : public InputMedia
    {
        /** @brief Default constructor. Constructs an empty InputMediaAnimation object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        InputMediaAnimation();

        /** @brief Constructs InputMediaAnimation object from parameters */
        InputMediaAnimation(const std::variant<QFile*, QString>& media,
                            const std::optional<std::variant<QFile*, QString>>& thumb  = std::nullopt,
                            const std::optional<QString>& caption = std::nullopt,
                            const std::optional<QString>& parse_mode = std::nullopt,
                            const std::optional<QVector<MessageEntity>>& caption_entities = std::nullopt,
                            const std::optional<qint32>& width = std::nullopt,
                            const std::optional<qint32>& height = std::nullopt,
                            const std::optional<qint32>& duration = std::nullopt);

        /** @brief JSON constructor. Constructs InputMediaAnimation object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has all key-value pairs related to InputMediaAnimation class fields. For example it should contain pairs such as "type" = "...",
         * "media" = "..." and so on, otherwise fields related to missing pairs will be setted to some default values(0, "", std::nullopt) */
        InputMediaAnimation(const QJsonObject& json_object);


        /** @brief Returns InputMediaAnimation in form of JSON object. Returns empty QJsonObject if InputMediaAnimation is empty */
        virtual QJsonObject toObject() const override;

        /** @brief Returns true if InputMediaAnimation is empty */
        virtual bool isEmpty() const override;

        /** @brief Returns type of the InputMedia */
        virtual Type getType() const override;


        std::partial_ordering operator <=> (const InputMediaAnimation&) const = default;


//** Fields **//
        
        /** @brief Type of the input media. Must be "animation" */
        const Type type = Type::ANIMATION;

        /** @brief Animation to send
         * 
         * Pass a file_id to send a animation that exists on the Telegram servers, pass an HTTP URL for Telegram to get an animation from the Internet, or pass QFile* to upload a new one */
        std::variant<QFile*, QString> media;

        /** @brief Optional. Thumbnail of the animation sent
         *
         * Сan be ignored if thumbnail generation for the file is supported server-side. The thumbnail should be in JPEG format and less than 200 kB in size. A thumbnail's width and height should not exceed 320. Thumbnails can't be reused with file_id and can be only uploaded as a new file */
        std::optional<std::variant<QFile*, QString>> thumb;

        /** @brief Optional. Caption of the animation to be sent, 0-1024 characters after entities parsing */
        std::optional<QString> caption;

        /** @brief Optional. Mode for parsing entities in the media caption */
        std::optional<QString> parse_mode;

        /** @brief Optional. List of special entities that appear in the caption, which can be specified instead of parse_mode */
        std::optional<QVector<MessageEntity>> caption_entities;
        
        /** @brief Optional. Animation width */
        std::optional<qint32> width;
        
        /** @brief Optional. Animation height */
        std::optional<qint32> height;
        
        /** @brief Optional. Animation duration */
        std::optional<qint32> duration;
    };
}

#endif // TELEGRAM_TYPES_INPUTMEDIAANIMATION_H
