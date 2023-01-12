#ifndef TELEGRAM_TYPES_BOTCOMMANDSCOPEALLGROUPCHATS_H
#define TELEGRAM_TYPES_BOTCOMMANDSCOPEALLGROUPCHATS_H

#include <compare>

#include "qjsonobject.h"

#include "Types/BotCommandScope.h"

namespace Telegram
{
    /**
     *
     * @brief This struct represents a scope of bot commands, covering all group and supergroup chats
     *
     */

    struct BotCommandScopeAllGroupChats : public BotCommandScope
    {
        /** @brief Constructs BotCommandScopeAllGroupChats object */
        BotCommandScopeAllGroupChats() {};


        /**  @brief Returns BotCommandScopeAllGroupChats in form of JSON object */
        inline virtual QJsonObject toObject() const override { return { { "type", "all_group_chats" } }; }

        /** @brief Returns true if BotCommandScopeAllGroupChats is empty */
        inline virtual bool isEmpty() const override { return false; };

        /** @brief Returns type of the BotCommandScope */
        inline virtual Type getType() const override { return type; };


        std::partial_ordering operator <=> (const BotCommandScopeAllGroupChats&) const = default;


        /** @brief Scope type */
        const Type type = Type::ALL_GROUP_CHATS;
    };
}

#endif // TELEGRAM_TYPES_BOTCOMMANDSCOPEALLGROUPCHATS_H
