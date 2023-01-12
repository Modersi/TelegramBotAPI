#ifndef TELEGRAM_TYPES_CHATMEMBERRESTRICTED_H
#define TELEGRAM_TYPES_CHATMEMBERRESTRICTED_H

#include <compare>

#include "qjsonobject.h"

#include "User.h"
#include "ChatMember.h"

namespace Telegram
{
    /**
     *
     * @brief This struct represents a chat member that is under certain restrictions in the chat. Supergroups only
     *
     */

    struct ChatMemberRestricted : public ChatMember
    {
        /** @brief Default constructor. Constructs an empty object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        ChatMemberRestricted();

        /** @brief Constructs ChatMemberRestricted object from parameters */
        ChatMemberRestricted(const User& user,
                             const bool& is_member,
                             const bool& can_change_info,
                             const bool& can_invite_users,
                             const bool& can_pin_messages,
                             const bool& can_send_messages,
                             const bool& can_send_media_messages,
                             const bool& can_send_polls,
                             const bool& can_send_other_messages,
                             const bool& can_add_web_page_previews,
                             const qint32& until_date);

        /** @brief JSON constructor. Constructs ChatMemberRestricted object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has all key-value pairs related to ChatMemberRestricted class fields. For example it should contain pairs such as "user" = "...",
         * "status" = "..." and so on, otherwise fields related to missing pairs will be setted to some default values(0, "", std::nullopt) */
        ChatMemberRestricted(const QJsonObject& json_object);


        /* @brief Returns ChatMemberRestricted in form of JSON object. Returns empty QJsonObject if ChatMemberRestricted is empty */
        virtual QJsonObject toObject() const override;

        /* @brief Returns true if ChatMemberRestricted is empty */
        virtual bool isEmpty() const override;

        /** @brief Returns status of the ChatMember */
        virtual Status getStatus() const override;


        std::partial_ordering operator <=> (const ChatMemberRestricted&) const = default;


//** Fields **//

        /** @brief The member's status in the chat, always “restricted” */
        const Status status = Status::RESTRICTED;

        /** @brief Information about the user */
        User user;

        /** @brief True, if the user is a member of the chat at the moment of the request */
        bool is_member;

        /** @brief True, if the user is allowed to change the chat title, photo and other settings */
        bool can_change_info;

        /** @brief True, if the user is allowed to invite new users to the chat */
        bool can_invite_users;

        /** @brief True, if the user is allowed to pin messages; groups and supergroups only */
        bool can_pin_messages;

        /** @brief True, if the user is allowed to send text messages, contacts, locations and venues */
        bool can_send_messages;

        /** @brief True, if the user is allowed to send audios, documents, photos, videos, video notes and voice notes */
        bool can_send_media_messages;

        /** @brief True, if the user is allowed to send polls */
        bool can_send_polls;

        /** @brief True, if the user is allowed to send animations, games, stickers and use inline bots */
        bool can_send_other_messages;

        /** @brief True, if the user is allowed to add web page previews to their messages */
        bool can_add_web_page_previews;

        /** @brief Date when restrictions will be lifted for this user; unix time. If 0, then the user is restricted forever */
        qint32 until_date;
    };
}

#endif // TELEGRAM_TYPES_CHATMEMBERRESTRICTED_H
