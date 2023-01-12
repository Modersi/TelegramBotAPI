#ifndef TELEGRAM_TYPES_REPLYKEYBOARDMARKUP_H
#define TELEGRAM_TYPES_REPLYKEYBOARDMARKUP_H

#include <compare>
#include <optional>

#include "qvector.h"
#include "qjsonobject.h"

#include "KeyboardButton.h"

namespace Telegram
{
    /**
     *
     * @brief This object represents a custom keyboard with reply options
     * 
     */

    struct ReplyKeyboardMarkup
    {
        /** @brief Default constructor. Constructs an empty ReplyKeyboardMarkup object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        ReplyKeyboardMarkup();

        /** @brief Constructs ReplyKeyboardMarkup object with initializer_lis t*/
        ReplyKeyboardMarkup(std::initializer_list<std::initializer_list<KeyboardButton>> keyboard,
                            const std::optional<bool>& resize_keyboard = std::nullopt,
                            const std::optional<bool>& one_time_keyboard = std::nullopt,
                            const std::optional<bool>& selective = std::nullopt);

        /** @brief Constructs ReplyKeyboardMarkup object from parameters */
        ReplyKeyboardMarkup(const QVector<QVector<KeyboardButton>>& keyboard,
                            const std::optional<bool>& resize_keyboard = std::nullopt,
                            const std::optional<bool>& one_time_keyboard = std::nullopt,
                            const std::optional<bool>& selective = std::nullopt);

        /** @brief JSON constructor. Constructs ReplyKeyboardMarkup object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has all key-value pairs related to ReplyKeyboardMarkup class fields. For example it should contain pairs such as "keyboard" = "...",
         * "resize_keyboard" = "..." and so on, otherwise fields related to missing pairs will be setted to some default values(0, "", std::nullopt) */
        ReplyKeyboardMarkup(const QJsonObject& json_object);


        /* @brief Returns ReplyKeyboardMarkup in form of JSON object. Returns empty QJsonObject if ReplyKeyboardMarkup is empty */
        QJsonObject toObject() const;

        /* @brief Returns true if ReplyKeyboardMarkup is empty */
        bool isEmpty() const;


        std::partial_ordering operator <=> (const ReplyKeyboardMarkup&) const = default;


//** Fields **//

        /** @brief Array of button rows, each represented by an Array of KeyboardButton objects */
        QVector<QVector<KeyboardButton>> keyboard;
        
        /** @brief Optional. Requests clients to resize the keyboard vertically for optimal fit(e.g., make the keyboard smaller if there are just two rows of buttons)
         * 
         * Defaults to false, in which case the custom keyboard is always of the same height as the app's standard keyboard */
        std::optional<bool> resize_keyboard;
        
        /** @brief Optional. Requests clients to hide the keyboard as soon as it's been used
         *
         * The keyboard will still be available, but clients will automatically display the usual letter-keyboard in the chat – the user can press a special button in the input field to see the custom keyboard again. Defaults to false */
        std::optional<bool> one_time_keyboard;
        
        /** @brief Optional. Use this parameter if you want to show the keyboard to specific users only 
         *
         * Targets: 1) users that are @mentioned in the text of the Message object; 2) if the bot's message is a reply (has reply_to_message_id), sender of the original message
         * > Example: A user requests to change the bot's language, bot replies to the request with a keyboard to select the new language. Other users in the group don't see the keyboard */
        std::optional<bool> selective;
    };
}

#endif // TELEGRAM_TYPES_REPLYKEYBOARDMARKUP_H
