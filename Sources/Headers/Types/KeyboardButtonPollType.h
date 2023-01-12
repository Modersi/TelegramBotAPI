#ifndef TELEGRAM_TYPES_KEYBOARDBUTTONPOLLTYPE_H
#define TELEGRAM_TYPES_KEYBOARDBUTTONPOLLTYPE_H

#include <compare>
#include <optional>

#include "qjsonobject.h"

#include "Poll.h"

namespace Telegram
{
    /**
     *
     * @brief This object represents type of a poll, which is allowed to be created and sent when the corresponding button is pressed.
     *
     */

    struct KeyboardButtonPollType
    {
        /** @brief Constructs KeyboardButtonPollType object from parameters */
        KeyboardButtonPollType(const std::optional<Poll::Type>& type = std::nullopt);

        /** @brief JSON constructor. Constructs InlineKeyboardButton object from QJsonObject
        *
        * QJsonObject which is passed to constuctor has to has key-value pair "type" = "..." to construct correct object, otherwise empty KeyboardButtonPollType object will be constructed */
        KeyboardButtonPollType(const QJsonObject& json_object);


        /* @brief Returns KeyboardButtonPollType in form of JSON object. Returns empty QJsonObject if KeyboardButtonPollType is empty */
        QJsonObject toObject() const;

        /* @brief Returns true if KeyboardButtonPollType is empty */
        bool isEmpty() const;


        std::partial_ordering operator <=> (const KeyboardButtonPollType&) const = default;


//** Fields **//

        /** @brief Optional. If Poll::Type::QUIZ is passed, the user will be allowed to create only polls in the quiz mode. If Poll::Type::REGULAR is passed, only regular polls will be allowed. Otherwise, the user will be allowed to create a poll of any type */
        std::optional<Poll::Type> type;
    };
}

#endif // TELEGRAM_TYPES_KEYBOARDBUTTONPOLLTYPE_H
