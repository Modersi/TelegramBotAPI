#ifndef TELEGRAM_TYPES_BOTCOMMANDSCOPEALLPRIVATECHATS_H
#define TELEGRAM_TYPES_BOTCOMMANDSCOPEALLPRIVATECHATS_H

#include <compare>

#include "qjsonobject.h"

#include "Types/BotCommandScope.h"

namespace Telegram
{
    /**
     *
     * @brief This struct represents a scope of bot commands, covering all private chats
     *
     */

    struct BotCommandScopeAllPrivateChats : public BotCommandScope
    {
        /** @brief Constructs BotCommandScopeAllPrivateChats object */
        BotCommandScopeAllPrivateChats() {};


        /**  @brief Returns BotCommandScopeAllPrivateChats in form of JSON object */
        inline virtual QJsonObject toObject() const override { return { { "type", "all_private_chats" } }; }

        /** @brief Returns true if BotCommandScopeAllPrivateChats is empty */
        inline virtual bool isEmpty() const override { return false; };

        /** @brief Returns type of the BotCommandScope */
        inline virtual Type getType() const override { return type; };


        std::partial_ordering operator <=> (const BotCommandScopeAllPrivateChats&) const = default;


        /** @brief Scope type */
        const Type type = Type::ALL_PRIVATE_CHATS;
    };
}

#endif // TELEGRAM_TYPES_BOTCOMMANDSCOPEALLPRIVATECHATS_H
