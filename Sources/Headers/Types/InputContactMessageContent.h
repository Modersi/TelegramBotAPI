#ifndef TELEGRAM_TYPES_INPUTCONTACTMESSAGECONTENT_H
#define TELEGRAM_TYPES_INPUTCONTACTMESSAGECONTENT_H

#include <compare>
#include <optional>

#include "qstring.h"
#include "qjsonobject.h"

#include "Types/InputMessageContent.h"

namespace Telegram
{
    /**
    *
    * @brief This struct represents the content of a venue message to be sent as the result of an inline query
    *
    */

    struct InputContactMessageContent : public InputMessageContent
    {
        /** @brief Default constructor. Constructs an empty InputContactMessageContent object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        InputContactMessageContent();

        /** @brief Constructs InputContactMessageContent object from parameters */
        InputContactMessageContent(const QString& phone_number,
                                   const QString& first_name,	 
                                   const std::optional<QString>& last_name = std::nullopt,	 
                                   const std::optional<QString>& vcard = std::nullopt);


        /* @brief Returns InputContactMessageContent in form of JSON object. Returns empty QJsonObject if InputContactMessageContent is empty */
        virtual QJsonObject toObject() const override;

        /* @brief Returns true if InputContactMessageContent is empty */
        virtual bool isEmpty() const override;


        std::partial_ordering operator <=> (const InputContactMessageContent&) const = default;


//** Fields **//

        /* @brief Contact's phone number */
        QString phone_number;
        
        /* @brief Contact's first name */
        QString first_name;
        
        /* @brief Optional. Contact's last name */
        std::optional<QString> last_name;
        
        /* @brief Optional. Additional data about the contact in the form of a vCard, 0-2048 bytes */
        std::optional<QString> vcard;
    };
}

#endif // TELEGRAM_TYPES_INPUTCONTACTMESSAGECONTENT_H
