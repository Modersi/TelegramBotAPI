#ifndef TELEGRAM_TYPES_BOTCOMMANDSCOPECHATADMINISTRATORS_H
#define TELEGRAM_TYPES_BOTCOMMANDSCOPECHATADMINISTRATORS_H

#include <variant>

#include "qstring.h"
class QJsonObject;

namespace Telegram
{
    /**
     *
     * @brief This struct represents the scope of bot commands, covering all administrators of a specific group or supergroup chat
     *
     * The following algorithm is used to determine the list of commands for a particular user viewing the bot menu. The first list of commands which is set is returned:
     *
     * Commands in the chat with the bot:
     * • botCommandScopeChat + language_code
     * • botCommandScopeChat
     * • botCommandScopeAllPrivateChats + language_code
     * • botCommandScopeAllPrivateChats
     * • botCommandScopeDefault + language_code
     * • botCommandScopeDefault
     *
     * Commands in group and supergroup chats:
     * • botCommandScopeChatMember + language_code
     * • botCommandScopeChatMember
     * • botCommandScopeChatAdministrators + language_code (admins only)
     * • botCommandScopeChatAdministrators (admins only)
     * • botCommandScopeChat + language_code
     * • botCommandScopeChat
     * • botCommandScopeAllChatAdministrators + language_code (admins only)
     * • botCommandScopeAllChatAdministrators (admins only)
     * • botCommandScopeAllGroupChats + language_code
     * • botCommandScopeAllGroupChats
     * • botCommandScopeDefault + language_code
     * • botCommandScopeDefault
     *
     */

    struct BotCommandScopeChatAdministrators
    {
        /** @brief Constructs BotCommandScopeChatAdministrators object from parameters */
        BotCommandScopeChatAdministrators(const std::variant<qint32, QString>& chat_id);

        /** @brief JSON constructor. Constructs BotCommandScopeChatAdministrators object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has key-value pair "chat_id" = "..." to construct correct object, otherwise if this pair is missing empty object will be created */
        BotCommandScopeChatAdministrators(const QJsonObject& jsonObject);

        /* @brief Returns true if BotCommandScopeChatAdministrators is empty */
        bool isEmpty() const;

        /* @brief Returns BotCommandScopeChatAdministrators in form of JSON object */
        QJsonObject toObject() const;

//** Fields **//

        /** @brief Scope type */
        const QString type = "chat_administrators";

        /** @brief Unique identifier for the target chat or username of the target supergroup (in the format @supergroupusername) */
        std::variant<qint32, QString> chat_id;
    };
}

#endif // TELEGRAM_TYPES_BOTCOMMANDSCOPECHATADMINISTRATORS_H
