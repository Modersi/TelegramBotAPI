#ifndef TELEGRAM_TYPES_CHATMEMBER_H
#define TELEGRAM_TYPES_CHATMEMBER_H

namespace Telegram
{
    /**
     *
     * @brief This struct contains information about one member of a chat. Currently, the following 6 types of chat members are supported:
     *  • ChatMemberOwner
     *  • ChatMemberAdministrator
     *  • ChatMemberMember
     *  • ChatMemberRestricted
     *  • ChatMemberLeft
     *  • ChatMemberBanned          
     *
     */

    struct ChatMember
    {
        /**  @brief Returns ChatMember in form of JSON object */
        virtual QJsonObject toObject() const = 0;

        /** @brief Returns true if ChatMember is empty */
        virtual bool isEmpty() const = 0;

        /** @brief Virtual destructor */
        virtual ~ChatMember() = default;
    };
}

#endif // TELEGRAM_TYPES_CHATMEMBER_H
