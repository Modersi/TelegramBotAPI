#ifndef TELEGRAM_TYPES_BOTCOMMANDSCOPEALLGROUPCHATS_H
#define TELEGRAM_TYPES_BOTCOMMANDSCOPEALLGROUPCHATS_H

#include "qstring.h"
class QJsonObject;

namespace Telegram
{
    /**
     *
     * @brief This struct represents the scope of bot commands, covering all group and supergroup chats
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

    struct BotCommandScopeAllGroupChats
    {
        /* @brief Returns BotCommandScopeAllGroupChats in form of JSON object */
        QJsonObject toObject() const;

        /** @brief Scope type */
        const QString type = "all_group_chats";
    };
}

#endif // TELEGRAM_TYPES_BOTCOMMANDSCOPEALLGROUPCHATS_H
