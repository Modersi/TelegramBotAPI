#ifndef TELEGRAM_TYPES_BOTCOMMANDSCOPECHATADMINISTRATORS_H
#define TELEGRAM_TYPES_BOTCOMMANDSCOPECHATADMINISTRATORS_H

#include <variant>
#include <compare>

#include "qjsonobject.h"
#include "qstring.h"

#include "Types/BotCommandScope.h"

namespace Telegram
{
    /**
     *
     * @brief This struct represents a scope of bot commands, covering all administrators of a specific group or supergroup chat
     *
     */

    struct BotCommandScopeChatAdministrators : public BotCommandScope
    {
        /** @brief Constructs BotCommandScopeChatAdministrators object from parameters */
        BotCommandScopeChatAdministrators(const std::variant<qint32, QString>& chat_id);

        /** @brief JSON constructor. Constructs BotCommandScopeChatAdministrators object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has key-value pair "chat_id" = "..." to construct correct object, otherwise if this pair is missing empty object will be created */
        BotCommandScopeChatAdministrators(const QJsonObject& json_object);


        /* @brief Returns true if BotCommandScopeChatAdministrators is empty */
        virtual bool isEmpty() const override;

        /* @brief Returns BotCommandScopeChatAdministrators in form of JSON object */
        virtual QJsonObject toObject() const override;

        /** @brief Returns type of the BotCommandScope */
        virtual Type getType() const override;


        std::partial_ordering operator <=> (const BotCommandScopeChatAdministrators&) const = default;


//** Fields **//

        /** @brief Scope type */
        const Type type = Type::CHAT_ADMINISTRATORS;

        /** @brief Unique identifier for the target chat or username of the target supergroup (in the format @supergroupusername) */
        std::variant<qint32, QString> chat_id;
    };
}

#endif // TELEGRAM_TYPES_BOTCOMMANDSCOPECHATADMINISTRATORS_H
