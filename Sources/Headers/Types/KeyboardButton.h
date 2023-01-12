#ifndef TELEGRAM_TYPES_KEYBOARDBUTTON_H
#define TELEGRAM_TYPES_KEYBOARDBUTTON_H

#include <compare>
#include <optional>

#include "qstring.h"
#include "qjsonobject.h"

#include "KeyboardButtonPollType.h"

namespace Telegram
{
    /**
     *
     * @brief This struct represents one button of the reply keyboard
     * 
     * For simple text buttons String can be used instead of this object to specify text of the button. Optional fields request_contact, request_location, and request_poll are mutually exclusive
     *
     * > Note: request_contact and request_location options will only work in Telegram versions released after 9 April, 2016. Older clients will display unsupported message
     * > Note: request_poll option will only work in Telegram versions released after 23 January, 2020. Older clients will display unsupported message
     * 
     */

    struct KeyboardButton
    {
        /** @brief Default constructor. Constructs an empty KeyboardButton object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        KeyboardButton();

        /** @brief Constructs KeyboardButton object from parameters */
        KeyboardButton(const QString& text,
                       const std::optional<bool>& request_contact = std::nullopt,
                       const std::optional<bool>& request_location = std::nullopt,
                       const std::optional<KeyboardButtonPollType>& request_poll = std::nullopt);

        /** @brief JSON constructor. Constructs KeyboardButton object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has all key-value pairs related to KeyboardButton class fields. For example it should contain pairs such as "text" = "...",
         * "request_contact" = "..." and so on, otherwise fields related to missing pairs will be setted to some default values(0, "", std::nullopt) */
        KeyboardButton(const QJsonObject& json_object);


        /* @brief Returns KeyboardButton in form of JSON object. Returns empty QJsonObject if KeyboardButton is empty */
        QJsonObject toObject() const;

        /* @brief Returns true if KeyboardButton is empty */
        bool isEmpty() const;


        std::partial_ordering operator <=> (const KeyboardButton&) const = default;


//** Fields **//

        /** @brief Text of the button. If none of the optional fields are used, it will be sent as a message when the button is pressed */
        QString text;

        /** @brief Optional. True, the user's phone number will be sent as a contact when the button is pressed. Available in private chats only */
        std::optional<bool> request_contact;

        /** @brief Optional. True, the user's current location will be sent when the button is pressed. Available in private chats only */
        std::optional<bool> request_location;

        /** @brief Optional. If specified, the user will be asked to create a poll and send it to the bot when the button is pressed. Available in private chats only */
        std::optional<KeyboardButtonPollType> request_poll;
    };
}

#endif // TELEGRAM_TYPES_KEYBOARDBUTTON_H
