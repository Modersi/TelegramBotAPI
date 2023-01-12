#ifndef TELEGRAM_TYPES_POLLANSWER_H
#define TELEGRAM_TYPES_POLLANSWER_H

#include <compare>

#include "qvector.h"
#include "qstring.h"

#include "User.h"

namespace Telegram
{
    /**
     *
     * @brief This object represents an answer of a user in a non-anonymous poll
     *
     */

    struct PollAnswer
    {
        /** @brief Default constructor. Constructs an empty PollAnswer object
         *
         * All fields setted to 0, "", etc... */
        PollAnswer();

        /** @brief Constructs PollAnswer object from parameters */
        PollAnswer(const QString& poll_id,
                   const User& user,
                   const QVector<qint32>& option_ids);

        /** @brief JSON constructor. Constructs PollAnswer object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has all key-value pairs related to PollAnswer class fields. For example it should contain pairs such as "poll_id" = "...",
         * "user" = "..." and so on, otherwise fields related to missing pairs will be setted to some default values(0, "", std::nullopt) */
        PollAnswer(const QJsonObject& json_object);


        /* @brief Returns PollAnswer in form of JSON object. Returns empty QJsonObject if PollAnswer is empty */
        QJsonObject toObject() const;

        /* @brief Returns true if PollAnswer is empty */
        bool isEmpty() const;


        std::partial_ordering operator <=> (const PollAnswer&) const = default;


//** Fields **//

        /** @brief Unique poll identifier */
        QString poll_id;
        
        /** @brief The user, who changed the answer to the poll */
        User user;
        
        /** @brief 0-based identifiers of answer options, chosen by the user. May be empty if the user retracted their vote */
        QVector<qint32> option_ids;
    };
}

#endif // TELEGRAM_TYPES_POLLANSWER_H
