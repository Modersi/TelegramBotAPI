#ifndef TELEGRAM_TYPES_INLINEQUERYRESULTCACHEDSTICKER_H
#define TELEGRAM_TYPES_INLINEQUERYRESULTCACHEDSTICKER_H

#include <compare>
#include <optional>
#include <memory>

#include "qstring.h"
#include "qjsonobject.h"

#include "Types/InputMessageContent.h"
#include "Types/InlineQueryResult.h"
#include "Types/InlineKeyboardMarkup.h"

namespace Telegram
{
    /**
     *
     * @brief This represents a link to a sticker stored on the Telegram servers
     *
     * By default, this sticker will be sent by the user. Alternatively, you can use input_message_content to send a message with the specified content instead of the sticker
     *
     * > Note: This will only work in Telegram versions released after 9 April, 2016 for static stickers and after 06 July, 2019 for animated stickers. Older clients will ignore them
     * 
     */

    struct InlineQueryResultCachedSticker : public InlineQueryResult
    {
        /** @brief Default constructor. Constructs an empty InlineQueryResultCachedSticker object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        InlineQueryResultCachedSticker();

        /** @brief Constructs InlineQueryResultCachedSticker object from parameters */
        InlineQueryResultCachedSticker(const QString& id,
                                       const QString& sticker_file_id,
                                       const std::optional<InlineKeyboardMarkup>& reply_markup = std::nullopt,
                                       const std::optional<std::shared_ptr<InputMessageContent>>& input_message_content = std::nullopt);


        /* @brief Returns InlineQueryResultCachedSticker in form of JSON object. Returns empty QJsonObject if InlineQueryResultCachedSticker is empty */
        virtual QJsonObject toObject() const override;

        /* @brief Returns true if InlineQueryResultCachedSticker is empty */
        virtual bool isEmpty() const override;

        /** @brief Returns type of the InlineQueryResult */
        virtual Type getType() const override;


        std::partial_ordering operator <=> (const InlineQueryResultCachedSticker&) const = default;


//** Fields **//

        /** @brief Type of the result, must be sticker */
        const Type type = Type::STICKER;

        /** @brief Unique identifier for this result, 1-64 bytes */
        QString	id;

        /** @brief A valid file identifier of the sticker */
        QString	sticker_file_id;

        /** @brief Optional. Inline keyboard attached to the message */
        std::optional<InlineKeyboardMarkup> reply_markup;

        /** @brief Optional. Content of the message to be sent instead of the sticker */
        std::optional<std::shared_ptr<InputMessageContent>> input_message_content;
    };
}

#endif // TELEGRAM_TYPES_INLINEQUERYRESULTCACHEDSTICKER_H
