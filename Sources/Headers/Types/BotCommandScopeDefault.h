#ifndef TELEGRAM_TYPES_BOTCOMMANDSCOPEDEFAULT_H
#define TELEGRAM_TYPES_BOTCOMMANDSCOPEDEFAULT_H

#include "Types/BotCommandScope.h"

namespace Telegram
{
    /**
     *
     * @brief This struct represents the default scope of bot commands. Default commands are used if no commands with a narrower scope are specified for the user
     *
     */

    struct BotCommandScopeDefault : public BotCommandScope
    {
        /** @brief Constructs BotCommandScopeDefault object */
        BotCommandScopeDefault() {};


        /**  @brief Returns BotCommandScopeAllGroupChats in form of JSON object */
        inline virtual QJsonObject toObject() const override { return QJsonObject{ { "type", type } }; }

        /** @brief Returns true if BotCommandScopeAllGroupChats is empty */
        inline virtual bool isEmpty() const override { return false; };


        /** @brief Scope type */
        const QString type = "default";
    };
}

#endif // TELEGRAM_TYPES_BOTCOMMANDSCOPEDEFAULT_H
