#ifndef TELEGRAM_TYPES_BOTCOMMANDSCOPEALLCHATADMINISTRATORS_H
#define TELEGRAM_TYPES_BOTCOMMANDSCOPEALLCHATADMINISTRATORS_H

#include "Types/BotCommandScope.h"

namespace Telegram
{
    /**
     *
     * @brief This struct represents the scope of bot commands, covering all group and supergroup chat administrators
     *
     */

    struct BotCommandScopeAllChatAdministrators : public BotCommandScope
    {
        /** @brief Constructs BotCommandScopeAllChatAdministrators object */
        BotCommandScopeAllChatAdministrators() {};


        /**  @brief Returns BotCommandScopeAllGroupChats in form of JSON object */
        inline virtual QJsonObject toObject() const override { return QJsonObject{ { "type", type } }; }

        /** @brief Returns true if BotCommandScopeAllGroupChats is empty */
        inline virtual bool isEmpty() const override { return false; };


        /** @brief Scope type */
        const QString type = "all_chat_administrators";
    };
}

#endif // TELEGRAM_TYPES_BOTCOMMANDSCOPEALLCHATADMINISTRATORS_H
