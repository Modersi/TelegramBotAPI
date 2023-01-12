#ifndef TELEGRAM_TYPES_INLINEQUERYRESULTCONTACT_H
#define TELEGRAM_TYPES_INLINEQUERYRESULTCONTACT_H

#include <compare>
#include <optional>
#include <memory>

#include "qstring.h"
#include "qjsonobject.h"
#include "qvector.h"

#include "Types/InputMessageContent.h"
#include "Types/InlineQueryResult.h"
#include "Types/InlineKeyboardMarkup.h"

namespace Telegram
{
    /**
     *
     * @brief This struct represents a contact with a phone number. By default, this contact will be sent by the user
     *
     * Alternatively, you can use input_message_content to send a message with the specified content instead of the contact
     *
     * > Note: This will only work in Telegram versions released after 9 April, 2016. Older clients will ignore them
     *
     */

    struct InlineQueryResultContact : public InlineQueryResult
    {
        /** @brief Default constructor. Constructs an empty InlineQueryResultContact object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        InlineQueryResultContact();

        /** @brief Constructs InlineQueryResultContact object from parameters */
        InlineQueryResultContact(const QString& id,
                                 const QString& phone_number,
                                 const QString& first_name,
                                 const std::optional<QString>& last_name = std::nullopt,
                                 const std::optional<QString>& vcard = std::nullopt,
                                 const std::optional<InlineKeyboardMarkup>& reply_markup = std::nullopt,
                                 const std::optional<std::shared_ptr<InputMessageContent>>& input_message_content = std::nullopt,
                                 const std::optional<QString>& thumb_url = std::nullopt,
                                 const std::optional<qint32>& thumb_width = std::nullopt,
                                 const std::optional<qint32>& thumb_height = std::nullopt);

        /* @brief Returns InlineQueryResultContact in form of JSON object. Returns empty QJsonObject if InlineQueryResultContact is empty */
        virtual QJsonObject toObject() const override;

        /* @brief Returns true if InlineQueryResultContact is empty */
        virtual bool isEmpty() const override;

        /** @brief Returns type of the InlineQueryResult */
        virtual Type getType() const override;

        std::partial_ordering operator <=> (const InlineQueryResultContact&) const = default;

//** Fields **//

        /** @brief Type of the result, must be contact */
        const Type type = Type::CONTACT;
        
        /** @brief Unique identifier for this result, 1-64 Bytes */
        QString	id;
        
        /** @brief Contact's phone number */
        QString	phone_number;
        
        /** @brief Contact's first name */
        QString	first_name;
        
        /** @brief Optional. Contact's last name */
        std::optional<QString> last_name;
        
        /** @brief Optional. Additional data about the contact in the form of a vCard, 0-2048 bytes */
        std::optional<QString> vcard;
        
        /** @brief Optional. Inline keyboard attached to the message */
        std::optional<InlineKeyboardMarkup> reply_markup;
        
        /** @brief Optional. Content of the message to be sent instead of the contact */
        std::optional<std::shared_ptr<InputMessageContent>> input_message_content;
        
        /** @brief Optional. Url of the thumbnail for the result */
        std::optional<QString> thumb_url;
        
        /** @brief Optional. Thumbnail width */
        std::optional<qint32> thumb_width;
        
        /** @brief Optional. Thumbnail height */
        std::optional<qint32> thumb_height;
    };
}

#endif // TELEGRAM_TYPES_INLINEQUERYRESULTCONTACT_H
