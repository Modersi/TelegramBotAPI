#ifndef TELEGRAM_TYPES_CHATMEMBER_H
#define TELEGRAM_TYPES_CHATMEMBER_H

#include "User.h"

namespace Telegram
{
    /**
     *
     * @brief This struct represent information about one member of a chat                   
     *
     */

    struct ChatMember
    {
        /** @brief Enum that represents all available status of chat member */
        enum class Status
        {
            UNINITIALIZED_VALUE,
            CREATOR,
            ADMINISTRARTOR,
            MEMBER,
            RESTRICTED,
            LEFT,
            KICKED
        };

        /** @brief Default constructor. Constructs an empty object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        ChatMember();

        /** @brief Constructs ChatMember object from parameters */
        ChatMember(const User& user,
                   const Status& status,
                   const std::optional<QString>& custom_title = std::nullopt,
                   const std::optional<bool>& is_anonymous = std::nullopt,
                   const std::optional<bool>& can_be_edited = std::nullopt,
                   const std::optional<bool>& can_manage_chat = std::nullopt,
                   const std::optional<bool>& can_post_messages = std::nullopt,
                   const std::optional<bool>& can_edit_messages = std::nullopt,
                   const std::optional<bool>& can_delete_messages = std::nullopt,
                   const std::optional<bool>& can_manage_voice_chats = std::nullopt,
                   const std::optional<bool>& can_restrict_members = std::nullopt,
                   const std::optional<bool>& can_promote_members = std::nullopt,
                   const std::optional<bool>& can_change_info = std::nullopt,
                   const std::optional<bool>& can_invite_users = std::nullopt,
                   const std::optional<bool>& can_pin_messages = std::nullopt,
                   const std::optional<bool>& is_member = std::nullopt,
                   const std::optional<bool>& can_send_messages = std::nullopt,
                   const std::optional<bool>& can_send_media_messages = std::nullopt,
                   const std::optional<bool>& can_send_polls = std::nullopt,
                   const std::optional<bool>& can_send_other_messages = std::nullopt,
                   const std::optional<bool>& can_add_web_page_previews = std::nullopt,
                   const std::optional<qint32>& until_date = std::nullopt);

        /** @brief JSON constructor. Constructs ChatMember object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has all key-value pairs related to ChatMember class fields. For example it should contain pairs such as "user" = "...",
         * "status" = "..." and so on, otherwise fields related to missing pairs will be setted to some default values(0, "", std::nullopt) */
        ChatMember(const QJsonObject& jsonObject);

        /* @brief Returns ChatMember in form of JSON object. Returns empty QJsonObject if ChatMember is empty */
        QJsonObject toObject() const;

        /* @brief Returns true if ChatMember is empty */
        bool isEmpty() const;

//** Fields **//

        /** @brief Information about the user */
        User user;
        
        /** @brief The member's status in the chat. Can be “creator”, “administrator”, “member”, “restricted”, “left” or “kicked” */
        Status status;
        
        /** @brief Optional. Owner and administrators only. Custom title for this user */
        std::optional<QString> custom_title;
        
        /** @brief Optional. Owner and administrators only. True, if the user's presence in the chat is hidden */
        std::optional<bool> is_anonymous;
        
        /** @brief Optional. Administrators only. True, if the bot is allowed to edit administrator privileges of that user */
        std::optional<bool> can_be_edited;
        
        /** @brief Optional. Administrators only. True, if the administrator can access the chat event log, chat statistics, message statistics in channels, see channel members, see anonymous administrators in supergroups and ignore slow mode. Implied by any other administrator privilege */
        std::optional<bool> can_manage_chat;
        
        /** @brief Optional. Administrators only. True, if the administrator can post in the channel; channels only */
        std::optional<bool> can_post_messages;
        
        /** @brief Optional. Administrators only. True, if the administrator can edit messages of other users and can pin messages; channels only */
        std::optional<bool> can_edit_messages;
        
        /** @brief Optional. Administrators only. True, if the administrator can delete messages of other users */
        std::optional<bool> can_delete_messages;
        
        /** @brief Optional. Administrators only. True, if the administrator can manage voice chats */
        std::optional<bool> can_manage_voice_chats;
        
        /** @brief Optional. Administrators only. True, if the administrator can restrict, ban or unban chat members */
        std::optional<bool> can_restrict_members;
        
        /** @brief Optional. Administrators only. True, if the administrator can add new administrators with a subset of their own privileges or demote administrators that he has promoted, directly or indirectly (promoted by administrators that were appointed by the user) */
        std::optional<bool> can_promote_members;
        
        /** @brief Optional. Administrators and restricted only. True, if the user is allowed to change the chat title, photo and other settings */
        std::optional<bool> can_change_info;
        
        /** @brief Optional. Administrators and restricted only. True, if the user is allowed to invite new users to the chat */
        std::optional<bool> can_invite_users;
        
        /** @brief Optional. Administrators and restricted only. True, if the user is allowed to pin messages; groups and supergroups only */
        std::optional<bool> can_pin_messages;
        
        /** @brief Optional. Restricted only. True, if the user is a member of the chat at the moment of the request */
        std::optional<bool> is_member;
        
        /** @brief Optional. Restricted only. True, if the user is allowed to send text messages, contacts, locations and venues */
        std::optional<bool> can_send_messages;
        
        /** @brief Optional. Restricted only. True, if the user is allowed to send audios, documents, photos, videos, video notes and voice notes */
        std::optional<bool> can_send_media_messages;
        
        /** @brief Optional. Restricted only. True, if the user is allowed to send polls */
        std::optional<bool> can_send_polls;
        
        /** @brief Optional. Restricted only. True, if the user is allowed to send animations, games, stickers and use inline bots */
        std::optional<bool> can_send_other_messages;
        
        /** @brief Optional. Restricted only. True, if the user is allowed to add web page previews to their messages */
        std::optional<bool> can_add_web_page_previews;
        
        /** @brief Optional. Restricted and kicked only. Date when restrictions will be lifted for this user; unix time */
        std::optional<qint32> until_date;
    };
}

#endif // TELEGRAM_TYPES_CHATMEMBER_H
