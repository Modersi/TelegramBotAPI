#ifndef TELEGRAM_TYPES_BOTCOMMANDSCOPEDEFAULT_H
#define TELEGRAM_TYPES_BOTCOMMANDSCOPEDEFAULT_H

#include <compare>

#include "qjsonobject.h"

#include "Types/BotCommandScope.h"

namespace Telegram
{
    /**
     *
     * @brief This struct represents a default scope of bot commands. Default commands are used if no commands with a narrower scope are specified for the user
     *
     */

    struct BotCommandScopeDefault : public BotCommandScope
    {
        /** @brief Constructs BotCommandScopeDefault object */
        BotCommandScopeDefault() {};


        /**  @brief Returns BotCommandScopeAllGroupChats in form of JSON object */
        inline virtual QJsonObject toObject() const override { return { {"type", "default" }}; }

        /** @brief Returns true if BotCommandScopeAllGroupChats is empty */
        inline virtual bool isEmpty() const override { return false; };

        /** @brief Returns type of the BotCommandScope */
        inline virtual Type getType() const override { return type; };


        std::partial_ordering operator <=> (const BotCommandScopeDefault&) const = default;


        /** @brief Scope type */
        const Type type = Type::DEFAULT;
    };
}

#endif // TELEGRAM_TYPES_BOTCOMMANDSCOPEDEFAULT_H
