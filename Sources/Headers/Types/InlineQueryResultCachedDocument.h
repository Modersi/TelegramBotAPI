#ifndef TELEGRAM_TYPES_INLINEQUERYRESULTCACHEDDOCUMENT_H
#define TELEGRAM_TYPES_INLINEQUERYRESULTCACHEDDOCUMENT_H

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
     * @brief This struct represents a link to a file stored on the Telegram servers
     *
     * By default, this file will be sent by the user with an optional caption. Alternatively, you can use input_message_content to send a message with the specified content instead of the file
     *
     */

    struct InlineQueryResultCachedDocument : public InlineQueryResult
    {
        /** @brief Default constructor. Constructs an empty InlineQueryResultCachedDocument object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        InlineQueryResultCachedDocument();

        /** @brief Constructs InlineQueryResultCachedDocument object from parameters */
        InlineQueryResultCachedDocument(const QString& id,
                                        const QString& title,
                                        const QString& document_file_id,
                                        const std::optional<QString>& description = std::nullopt,
                                        const std::optional<QString>& caption = std::nullopt,
                                        const std::optional<QString>& parse_mode = std::nullopt,
                                        const std::optional<QVector<MessageEntity>>& caption_entities = std::nullopt,
                                        const std::optional<InlineKeyboardMarkup>& reply_markup = std::nullopt,
                                        const std::optional<std::shared_ptr<InputMessageContent>>& input_message_content = std::nullopt);


        /* @brief Returns InlineQueryResultCachedDocument in form of JSON object. Returns empty QJsonObject if InlineQueryResultCachedDocument is empty */
        virtual QJsonObject toObject() const override;

        /* @brief Returns true if InlineQueryResultCachedDocument is empty */
        virtual bool isEmpty() const override;

        /** @brief Returns type of the InlineQueryResult */
        virtual Type getType() const override;              


        std::partial_ordering operator <=> (const InlineQueryResultCachedDocument&) const = default;


//** Fields **//

        /** @brief Type of the result, must be document */
        const Type type = Type::DOCUMENT;

        /** @brief Unique identifier for this result, 1-64 bytes */
        QString	id;

        /** @brief Title for the result */
        QString title;

        /** @brief A valid file identifier for the file */
        QString	document_file_id;

        /** @brief Optional. Short description of the result */
        std::optional<QString> description;

        /** @brief Optional. Caption of the document to be sent, 0-1024 characters after entities parsing */
        std::optional<QString> caption;

        /** @brief Optional. Mode for parsing entities in the caption */
        std::optional<QString> parse_mode;

        /** @brief Optional. List of special entities that appear in the caption, which can be specified instead of parse_mode */
        std::optional<QVector<MessageEntity>> caption_entities;

        /** @brief Optional. Inline keyboard attached to the message */
        std::optional<InlineKeyboardMarkup> reply_markup;

        /** @brief Optional. Content of the message to be sent instead of the file */
        std::optional<std::shared_ptr<InputMessageContent>> input_message_content;
    };
}

#endif // TELEGRAM_TYPES_INLINEQUERYRESULTCACHEDDOCUMENT_H
