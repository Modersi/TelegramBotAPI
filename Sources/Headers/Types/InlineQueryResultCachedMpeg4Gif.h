#ifndef TELEGRAM_TYPES_INLINEQUERYRESULTCACHEDMPEG4GIF_H
#define TELEGRAM_TYPES_INLINEQUERYRESULTCACHEDMPEG4GIF_H

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
     * @brief This struct represents a link to a video animation (H.264/MPEG-4 AVC video without sound) stored on the Telegram servers
     *
     * By default, this animated MPEG-4 file will be sent by the user with an optional caption. Alternatively, you can use input_message_content to send a message with the specified content instead of the animation
     *
     */

    struct InlineQueryResultCachedMpeg4Gif : public InlineQueryResult
    {
        /** @brief Default constructor. Constructs an empty InlineQueryResultCachedMpeg4Gif object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        InlineQueryResultCachedMpeg4Gif();

        /** @brief Constructs InlineQueryResultCachedMpeg4Gif object from parameters */
        InlineQueryResultCachedMpeg4Gif(const QString& id,
                                        const QString& mpeg4_file_id,
                                        const std::optional<QString>& title = std::nullopt,
                                        const std::optional<QString>& caption = std::nullopt,
                                        const std::optional<QString>& parse_mode = std::nullopt,
                                        const std::optional<QVector<MessageEntity>>& caption_entities = std::nullopt,
                                        const std::optional<InlineKeyboardMarkup>& reply_markup = std::nullopt,
                                        const std::optional<std::shared_ptr<InputMessageContent>>& input_message_content = std::nullopt);


        /* @brief Returns InlineQueryResultCachedMpeg4Gif in form of JSON object. Returns empty QJsonObject if InlineQueryResultCachedMpeg4Gif is empty */
        virtual QJsonObject toObject() const override;

        /* @brief Returns true if InlineQueryResultCachedMpeg4Gif is empty */
        virtual bool isEmpty() const override;

        /** @brief Returns type of the InlineQueryResult */
        virtual Type getType() const override;


        std::partial_ordering operator <=> (const InlineQueryResultCachedMpeg4Gif&) const = default;


//** Fields **//

        /** @brief Type of the result, must be mpeg4_gif */
        const Type type = Type::MPEG4_GIF;

        /** @brief Unique identifier for this result, 1-64 bytes */
        QString	id;

        /** @brief A valid file identifier for the MP4 file */
        QString	mpeg4_file_id;

        /** @brief Optional. Title for the result */
        std::optional<QString> title;

        /** @brief Optional. Caption of the MPEG-4 file to be sent, 0-1024 characters after entities parsing */
        std::optional<QString> caption;

        /** @brief Optional. Mode for parsing entities in the caption */
        std::optional<QString> parse_mode;

        /** @brief Optional. List of special entities that appear in the caption, which can be specified instead of parse_mode */
        std::optional<QVector<MessageEntity>> caption_entities;

        /** @brief Optional. Inline keyboard attached to the message */
        std::optional<InlineKeyboardMarkup> reply_markup;

        /** @brief Optional. Content of the message to be sent instead of the video animation */
        std::optional<std::shared_ptr<InputMessageContent>> input_message_content;
    };
}

#endif // TELEGRAM_TYPES_INLINEQUERYRESULTCACHEDMPEG4GIF_H
