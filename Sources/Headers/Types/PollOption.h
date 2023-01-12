#ifndef TELEGRAM_TYPES_POLLOPTION_H
#define TELEGRAM_TYPES_POLLOPTION_H

#include <compare>

#include "qstring.h"
#include "qjsonobject.h"

namespace Telegram
{
    /**
     *
     * @brief This object contains information about one answer option in a poll
     *
     */

    struct PollOption
    {
        /** @brief Default constructor. Constructs an empty PollOption object
         *
         * All fields setted to 0, "", etc... */
        PollOption();

        /** @brief Constructs PollOption object from parameters */
        PollOption(const QString& text,
                   const qint32& voter_count);

        /** @brief JSON constructor. Constructs PollOption object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has key-value pair "text" = "...", "voterCount" = "..." to construct correct object,
         * otherwise empty PollOption object will be constructed */
        PollOption(const QJsonObject& json_object);


        /* @brief Returns PollOption in form of JSON object. Returns empty QJsonObject if PollOption is empty */
        QJsonObject toObject() const;

        /* @brief Returns true if PollOption is empty */
        bool isEmpty() const;


        std::partial_ordering operator <=> (const PollOption&) const = default;


//** Fields **//

        /** @brief Option text, 1-100 characters */
        QString text;

        /** @brief Number of users that voted for this option */
        qint32 voter_count;
    };
}

#endif // TELEGRAM_TYPES_POLLOPTION_H
