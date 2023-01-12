#ifndef TELEGRAM_TYPES_REPLYKEYBOARDREMOVE_H
#define TELEGRAM_TYPES_REPLYKEYBOARDREMOVE_H

#include <compare>
#include <optional>

#include "qjsonobject.h"

namespace Telegram
{
    /**
     *
     * @brief Upon receiving a message with this object, Telegram clients will remove the current custom keyboard and display the default letter-keyboard
     *
     * By default, custom keyboards are displayed until a new keyboard is sent by a bot. An exception is made for one-time keyboards
     * that are hidden immediately after the user presses a button (see [ReplyKeyboardMarkup](https://core.telegram.org/bots/api#replykeyboardmarkup))
     *
     */

    struct ReplyKeyboardRemove
    {
        /** @brief Constructs ReplyKeyboardRemove object from parameters */
        ReplyKeyboardRemove(const std::optional<bool>& selective = std::nullopt);

        /** @brief JSON constructor. Constructs ReplyKeyboardRemove object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has all key-value pairs related to ReplyKeyboardRemove class fields. For example it should contain pairs such as "text" = "...",
         * "request_contact" = "..." and so on, otherwise fields related to missing pairs will be setted to some default values(0, "", std::nullopt) */
        ReplyKeyboardRemove(const QJsonObject& json_object);


        /* @brief Returns ReplyKeyboardRemove in form of JSON object. Returns empty QJsonObject if ReplyKeyboardRemove is empty */
        QJsonObject toObject() const;

        /* @brief Returns true if ReplyKeyboardRemove is empty */
        bool isEmpty() const;


        std::partial_ordering operator <=> (const ReplyKeyboardRemove&) const = default;


//** Fields **//

        /** @brief Requests clients to remove the custom keyboard 
         * 
         * User will not be able to summon this keyboard; if you want to hide the keyboard from sight but keep it accessible, use one_time_keyboard in ReplyKeyboardMarkup */
        const bool remove_keyboard = true;

        /** @brief Optional. Use this parameter if you want to remove the keyboard for specific users only
         *
         * Targets: 1) users that are @mentioned in the text of the Message object; 2) if the bot's message is a reply (has reply_to_message_id), sender of the original message
         * > Example: A user votes in a poll, bot returns confirmation message in reply to the vote and removes the keyboard for that user, while still showing the keyboard with poll options to users who haven't voted yet */
        std::optional<bool> selective;
    };
}

#endif // TELEGRAM_TYPES_REPLYKEYBOARDREMOVE_H
