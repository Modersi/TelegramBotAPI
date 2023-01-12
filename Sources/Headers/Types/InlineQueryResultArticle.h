#ifndef TELEGRAM_TYPES_INLINEQUERYRESULTARTICLE_H
#define TELEGRAM_TYPES_INLINEQUERYRESULTARTICLE_H

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
    * @brief This struct represents a link to an article or web page
    *
    */

    struct InlineQueryResultArticle : public InlineQueryResult
    {
        /** @brief Default constructor. Constructs an empty InlineQueryResultArticle object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        InlineQueryResultArticle();

        /** @brief Constructs InlineQueryResultArticle object from parameters */
        InlineQueryResultArticle(const QString& id,
                                 const QString& title,
                                 const std::shared_ptr<InputMessageContent>& input_message_content,
                                 const std::optional<InlineKeyboardMarkup>& reply_markup = std::nullopt,
                                 const std::optional<QString>& url = std::nullopt,
                                 const std::optional<bool>& hide_url = std::nullopt,
                                 const std::optional<QString>& description = std::nullopt,
                                 const std::optional<QString>& thumb_url = std::nullopt,
                                 const std::optional<qint32>& thumb_width = std::nullopt,
                                 const std::optional<qint32>& thumb_height = std::nullopt);


        /* @brief Returns InlineQueryResultArticle in form of JSON object. Returns empty QJsonObject if InlineQueryResultArticle is empty */
        virtual QJsonObject toObject() const override;

        /* @brief Returns true if InlineQueryResultArticle is empty */
        virtual bool isEmpty() const override;

        /** @brief Returns type of the InlineQueryResult */
        virtual Type getType() const override;


        std::partial_ordering operator <=> (const InlineQueryResultArticle&) const = default;

//** Fields **//

        /** @brief Type of the result, must be article */
        const Type type = Type::ARTICLE;

        /** @brief Unique identifier for this result, 1-64 Bytes */
        QString id;

        /** @brief Title of the result */
        QString title;

        /** @brief Content of the message to be sent */
        std::shared_ptr<InputMessageContent> input_message_content;

        /** @brief Optional. Inline keyboard attached to the message */
        std::optional<InlineKeyboardMarkup> reply_markup;
        
        /** @brief Optional. URL of the result */
        std::optional<QString> url;
        
        /** @brief Optional. Pass True, if you don't want the URL to be shown in the message */
        std::optional<bool> hide_url;
        
        /** @brief Optional. Short description of the result */
        std::optional<QString> description;
        
        /** @brief Optional. Url of the thumbnail for the result */
        std::optional<QString> thumb_url;
        
        /** @brief Optional. Thumbnail width */
        std::optional<qint32> thumb_width;
        
        /** @brief Optional. Thumbnail height */
        std::optional<qint32> thumb_height;
    };
}

#endif // TELEGRAM_TYPES_INLINEQUERYRESULTARTICLE_H
