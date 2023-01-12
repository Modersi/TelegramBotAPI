#ifndef TELEGRAM_TYPES_ERROR_H
#define TELEGRAM_TYPES_ERROR_H

#include <compare>

#include "qstring.h"
#include "qjsonobject.h"

namespace Telegram
{
    /**
     *
     * @brief This class represents an occured error
     *
     */

    struct Error
    {
        /** @brief Default constructor. Constructs an empty object
         *
         * All fields setted to "", 0 */
        Error();

        /** @brief Constructs Error object from parameters */
        Error(const QString& description,
              const qint32& error_code);

        /** @brief JSON constructor. Constructs Error object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has key-value pairs such as "description" = "...", "error_code" = "..." to construct correct object, otherwise if this pairs are missing empty object will be created */
        Error(const QJsonObject& json_object);


        /* @brief Returns Error in form of JSON object. Returns empty QJsonObject if Error is empty */
        QJsonObject toObject() const;

        /* @brief Returns true if Error is empty */
        bool isEmpty() const;


        std::partial_ordering operator <=> (const Error&) const = default;


//** Fields **//

        /** @brief Description of occured error */
        QString description;

        /** @brief Code of occured error */
        qint32 error_code;
    };
}

#endif // TELEGRAM_TYPES_ERROR_H
