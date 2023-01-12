#ifndef TELEGRAM_TYPES_BOTCOMMANDSCOPEALLCHATADMINISTRATORS_H
#define TELEGRAM_TYPES_BOTCOMMANDSCOPEALLCHATADMINISTRATORS_H

#include <compare>

#include "qjsonobject.h"

#include "Types/BotCommandScope.h"

namespace Telegram
{
    /**
     *
     * @brief This struct represents a scope of bot commands, covering all group and supergroup chat administrators
     *
     */

    struct BotCommandScopeAllChatAdministrators : public BotCommandScope
    {
        /** @brief Constructs BotCommandScopeAllChatAdministrators object */
        BotCommandScopeAllChatAdministrators() {};


        /**  @brief Returns BotCommandScopeAllGroupChats in form of JSON object */
        inline virtual QJsonObject toObject() const override { return { { "type", "all_chat_administrators" } }; }

        /** @brief Returns true if BotCommandScopeAllGroupChats is empty */
        inline virtual bool isEmpty() const override { return false; };

        /** @brief Returns type of the BotCommandScope */
        inline virtual Type getType() const override { return type; };


        std::partial_ordering operator <=> (const BotCommandScopeAllChatAdministrators&) const = default;


        /** @brief Scope type */
        const Type type = Type::ALL_CHAT_ADMINISTRATORS;
    };
}

#endif // TELEGRAM_TYPES_BOTCOMMANDSCOPEALLCHATADMINISTRATORS_H
