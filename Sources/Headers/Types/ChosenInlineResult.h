#ifndef TELEGRAM_TYPES_CHOSENINLINERESULT_H
#define TELEGRAM_TYPES_CHOSENINLINERESULT_H

#include <optional>
#include <compare>

#include "qstring.h"
#include "qjsonobject.h"

#include "Types/User.h"
#include "Types/Location.h"

namespace Telegram
{
    /**
     *
     * @brief Represents a result of an inline query that was chosen by the user and sent to their chat partner
     *
     * > Note: It is necessary to enable inline feedback via @Botfather in order to receive these objects in updates
     * 
     */

    struct ChosenInlineResult
    {
        /** @brief Default constructor. Constructs an empty ChosenInlineResult object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        ChosenInlineResult();

        /** @brief Constructs ChosenInlineResult object from parameters */
        ChosenInlineResult(const QString& result_id,
                           const User& from,
                           const QString& query,
                           const std::optional<Location>& location = std::nullopt,
                           const std::optional<QString>& inline_message_id = std::nullopt);

        /** @brief JSON constructor. Constructs ChosenInlineResult object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has all key-value pairs related to ChosenInlineResult class fields. For example it should contain pairs such as "result_id" = "...",
         * "from" = "..." and so on, otherwise fields related to missing pairs will be setted to some default values(0, "", std::nullopt) */
        ChosenInlineResult(const QJsonObject& json_object);


        /* @brief Returns ChosenInlineResult in form of JSON object. Returns empty QJsonObject if ChosenInlineResult is empty */
        QJsonObject toObject() const;

        /* @brief Returns true if ChosenInlineResult is empty */
        bool isEmpty() const;


        std::partial_ordering operator <=> (const ChosenInlineResult&) const = default;


//** Fields **//

        /* @brief The unique identifier for the result that was chosen */
        QString result_id;

        /* @brief The user that chose the result */
        User from;
        
        /* @brief The query that was used to obtain the result */
        QString query;

        /* @brief Optional. Sender location, only for bots that require user location */
        std::optional<Location> location;

        /* @brief Optional. Identifier of the sent inline message. Available only if there is an inline keyboard attached to the message. Will be also received in callback queries and can be used to edit the message */
        std::optional<QString> inline_message_id;

    };
}

#endif // TELEGRAM_TYPES_CHOSENINLINERESULT_H
