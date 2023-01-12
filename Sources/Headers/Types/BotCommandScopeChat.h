#ifndef TELEGRAM_TYPES_BOTCOMMANDSCOPECHAT_H
#define TELEGRAM_TYPES_BOTCOMMANDSCOPECHAT_H

#include <compare>
#include <variant>

#include "qjsonobject.h"
#include "qstring.h"

#include "Types/BotCommandScope.h"

namespace Telegram
{
    /**
     *
     * @brief This struct represents a scope of bot commands, covering a specific chat
     *
     */

    struct BotCommandScopeChat : public BotCommandScope
    {
        /** @brief Constructs BotCommandScopeChat object from parameters */
        BotCommandScopeChat(const std::variant<qint32, QString>& chat_id);

        /** @brief JSON constructor. Constructs BotCommandScopeChat object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has key-value pair "chat_id" = "..." to construct correct object, otherwise if this pair is missing empty object will be created */
        BotCommandScopeChat(const QJsonObject& json_object);


        /* @brief Returns true if BotCommandScopeChat is empty */
        virtual bool isEmpty() const override;

        /* @brief Returns BotCommandScopeChat in form of JSON object */
        virtual QJsonObject toObject() const override;

        /** @brief Returns type of the BotCommandScope */
        virtual Type getType() const override;


        std::partial_ordering operator <=> (const BotCommandScopeChat&) const = default;


//** Fields **//

        /** @brief Scope type */
        const Type type = Type::CHAT;

        /** @brief Unique identifier for the target chat or username of the target supergroup (in the format @supergroupusername) */
        std::variant<qint32, QString> chat_id;
    };
}

#endif // TELEGRAM_TYPES_BOTCOMMANDSCOPECHAT_H
