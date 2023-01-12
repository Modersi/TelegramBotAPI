#ifndef TELEGRAM_TYPES_CHATMEMBER_H
#define TELEGRAM_TYPES_CHATMEMBER_H

#include <compare>

#include "qmetaobject.h"
#include "qjsonobject.h"

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

    class ChatMember
    {
        Q_GADGET

    public:
        enum class Status {
            CREATOR,       // Represents a chat member that owns the chat and has all administrator privileges
            ADMINISTRATOR, // Represents a chat member that has some additional privileges
            MEMBER,        // Represents a chat member that has no additional privileges or restrictions
            RESTRICTED,    // Represents a chat member that is under certain restrictions in the chat. Supergroups only
            LEFT,          // Represents a chat member that isn't currently a member of the chat, but may join it themselves
            KICKED,        // Represents a chat member that was banned in the chat and can't return to the chat or view chat messages
            NULL_ENUMERATOR = -1
        };
        Q_ENUM(Status)


        /**  @brief Returns ChatMember in form of JSON object */
        virtual QJsonObject toObject() const = 0;

        /** @brief Returns true if ChatMember is empty */
        virtual bool isEmpty() const = 0;

        /** @brief Returns type of the ChatMember */
        virtual Status getStatus() const = 0;


        /** @brief Virtual destructor */
        virtual ~ChatMember() = default;
                     

        std::partial_ordering operator <=> (const ChatMember&) const = default;
    };
}

#include "ChatMemberAdministrator.h"
#include "ChatMemberBanned.h"
#include "ChatMemberLeft.h"
#include "ChatMemberMember.h"
#include "ChatMemberOwner.h"
#include "ChatMemberRestricted.h"
#include "ChatMemberUpdated.h"

#endif // TELEGRAM_TYPES_CHATMEMBER_H
