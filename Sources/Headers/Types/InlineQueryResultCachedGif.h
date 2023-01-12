#ifndef TELEGRAM_TYPES_INLINEQUERYRESULTCACHEDGIF_H
#define TELEGRAM_TYPES_INLINEQUERYRESULTCACHEDGIF_H

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
     * @brief This struct represents a link to an animated GIF file stored on the Telegram servers
     *
     * By default, this animated GIF file will be sent by the user with an optional caption. Alternatively, you can use input_message_content to send a message with specified content instead of the animation
     *
     */

    struct InlineQueryResultCachedGif : public InlineQueryResult
    {
        /** @brief Default constructor. Constructs an empty InlineQueryResultCachedGif object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        InlineQueryResultCachedGif();

        /** @brief Constructs InlineQueryResultCachedGif object from parameters */
        InlineQueryResultCachedGif(const QString& id,
                                   const QString& gif_file_id,
                                   const std::optional<QString>& title = std::nullopt,
                                   const std::optional<QString>& caption = std::nullopt,
                                   const std::optional<QString>& parse_mode = std::nullopt,
                                   const std::optional<QVector<MessageEntity>>& caption_entities = std::nullopt,
                                   const std::optional<InlineKeyboardMarkup>& reply_markup = std::nullopt,
                                   const std::optional<std::shared_ptr<InputMessageContent>>& input_message_content = std::nullopt);


        /* @brief Returns InlineQueryResultCachedGif in form of JSON object. Returns empty QJsonObject if InlineQueryResultCachedGif is empty */
        virtual QJsonObject toObject() const override;

        /* @brief Returns true if InlineQueryResultCachedGif is empty */
        virtual bool isEmpty() const override;

        /** @brief Returns type of the InlineQueryResult */
        virtual Type getType() const override;


        std::partial_ordering operator <=> (const InlineQueryResultCachedGif&) const = default;


//** Fields **//

        /** @brief Type of the result, must be gif */
        const Type type = Type::GIF;

        /** @brief Unique identifier for this result, 1-64 bytes */
        QString	id;

        /** @brief A valid file identifier for the GIF file */
        QString	gif_file_id;

        /** @brief Optional. Title for the result */
        std::optional<QString> title;

        /** @brief Optional. Caption of the GIF file to be sent, 0-1024 characters after entities parsing */
        std::optional<QString> caption;

        /** @brief Optional. Mode for parsing entities in the caption */
        std::optional<QString> parse_mode;

        /** @brief Optional. List of special entities that appear in the caption, which can be specified instead of parse_mode */
        std::optional<QVector<MessageEntity>> caption_entities;

        /** @brief Optional. Inline keyboard attached to the message */
        std::optional<InlineKeyboardMarkup> reply_markup;

        /** @brief Optional. Content of the message to be sent instead of the GIF animation */
        std::optional<std::shared_ptr<InputMessageContent>> input_message_content;
    };
}

#endif // TELEGRAM_TYPES_INLINEQUERYRESULTCACHEDGIF_H
