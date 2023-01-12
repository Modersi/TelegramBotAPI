#ifndef TELEGRAM_TYPES_FORCEREPLY_H
#define TELEGRAM_TYPES_FORCEREPLY_H

#include <compare>
#include <optional>

#include "qstring.h"
#include "qjsonobject.h"

namespace Telegram
{
    /**
     *
     * @brief This class represents a Force Reply
     *
     * Upon receiving a message with this object, Telegram clients will display a reply interface to the user (act as if the user has selected the bot's message and tapped 'Reply').
     * This can be extremely useful if you want to create user-friendly step-by-step interfaces without having to sacrifice [privacy mode](https://core.telegram.org/bots#privacy-mode)
     * 
     * > **Example:** A [poll bot](https://t.me/PollBot) for groups runs in privacy mode (only receives commands, replies to its messages and mentions). There could be two ways to create a new poll:
     * > - Explain the user how to send a command with parameters (e.g. /newpoll question answer1 answer2). May be appealing for hardcore users but lacks modern day polish.
     * > - Guide the user through a step-by-step process. 'Please send me your question', 'Cool, now let's add the first answer option', 'Great. Keep adding answer options, then send /done when you're ready'.
     * >
     * > The last option is definitely more attractive. And if you use ForceReply in your bot's questions, it will receive the user's answers even if it only receives replies, commands and mentions — without any extra work for the user
     * 
     */

    struct ForceReply
    {
        /** @brief Constructs ForceReply object from parameters */
        ForceReply(const std::optional<QString>& input_field_placeholder = std::nullopt, const std::optional<bool>& selective = std::nullopt);

        /** @brief JSON constructor. Constructs ForceReply object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has key-value pair "selective" = ..., "input_field_placeholder" = ... otherwise this field will be setted to std::nullopt */
        ForceReply(const QJsonObject& json_object);


        /* @brief Returns ForceReply in form of JSON object */
        QJsonObject toObject() const;

        /* @brief Returns true if ForceReply is empty */
        bool isEmpty() const;


        std::partial_ordering operator <=> (const ForceReply&) const = default;


//** Fields **//

        /** @brief Shows reply interface to the user, as if they manually selected the bot's message and tapped 'Reply' */
        const bool force_reply = true;

        /** @brief Optional. The placeholder to be shown in the input field when the reply is active; 1-64 characters */
        std::optional<QString> input_field_placeholder;

        /**@brief Optional. Use this parameter if you want to force reply from specific users only
         * 
         * Targets: 1) users that are @mentioned in the text of the Message object; 2) if the bot's message is a reply (has replyToMessageId), sender of the original message */
        std::optional<bool> selective;
    };
}

#endif // TELEGRAM_TYPES_FORCEREPLY_H
