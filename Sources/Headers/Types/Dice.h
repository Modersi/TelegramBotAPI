#ifndef TELEGRAM_TYPES_DICE_H
#define TELEGRAM_TYPES_DICE_H

#include <compare>

#include "qstring.h"
#include "qjsonobject.h"

namespace Telegram
{
    /**
     *
     * @brief This struct represents an animated emoji that displays a random value
     *
     */

    struct Dice
    {
        /** @brief Default constructor. Constructs an empty Dice object
         *
         * All fields setted to 0 or "" */
        Dice();

        /** @brief Constructs Dice object from parameters */
        Dice(const QString& emoji,
             const qint32&  value);

        /** @brief JSON constructor. Constructs Dice object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has key-value pairs "emoji" = "..." and "value" = "..." to construct correct object,
         * otherwise fields related to missing pairs will be setted to some default values(0, "") */
        Dice(const QJsonObject& json_object);


        /* @brief Returns Dice in form of JSON object. Returns empty QJsonObject if Dice is empty */
        QJsonObject toObject() const;

        /* @brief Returns true if Dice is empty */
        bool isEmpty() const;


        std::partial_ordering operator <=> (const Dice&) const = default;


//** Fields **//

        /** @brief Emoji on which the dice throw animation is based */
        QString emoji;
        
        /** @brief Value of the dice
         * 
         *  1-6 for “🎲” (dice) and “🎯”(darts throw) base emoji, 1-5 for “🏀”(ball throw) base emoji */
        qint32 value;
    };
}

#endif // TELEGRAM_TYPES_DICE_H
