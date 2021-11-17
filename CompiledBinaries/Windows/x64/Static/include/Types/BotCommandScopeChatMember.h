#ifndef TELEGRAM_TYPES_BOTCOMMANDSCOPECHATMEMBER_H
#define TELEGRAM_TYPES_BOTCOMMANDSCOPECHATMEMBER_H

#include "Types/BotCommandScope.h"

#include <variant>

namespace Telegram
{
    /**
     *
     * @brief This struct represents the scope of bot commands, covering a specific member of a group or supergroup chat
     *
     */

    struct BotCommandScopeChatMember : public BotCommandScope
    {
        /** @brief Constructs BotCommandScopeChatMember object from parameters */
        BotCommandScopeChatMember(const std::variant<qint32, QString>& chat_id, const qint32& user_id);

        /** @brief JSON constructor. Constructs BotCommandScopeChatMember object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has key-value pairs such as "chat_id" = "...", "user_id" = "..." to construct correct object, otherwise if this pairs are missing empty object will be created */
        BotCommandScopeChatMember(const QJsonObject& jsonObject);

        /* @brief Returns true if BotCommandScopeChatMember is empty */
        virtual bool isEmpty() const override;

        /* @brief Returns BotCommandScopeChatMember in form of JSON object */
        virtual QJsonObject toObject() const override;

//** Fields **//

        /** @brief Scope type */
        const QString type = "chat_member";

        /** @brief Unique identifier for the target chat or username of the target supergroup (in the format @supergroupusername) */
        std::variant<qint32, QString> chat_id;

        /** @brief Unique identifier of the target user */
        qint32 user_id;
    };
}

#endif // TELEGRAM_TYPES_BOTCOMMANDSCOPECHATMEMBER_H
