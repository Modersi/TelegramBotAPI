#ifndef TELEGRAM_TYPES_BOTCOMMANDSCOPE_H
#define TELEGRAM_TYPES_BOTCOMMANDSCOPE_H

#include "qstring.h"
#include "qjsonobject.h"

namespace Telegram
{
    /**
    *
    * @brief This struct represents the scope to which bot commands are applied. This is a base struct for all BotCommandScopes listed below
    * 
    *   Currently, the following 7 scopes are supported:
    *   • BotCommandScopeDefault
    *   • BotCommandScopeAllPrivateChats
    *   • BotCommandScopeAllGroupChats
    *   • BotCommandScopeAllChatAdministrators
    *   • BotCommandScopeChat
    *   • BotCommandScopeChatAdministrators
    *   • BotCommandScopeChatMember
    * 
    *   ** Determining list of commands **
    *   The following algorithm is used to determine the list of commands for a particular user viewing the bot menu. The first list of commands which is set is returned:
    *   
    *   Commands in the chat with the bot:
    *   • botCommandScopeChat + language_code
    *   • botCommandScopeChat
    *   • botCommandScopeAllPrivateChats + language_code
    *   • botCommandScopeAllPrivateChats
    *   • botCommandScopeDefault + language_code
    *   • botCommandScopeDefault
    * 
    *   Commands in group and supergroup chats:
    *   • botCommandScopeChatMember + language_code
    *   • botCommandScopeChatMember
    *   • botCommandScopeChatAdministrators + language_code (admins only)
    *   • botCommandScopeChatAdministrators (admins only)
    *   • botCommandScopeChat + language_code
    *   • botCommandScopeChat
    *   • botCommandScopeAllChatAdministrators + language_code (admins only)
    *   • botCommandScopeAllChatAdministrators (admins only)
    *   • botCommandScopeAllGroupChats + language_code
    *   • botCommandScopeAllGroupChats
    *   • botCommandScopeDefault + language_code
    *   • botCommandScopeDefault
    * 
    */

    struct BotCommandScope
    {
        /**  @brief Returns BotCommandScope in form of JSON object */
        virtual QJsonObject toObject() const = 0;

        /** @brief Returns true if BotCommandScope is empty */
        virtual bool isEmpty() const = 0;

        /** @brief Virtual destructor */
        virtual ~BotCommandScope() = default;
    };
}

#endif // TELEGRAM_TYPES_BOTCOMMANDSCOPE_H
