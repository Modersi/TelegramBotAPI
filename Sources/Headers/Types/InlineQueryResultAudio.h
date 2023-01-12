#ifndef TELEGRAM_TYPES_INLINEQUERYRESULTAUDIO_H
#define TELEGRAM_TYPES_INLINEQUERYRESULTAUDIO_H

#include <compare>
#include <optional>
#include <memory>

#include "qstring.h"
#include "qjsonobject.h"
#include "qvector.h"

#include "Types/InputMessageContent.h"
#include "Types/InlineQueryResult.h"
#include "Types/InlineKeyboardMarkup.h"
#include "Types/MessageEntity.h"

namespace Telegram
{
    /**
     *
     * @brief This struct represents a link to an MP3 audio file. By default, this audio file will be sent by the user
     *
     * Alternatively, you can use input_message_content to send a message with the specified content instead of the audio
     *
     * > Note: This will only work in Telegram versions released after 9 April, 2016. Older clients will ignore them
     * 
     */

    struct InlineQueryResultAudio : public InlineQueryResult
    {
        /** @brief Default constructor. Constructs an empty InlineQueryResultAudio object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        InlineQueryResultAudio();

        /** @brief Constructs InlineQueryResultAudio object from parameters */
        InlineQueryResultAudio(const QString& id,	                 
                               const QString& audio_url,	         
                               const QString& title,	             
                               const std::optional<QString>& caption = std::nullopt,	             
                               const std::optional<QString>& parse_mode = std::nullopt,	         
                               const std::optional<QVector<MessageEntity>>& caption_entities = std::nullopt,	 
                               const std::optional<QString>& performer = std::nullopt,	         
                               const std::optional<qint32>& audio_duration = std::nullopt,	     
                               const std::optional<InlineKeyboardMarkup>& reply_markup = std::nullopt,	     
                               const std::optional<std::shared_ptr<InputMessageContent>>& input_message_content = std::nullopt);


        /* @brief Returns InlineQueryResultAudio in form of JSON object. Returns empty QJsonObject if InlineQueryResultAudio is empty */
        virtual QJsonObject toObject() const override;

        /* @brief Returns true if InlineQueryResultAudio is empty */
        virtual bool isEmpty() const override;

        /** @brief Returns type of the InlineQueryResult */
        virtual Type getType() const override;


        std::partial_ordering operator <=> (const InlineQueryResultAudio&) const = default;


//** Fields **//

        /** @brief Type of the result, must be audio */
        const Type type = Type::AUDIO;

        /** @brief Unique identifier for this result, 1-64 bytes */
        QString	id;
        
        /** @brief A valid URL for the audio file */
        QString	audio_url;
        
        /** @brief Title */
        QString	title;
        
        /** @brief Optional. Caption, 0-1024 characters after entities parsing */
        std::optional<QString> caption;
        
        /** @brief Optional. Mode for parsing entities in the audio caption */
        std::optional<QString> parse_mode;
        
        /** @brief Optional. List of special entities that appear in the caption, which can be specified instead of parse_mode */
        std::optional<QVector<MessageEntity>> caption_entities;
        
        /** @brief Optional. Performer */
        std::optional<QString>performer;
        
        /** @brief Optional. Audio duration in seconds */
        std::optional<qint32> audio_duration;
        
        /** @brief Optional. Inline keyboard attached to the message */
        std::optional<InlineKeyboardMarkup> reply_markup;
        
        /** @brief Optional. Content of the message to be sent instead of the audio */
        std::optional<std::shared_ptr<InputMessageContent>> input_message_content;
    };
}

#endif // TELEGRAM_TYPES_INLINEQUERYRESULTAUDIO_H
