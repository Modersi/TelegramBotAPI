#ifndef TELEGRAM_TYPES_BOTCOMMANDSCOPEALLPRIVATECHATS_H
#define TELEGRAM_TYPES_BOTCOMMANDSCOPEALLPRIVATECHATS_H

#include "Types/BotCommandScope.h"

namespace Telegram
{
    /**
     *
     * @brief This struct represents the scope of bot commands, covering all private chats
     *
     */

    struct BotCommandScopeAllPrivateChats : public BotCommandScope
    {
        /** @brief Constructs BotCommandScopeAllPrivateChats object */
        BotCommandScopeAllPrivateChats() {};


        /**  @brief Returns BotCommandScopeAllPrivateChats in form of JSON object */
        inline virtual QJsonObject toObject() const override { return QJsonObject{ { "type", type } }; }

        /** @brief Returns true if BotCommandScopeAllPrivateChats is empty */
        inline virtual bool isEmpty() const override { return false; };


        /** @brief Scope type */
        const QString type = "all_private_chats";
    };
}

#endif // TELEGRAM_TYPES_BOTCOMMANDSCOPEALLPRIVATECHATS_H
