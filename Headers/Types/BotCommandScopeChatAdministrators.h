#ifndef TELEGRAM_TYPES_BOTCOMMANDSCOPECHATADMINISTRATORS_H
#define TELEGRAM_TYPES_BOTCOMMANDSCOPECHATADMINISTRATORS_H

#include "Types/BotCommandScope.h"

#include <variant>

namespace Telegram
{
    /**
     *
     * @brief This struct represents the scope of bot commands, covering all administrators of a specific group or supergroup chat
     *
     *
     */

    struct BotCommandScopeChatAdministrators : public BotCommandScope
    {
        /** @brief Constructs BotCommandScopeChatAdministrators object from parameters */
        BotCommandScopeChatAdministrators(const std::variant<qint32, QString>& chat_id);

        /** @brief JSON constructor. Constructs BotCommandScopeChatAdministrators object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has key-value pair "chat_id" = "..." to construct correct object, otherwise if this pair is missing empty object will be created */
        BotCommandScopeChatAdministrators(const QJsonObject& jsonObject);

        /* @brief Returns true if BotCommandScopeChatAdministrators is empty */
        virtual bool isEmpty() const override;

        /* @brief Returns BotCommandScopeChatAdministrators in form of JSON object */
        virtual QJsonObject toObject() const override;

//** Fields **//

        /** @brief Scope type */
        const QString type = "chat_administrators";

        /** @brief Unique identifier for the target chat or username of the target supergroup (in the format @supergroupusername) */
        std::variant<qint32, QString> chat_id;
    };
}

#endif // TELEGRAM_TYPES_BOTCOMMANDSCOPECHATADMINISTRATORS_H
