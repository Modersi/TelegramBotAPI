#ifndef TELEGRAM_TYPES_INPUTINVOICEMESSAGECONTENT_H
#define TELEGRAM_TYPES_INPUTINVOICEMESSAGECONTENT_H

#include <compare>
#include <optional>

#include "qstring.h"
#include "qjsonobject.h"
#include "qvector.h"

#include "Types/InputMessageContent.h"
//#include "Types/LabeledPrice.h"

namespace Telegram
{
    /**
    *
    * @brief This struct represents the content of an invoice message to be sent as the result of an inline query
    *
    */

    struct InputInvoiceMessageContent : public InputMessageContent
    {
        /** @brief Default constructor. Constructs an empty InputInvoiceMessageContent object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        InputInvoiceMessageContent();

        /** @brief Constructs InputInvoiceMessageContent object from parameters */
        InputInvoiceMessageContent(const QString& title,	                     
                                   const QString& description,	                 
                                   const QString& payload,	                     
                                   const QString& provider_token,	             
                                   const QString& currency,	                 
                                   //const QVector<LabeledPrice>& prices,
                                   const std::optional<qint32>& max_tip_amount = std::nullopt,	             
                                   const std::optional<QVector<qint32>>& suggested_tip_amounts = std::nullopt,	     
                                   const std::optional<QJsonObject>& provider_data = std::nullopt,
                                   const std::optional<QString>& photo_url = std::nullopt,	                 
                                   const std::optional<qint32>& photo_size = std::nullopt,	                 
                                   const std::optional<qint32>& photo_width = std::nullopt,	                 
                                   const std::optional<qint32>& photo_height = std::nullopt,	             
                                   const std::optional<bool>& need_name = std::nullopt,	                 
                                   const std::optional<bool>& need_phone_number = std::nullopt,	         
                                   const std::optional<bool>& need_email = std::nullopt,	                 
                                   const std::optional<bool>& need_shipping_address = std::nullopt,	     
                                   const std::optional<bool>& send_phone_number_to_provider = std::nullopt,
                                   const std::optional<bool>& send_email_to_provider = std::nullopt,	     
                                   const std::optional<bool>& is_flexible = std::nullopt);


        /* @brief Returns InputInvoiceMessageContent in form of JSON object. Returns empty QJsonObject if InputInvoiceMessageContent is empty */
        virtual QJsonObject toObject() const override;

        /* @brief Returns true if InputInvoiceMessageContent is empty */
        virtual bool isEmpty() const override;


//** Fields **//

        /* @brief Product name, 1-32 characters */
        QString title;
        
        /* @brief Product description, 1-255 characters */
        QString description;
        
        /* @brief Bot-defined invoice payload, 1-128 bytes. This will not be displayed to the user, use for your internal processes */
        QString payload;
        
        /* @brief Payment provider token, obtained via Botfather */
        QString provider_token;
        
        /* @brief Three-letter ISO 4217 currency code, see more on https://core.telegram.org/bots/payments#supported-currencies */
        QString currency;
        
        /* @brief  Price breakdown, a list of components (e.g. product price, tax, discount, delivery cost, delivery tax, bonus, etc.) */
        //QVector<LabeledPrice> prices;
        
        /* @brief Optional. The maximum accepted amount for tips in the smallest units of the currency (integer, not float/double). For example, for a maximum tip of US$ 1.45 pass max_tip_amount = 145. See the exp parameter in currencies.json(https://core.telegram.org/bots/payments/currencies.json), it shows the number of digits past the decimal point for each currency (2 for the majority of currencies). Defaults to 0 */
        std::optional<qint32> max_tip_amount;
        
        /* @brief Optional. An array of suggested amounts of tip in the smallest units of the currency (integer, not float/double). At most 4 suggested tip amounts can be specified. The suggested tip amounts must be positive, passed in a strictly increased order and must not exceed max_tip_amount */
        std::optional<QVector<qint32>> suggested_tip_amounts;
        
        /* @brief Optional. A JSON-serialized object for data about the invoice, which will be shared with the payment provider. A detailed description of the required fields should be provided by the payment provider */
        std::optional<QJsonObject> provider_data;
        
        /* @brief Optional. URL of the product photo for the invoice. Can be a photo of the goods or a marketing image for a service. People like it better when they see what they are paying for */
        std::optional<QString> photo_url;
        
        /* @brief Optional. Photo size */
        std::optional<qint32> photo_size;
        
        /* @brief Optional. Photo width */
        std::optional<qint32> photo_width;
        
        /* @brief Optional. Photo height */
        std::optional<qint32> photo_height;
        
        /* @brief Optional. Pass True, if you require the user's full name to complete the order */
        std::optional<bool> need_name;
        
        /* @brief Optional. Pass True, if you require the user's phone number to complete the order */
        std::optional<bool> need_phone_number;
        
        /* @brief Optional. Pass True, if you require the user's email address to complete the order */
        std::optional<bool> need_email;
        
        /* @brief Optional. Pass True, if you require the user's shipping address to complete the order */
        std::optional<bool> need_shipping_address;
        
        /* @brief Optional. Pass True, if user's phone number should be sent to provider */
        std::optional<bool> send_phone_number_to_provider;
        
        /* @brief Optional. Pass True, if user's email address should be sent to provider */
        std::optional<bool> send_email_to_provider;
        
        /* @brief Optional. Pass True, if the final price depends on the shipping method */
        std::optional<bool> is_flexible;
    };
}

#endif // TELEGRAM_TYPES_INPUTINVOICEMESSAGECONTENT_H
