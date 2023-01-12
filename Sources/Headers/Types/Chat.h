#ifndef TELEGRAM_TYPES_CHAT_H
#define TELEGRAM_TYPES_CHAT_H

#include <compare>
#include <optional>
#include <memory>

#include "qmetaobject.h"
#include "qstring.h"
#include "qjsonobject.h"

namespace Telegram { class Message; }
#include "ChatPhoto.h"
#include "ChatPermissions.h"
#include "ChatLocation.h"

namespace Telegram
{
    /**
     *
     * @brief This structure represents a Chat
     *
     */

    class Chat
    {
        Q_GADGET

    public:
        /** @brief Enum that represents all available types of chat */
        enum class Type {
            PRIVATE,
            GROUP,
            SUPERGROUP,
            CHANNEL,
            NULL_ENUMERATOR = -1
        };
        Q_ENUM(Type)


        /** @brief Default constructor. Constructs an empty object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        Chat();

        /** @brief Constructs Chat object from parameters */
        Chat(const qint64& id,
             const Type& type,
             const std::optional<QString>& title = std::nullopt,
             const std::optional<QString>& username = std::nullopt,
             const std::optional<QString>& first_name = std::nullopt,
             const std::optional<QString>& last_name = std::nullopt,
             const std::optional<ChatPhoto>& photo = std::nullopt,
             const std::optional<QString>& bio = std::nullopt,
             const std::optional<QString>& description = std::nullopt,
             const std::optional<QString>& invite_link = std::nullopt,
             const std::optional<std::shared_ptr<Message>>& pinned_message = std::nullopt,
             const std::optional<ChatPermissions>& permissions = std::nullopt,
             const std::optional<qint32>& slow_mode_delay = std::nullopt,
             const std::optional<qint32>& message_auto_delete_time = std::nullopt,
             const std::optional<QString>& sticker_set_name = std::nullopt,
             const std::optional<bool>& can_set_sticker_set = std::nullopt,
             const std::optional<qint64>& linked_chat_id = std::nullopt,
             const std::optional<ChatLocation>& location = std::nullopt);

        /** @brief JSON constructor. Constructs Chat object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has all key-value pairs related to Chat class fields. For example it should contain pairs such as "id" = "...",
         * "type" = "..." and so on, otherwise fields related to missing pairs will be setted to some default values(0, "", std::nullopt) */
        Chat(const QJsonObject& json_object);


        /* @brief Returns Chat in form of JSON object. Returns empty QJsonObject if Chat is empty */
        QJsonObject toObject() const;

        /* @brief Returns true if Chat is empty */
        bool isEmpty() const;


        std::partial_ordering operator <=> (const Chat&) const = default;


//** Fields **//

        /** @brief Unique identifier for this chat */
        qint64 id;
        
        /** @brief Type of chat, can be either "private", "group", "supergroup" or "channel" */
        Type type;
        
        /** @brief Optional. Title, for supergroups, channels and group chats */
        std::optional<QString> title;
        
        /** @brief Optional. Username, for private chats, supergroupsand channels if available */
        std::optional<QString> username;
        
        /** @brief Optional. First name of the other party in a private chat */
        std::optional<QString> first_name;

        /** @brief Optional. Last name of the other party in a private chat */
        std::optional<QString> last_name;
        
        /** @brief Optional. Chat photo. Returned only in getChat */
        std::optional<ChatPhoto> photo;
        
        /** @brief Optional. Bio of the other party in a private chat. Returned only in getChat */
        std::optional<QString> bio;
        
        /** @brief Optional. Description, for groups, supergroups and channel chats. Returned only in getChat */
        std::optional<QString> description;
        
        /** @brief Optional. Primary invite link, for groups, supergroups and channel chats. Returned only in getChat */
        std::optional<QString> invite_link;
        
        /** @brief Optional. The most recent pinned message(by sending date). Returned only in getChat */
        std::optional<std::shared_ptr<Message>> pinned_message;
        
        /** @brief Optional. Default chat member permissions, for groups and supergroups. Returned only in getChat */
        std::optional<ChatPermissions> permissions;
        
        /** @brief Optional. For supergroups, the minimum allowed delay between consecutive messages sent by each unpriviledged user. Returned only in getChat */
        std::optional<qint32> slow_mode_delay;
        
        /** @brief Optional. The time after which all messages sent to the chat will be automatically deleted; in seconds. Returned only in getChat */
        std::optional<qint32> message_auto_delete_time;
        
        /** @brief Optional. For supergroups, name of group sticker set. Returned only in getChat */
        std::optional<QString> sticker_set_name;
        
        /** @brief Optional. True, if the bot can change the group sticker set. Returned only in getChat */
        std::optional<bool> can_set_sticker_set;
        
        /** @brief Optional. Unique identifier for the linked chat, i.e.the discussion group identifier for a channel and vice versa; for supergroupsand channel chats. Returned only in getChat */
        std::optional<qint64> linked_chat_id;
        
        /** @brief Optional. For supergroups, the location to which the supergroup is connected. Returned only in getChat */
        std::optional<ChatLocation> location;
    };
}

#endif // TELEGRAM_TYPES_CHAT_H
