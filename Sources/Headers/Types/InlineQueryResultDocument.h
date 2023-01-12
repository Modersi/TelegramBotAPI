#ifndef TELEGRAM_TYPES_INLINEQUERYRESULTDOCUMENT_H
#define TELEGRAM_TYPES_INLINEQUERYRESULTDOCUMENT_H

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
     * @brief This struct represents a link to a file. By default, this file will be sent by the user with an optional caption
     *
     * Alternatively, you can use input_message_content to send a message with the specified content instead of the file. Currently, only .PDF and .ZIP files can be sent using this method
     *
     * > Note: This will only work in Telegram versions released after 9 April, 2016. Older clients will ignore them
     *
     */

    struct InlineQueryResultDocument : public InlineQueryResult
    {
        /** @brief Default constructor. Constructs an empty InlineQueryResultDocument object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        InlineQueryResultDocument();

        /** @brief Constructs InlineQueryResultDocument object from parameters */
        InlineQueryResultDocument(const QString& id,	                 
                                  const QString& title,	             
                                  const QString& document_url,	     
                                  const QString& mime_type,	         
                                  const std::optional<QString>& caption = std::nullopt,	             
                                  const std::optional<QString>& parse_mode = std::nullopt,	         
                                  const std::optional<QVector<MessageEntity>>& caption_entities = std::nullopt,	 
                                  const std::optional<QString>& description = std::nullopt,	         
                                  const std::optional<InlineKeyboardMarkup>& reply_markup = std::nullopt,	     
                                  const std::optional<std::shared_ptr<InputMessageContent>>& input_message_content = std::nullopt,
                                  const std::optional<QString>& thumb_url = std::nullopt,	         
                                  const std::optional<qint32>& thumb_width = std::nullopt,	         
                                  const std::optional<qint32>& thumb_height = std::nullopt);


        /* @brief Returns InlineQueryResultDocument in form of JSON object. Returns empty QJsonObject if InlineQueryResultDocument is empty */
        virtual QJsonObject toObject() const override;

        /* @brief Returns true if InlineQueryResultDocument is empty */
        virtual bool isEmpty() const override;

        /** @brief Returns type of the InlineQueryResult */
        virtual Type getType() const override;


        std::partial_ordering operator <=> (const InlineQueryResultDocument&) const = default;


//** Fields **//

        /** @brief Type of the result, must be document */
        const Type type = Type::DOCUMENT;
        
        /** @brief Unique identifier for this result, 1-64 bytes */
        QString	id;
        
        /** @brief Title for the result */
        QString	title;
        
        /** @brief A valid URL for the file */
        QString	document_url;
        
        /** @brief Mime type of the content of the file, either “application/pdf” or “application/zip” */
        QString	mime_type;
        
        /** @brief Optional. Caption of the document to be sent, 0-1024 characters after entities parsing */
        std::optional<QString> caption;
        
        /** @brief Optional. Mode for parsing entities in the document caption */
        std::optional<QString> parse_mode;
        
        /** @brief Optional. List of special entities that appear in the caption, which can be specified instead of parse_mode */
        std::optional<QVector<MessageEntity>> caption_entities;
        
        /** @brief Optional. Short description of the result */
        std::optional<QString> description;
        
        /** @brief Optional. Inline keyboard attached to the message */
        std::optional<InlineKeyboardMarkup> reply_markup;
        
        /** @brief Optional. Content of the message to be sent instead of the file */
        std::optional<std::shared_ptr<InputMessageContent>>	input_message_content;
        
        /** @brief Optional. URL of the thumbnail (jpeg only) for the file */
        std::optional<QString>	thumb_url;
        
        /** @brief Optional. Thumbnail width */
        std::optional<qint32> thumb_width;
        
        /** @brief Optional. Thumbnail height */
        std::optional<qint32> thumb_height;
    };
}

#endif // TELEGRAM_TYPES_INLINEQUERYRESULTDOCUMENT_H
