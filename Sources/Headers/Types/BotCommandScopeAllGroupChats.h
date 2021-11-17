#ifndef TELEGRAM_TYPES_BOTCOMMANDSCOPEALLGROUPCHATS_H
#define TELEGRAM_TYPES_BOTCOMMANDSCOPEALLGROUPCHATS_H

#include "Types/BotCommandScope.h"

namespace Telegram
{
    /**
     *
     * @brief This struct represents the scope of bot commands, covering all group and supergroup chats
     *
     */

    struct BotCommandScopeAllGroupChats : public BotCommandScope
    {
        /** @brief Constructs BotCommandScopeAllGroupChats object */
        BotCommandScopeAllGroupChats() {};


        /**  @brief Returns BotCommandScopeAllGroupChats in form of JSON object */
        inline virtual QJsonObject toObject() const override { return QJsonObject{ { "type", type } }; }

        /** @brief Returns true if BotCommandScopeAllGroupChats is empty */
        inline virtual bool isEmpty() const override { return false; };


        /** @brief Scope type */
        const QString type = "all_group_chats";
    };
}

#endif // TELEGRAM_TYPES_BOTCOMMANDSCOPEALLGROUPCHATS_H
