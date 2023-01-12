#ifndef TELEGRAM_TYPES_CONTACT_H
#define TELEGRAM_TYPES_CONTACT_H

#include <compare>
#include <optional>

#include "qstring.h"
#include "qjsonobject.h"

namespace Telegram
{
    /**
     *
     * @brief This struct represents a phone contact
     *
     */

    struct Contact
    {
        /** @brief Default constructor. Constructs an empty Contact object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        Contact();

        /** @brief Constructs Contact object from parameters */
        Contact(const QString& phone_number,
                const QString& first_name,
                const std::optional<QString>& last_name = std::nullopt,
                const std::optional<qint64>& user_id = std::nullopt,
                const std::optional<QString>& vcard = std::nullopt);

        /** @brief JSON constructor. Constructs Contact object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has all key-value pairs related to Contact class fields. For example it should contain pairs such as "phone_number" = "...",
         * "first_name" = "..." and so on, otherwise fields related to missing pairs will be setted to some default values(0, "", std::nullopt) */
        Contact(const QJsonObject& json_object);


        /* @brief Returns Contact in form of JSON object. Returns empty QJsonObject if Contact is empty */
        QJsonObject toObject() const;

        /* @brief Returns true if Contact is empty */
        bool isEmpty() const;


        std::partial_ordering operator <=> (const Contact&) const = default;


//** Fields **//

        /** @brief Contact's phone number */
        QString phone_number;
        
        /** @brief Contact's first name */
        QString first_name;
        
        /** @brief Optional. Contact's last name */
        std::optional<QString> last_name;
        
        /** @brief Optional. Contact's user identifier in Telegram */
        std::optional<qint64> user_id;
        
        /** @brief Optional. Additional data about the contact in the form of a vCard */
        std::optional<QString> vcard;
    };
}

#endif // TELEGRAM_TYPES_CONTACT_H
