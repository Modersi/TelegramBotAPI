#ifndef TELEGRAM_TYPES_INLINEQUERYRESULTCACHEDPHOTO_H
#define TELEGRAM_TYPES_INLINEQUERYRESULTCACHEDPHOTO_H

#include <compare>
#include <optional>
#include <memory>

#include "qstring.h"
#include "qvector.h"
#include "qjsonobject.h"

#include "Types/InputMessageContent.h"
#include "Types/InlineQueryResult.h"
#include "Types/InlineKeyboardMarkup.h"
#include "Types/MessageEntity.h"

namespace Telegram
{
    /**
     *
     * @brief This struct represents a link to a photo stored on the Telegram servers
     *
     * By default, this photo will be sent by the user with an optional caption. Alternatively, you can use input_message_content to send a message with the specified content instead of the photo
     *
     */

    struct InlineQueryResultCachedPhoto : public InlineQueryResult
    {
        /** @brief Default constructor. Constructs an empty InlineQueryResultCachedPhoto object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        InlineQueryResultCachedPhoto();

        /** @brief Constructs InlineQueryResultCachedPhoto object from parameters */
        InlineQueryResultCachedPhoto(const QString& id,	                 
                                     const QString& photo_file_id,	     
                                     const std::optional<QString>& title = std::nullopt,	             
                                     const std::optional<QString>& description = std::nullopt,	         
                                     const std::optional<QString>& caption = std::nullopt,	             
                                     const std::optional<QString>& parse_mode = std::nullopt,	         
                                     const std::optional<QVector<MessageEntity>>& caption_entities = std::nullopt,	 
                                     const std::optional<InlineKeyboardMarkup>& reply_markup = std::nullopt,	     
                                     const std::optional<std::shared_ptr<InputMessageContent>>& input_message_content = std::nullopt);


        /* @brief Returns InlineQueryResultCachedPhoto in form of JSON object. Returns empty QJsonObject if InlineQueryResultCachedPhoto is empty */
        virtual QJsonObject toObject() const override;

        /* @brief Returns true if InlineQueryResultCachedPhoto is empty */
        virtual bool isEmpty() const override;

        /** @brief Returns type of the InlineQueryResult */
        virtual Type getType() const override;


        std::partial_ordering operator <=> (const InlineQueryResultCachedPhoto&) const = default;


//** Fields **//

        /** @brief Type of the result, must be photo */
        const Type type = Type::PHOTO;
        
        /** @brief Unique identifier for this result, 1-64 bytes */
        QString	id;
        
        /** @brief A valid file identifier of the photo */
        QString	photo_file_id;
        
        /** @brief Optional. Title for the result */
        std::optional<QString> title;
        
        /** @brief Optional. Short description of the result */
        std::optional<QString> description;
        
        /** @brief Optional. Caption of the photo to be sent, 0-1024 characters after entities parsing */
        std::optional<QString> caption;
        
        /** @brief Optional. Mode for parsing entities in the photo caption */
        std::optional<QString> parse_mode;
        
        /** @brief Optional. List of special entities that appear in the caption, which can be specified instead of parse_mode */
        std::optional<QVector<MessageEntity>> caption_entities;
        
        /** @brief Optional. Inline keyboard attached to the message */  
        std::optional<InlineKeyboardMarkup> reply_markup;
        
        /** @brief Optional. Content of the message to be sent instead of the photo */
        std::optional<std::shared_ptr<InputMessageContent>> input_message_content;
    };
}

#endif // TELEGRAM_TYPES_INLINEQUERYRESULTCACHEDPHOTO_H
