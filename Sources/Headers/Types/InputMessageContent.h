#ifndef TELEGRAM_TYPES_INPUTMESSAGECONTENT_H
#define TELEGRAM_TYPES_INPUTMESSAGECONTENT_H

#include <compare>

#include "qjsonobject.h"

namespace Telegram
{
    /**
    *
    * @brief This struct represents the content of a message to be sent as a result of an inline query. This is an abstract class, it's only base class for classes listed below
    *
    *   Telegram clients currently support the following 5 types:
    *   • InputTextMessageContent
    *   • InputLocationMessageContent
    *   • InputVenueMessageContent
    *   • InputContactMessageContent
    *   • InputInvoiceMessageContent
    *
    */

    struct InputMessageContent
    {
        /* @brief Returns InputMessageContent in form of JSON object */
        inline virtual QJsonObject toObject() const = 0;

        /** @brief Returns true if InputMessageContent is empty */
        virtual bool isEmpty() const = 0;


        /** @brief Virtual destructor */
        virtual ~InputMessageContent() = default;   


        std::partial_ordering operator <=> (const InputMessageContent&) const = default;

    };
}

#include "InputTextMessageContent.h"
#include "InputLocationMessageContent.h"
#include "InputVenueMessageContent.h"
#include "InputContactMessageContent.h"
#include "InputInvoiceMessageContent.h"

#endif // TELEGRAM_TYPES_INPUTMESSAGECONTENT_H
