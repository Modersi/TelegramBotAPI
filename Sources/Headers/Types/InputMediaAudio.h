#ifndef TELEGRAM_TYPES_INPUTMEDIAAUDIO_H
#define TELEGRAM_TYPES_INPUTMEDIAAUDIO_H

#include <compare>
#include <variant>
#include <optional>

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
     * @brief Represents an audio file to be treated as music to be sent
     *
     */

    struct InputMediaAudio : public InputMedia
    {
        /** @brief Default constructor. Constructs an empty InputMediaAudio object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        InputMediaAudio();

        /** @brief Constructs InputMediaAudio object from parameters */
        InputMediaAudio(const std::variant<QFile*, QString>& media,
                        const std::optional<std::variant<QFile*, QString>>& thumb = std::nullopt,
                        const std::optional<QString>& caption = std::nullopt,
                        const std::optional<QString>& parse_mode = std::nullopt,
                        const std::optional<QVector<MessageEntity>>& caption_entities = std::nullopt,
                        const std::optional<qint32>& duration = std::nullopt,
                        const std::optional<QString>& performer = std::nullopt,
                        const std::optional<QString>& title = std::nullopt);

        /** @brief JSON constructor. Constructs InputMediaAudio object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has all key-value pairs related to InputMediaAudio class fields. For example it should contain pairs such as "type" = "...",
         * "media" = "..." and so on, otherwise fields related to missing pairs will be setted to some default values(0, "", std::nullopt) */
        InputMediaAudio(const QJsonObject& json_object);


        /* @brief Returns InputMediaAudio in form of JSON object. Returns empty QJsonObject if InputMediaAudio is empty */
        virtual QJsonObject toObject() const override;

        /* @brief Returns true if InputMediaAudio is empty */
        virtual bool isEmpty() const override;
        
        /** @brief Returns type of the InputMedia */
        virtual Type getType() const override;


        std::partial_ordering operator <=> (const InputMediaAudio&) const = default;


//** Fields **//

        /** @brief Type of the input media. Must be "audio" */
        const Type type = Type::AUDIO;

        /** @brief Audio to send
         *
         * Pass a file_id to send an audio that exists on the Telegram servers, pass an HTTP URL for Telegram to get an audio from the Internet, or pass QFile* to upload a new one */
        std::variant<QFile*, QString> media;

        /** @brief Optional. Thumbnail of the audio sent
         *
         * Сan be ignored if thumbnail generation for the audio is supported server-side. The thumbnail should be in JPEG format and less than 200 kB in size. A thumbnail's width and height should not exceed 320. Thumbnails can't be reused with file_id and can be only uploaded as a new file via QFile* */
        std::optional<std::variant<QFile*, QString>> thumb;

        /** @brief Optional. Caption of the audio to be sent, 0-1024 characters after entities parsing */
        std::optional<QString> caption;

        /** @brief Optional. Mode for parsing entities in the audio caption. See formatting options for more details. */
        std::optional<QString> parse_mode;

        /** @brief Optional. List of special entities that appear in the caption, which can be specified instead of parse_mode */
        std::optional<QVector<MessageEntity>> caption_entities;

        /** @brief Optional. Audio duration */
        std::optional<qint32> duration;

        /** @brief Optional. Performer of the audio */
        std::optional<QString> performer;

        /** @brief Optional. Title of the audio */
        std::optional<QString> title;
    };
}

#endif // TELEGRAM_TYPES_INPUTMEDIAAUDIO_H
