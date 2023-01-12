#ifndef TELEGRAM_TYPES_CHATMEMBERADMINISTRATOR_H
#define TELEGRAM_TYPES_CHATMEMBERADMINISTRATOR_H

#include <compare>
#include <optional>

#include "qstring.h"
#include "qjsonobject.h"

#include "User.h"
#include "ChatMember.h"

namespace Telegram
{
    /**
     *
     * @brief This struct represents a chat member that has some additional privileges
     *
     */

    struct ChatMemberAdministrator : public ChatMember
    {
        /** @brief Default constructor. Constructs an empty object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        ChatMemberAdministrator();

        /** @brief Constructs ChatMemberAdministrator object from parameters */
        ChatMemberAdministrator(const User& user,
                                const bool& can_be_edited,
                                const bool& is_anonymous,
                                const bool& can_manage_chat,
                                const bool& can_delete_messages,
                                const bool& can_manage_voice_chats,
                                const bool& can_restrict_members,
                                const bool& can_promote_members,
                                const bool& can_change_info,
                                const bool& can_invite_users,
                                const std::optional<bool>& can_post_messages = std::nullopt,
                                const std::optional<bool>& can_edit_messages = std::nullopt,
                                const std::optional<bool>& can_pin_messages = std::nullopt,
                                const std::optional<QString>& custom_title = std::nullopt);

        /** @brief JSON constructor. Constructs ChatMemberAdministrator object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has all key-value pairs related to ChatMemberAdministrator class fields. For example it should contain pairs such as "user" = "...",
         * "can_be_edited" = "..." and so on, otherwise fields related to missing pairs will be setted to some default values(0, "", std::nullopt) */
        ChatMemberAdministrator(const QJsonObject& json_object);


        /* @brief Returns ChatMemberAdministrator in form of JSON object. Returns empty QJsonObject if ChatMemberAdministrator is empty */
        virtual QJsonObject toObject() const override;

        /* @brief Returns true if ChatMemberAdministrator is empty */
        virtual bool isEmpty() const override;

        /** @brief Returns status of the ChatMember */
        virtual Status getStatus() const override;


        std::partial_ordering operator <=> (const ChatMemberAdministrator&) const = default;

//** Fields **//

        /** @brief The member's status in the chat, always "administrator" */
        const Status status = Status::ADMINISTRATOR;

        /** @brief Information about the user */
        User user;

        /** @brief True, if the bot is allowed to edit administrator privileges of that user */
        bool can_be_edited;
        
        /** @brief True, if the user's presence in the chat is hidden */
        bool is_anonymous;
        
        /** @brief True, if the administrator can access the chat event log, chat statistics, message statistics in channels, see channel members, see anonymous administrators in supergroups and ignore slow mode. Implied by any other administrator privilege */
        bool can_manage_chat;
        
        /** @brief True, if the administrator can delete messages of other users */
        bool can_delete_messages;

        /** @brief Optional. True, if the administrator can manage voice chats */
        bool can_manage_voice_chats;

        /** @brief Optional. True, if the administrator can restrict, ban or unban chat members */
        bool can_restrict_members;

        /** @brief Optional. True, if the administrator can add new administrators with a subset of their own privileges or demote administrators that he has promoted, directly or indirectly (promoted by administrators that were appointed by the user) */
        bool can_promote_members;

        /** @brief Optional. True, if the user is allowed to change the chat title, photo and other settings */
        bool can_change_info;
        
        /** @brief Optional. True, if the user is allowed to invite new users to the chat */
        bool can_invite_users;
        
        /** @brief Optional. True, if the administrator can post in the channel; channels only */
        std::optional<bool> can_post_messages;

        /** @brief Optional. True, if the administrator can edit messages of other users and can pin messages; channels only */
        std::optional<bool> can_edit_messages;
        
        /** @brief Optional. Administrators and restricted only. True, if the user is allowed to pin messages; groups and supergroups only */
        std::optional<bool> can_pin_messages;
        
        /** @brief Optional. Custom title for this user */
        std::optional<QString> custom_title;
    };
}

#endif // TELEGRAM_TYPES_CHATMEMBERADMINISTRATOR_H
