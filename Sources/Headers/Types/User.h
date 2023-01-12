#ifndef TELEGRAM_TYPES_USER_H
#define TELEGRAM_TYPES_USER_H

#include <compare>
#include <optional>

#include "qstring.h"
#include "qjsonobject.h"

namespace Telegram
{
    /**
     *
     * @brief This struct represents a Telegram user or bot
     * 
     */

    struct User
    {
        /** @brief Default constructor. Constructs an empty User object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        User();

        /** @brief Constructs User object from parameters */
        User(const qint64& id,
             const bool& is_bot,
             const QString& first_name,
             const std::optional<QString>& last_name = std::nullopt,
             const std::optional<QString>& username = std::nullopt,
             const std::optional<QString>& language_code = std::nullopt,
             const std::optional<bool>& can_join_groups = std::nullopt,
             const std::optional<bool>& can_read_all_group_messages = std::nullopt,
             const std::optional<bool>& supports_inline_queries = std::nullopt);

        /** @brief JSON constructor. Constructs User object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has all key-value pairs related to User class fields. For example it should contain pairs such as "id" = "...",
         * "is_bot" = "..." and so on, otherwise fields related to missing pairs will be setted to some default values(0, "", std::nullopt) */
        User(const QJsonObject& json_object);


        /* @brief Returns User in form of JSON object. Returns empty QJsonObject if User is empty */
        QJsonObject toObject() const;

        /* @brief Returns true if User is empty */
        bool isEmpty() const;


        std::partial_ordering operator <=> (const User&) const = default;


    //** Fields **//

        /** @brief Unique identifier for this user or bot */
        qint64 id;
        
        /** @brief True, if this user is a bot */
        bool is_bot;
        
        /** @brief User's or bot's first name */
        QString first_name;
        
        /** @brief Optional. User's or bot's last name */
        std::optional<QString> last_name;
        
        /** @brief Optional. User's or bot's username */
        std::optional<QString> username;
        
        /** @brief Optional. IETF language tag of the user's language */
        std::optional<QString> language_code;
        
        /** @brief Optional. True, if the bot can be invited to groups. Returned only in getMe */
        std::optional<bool> can_join_groups;
        
        /** @brief Optional.True, if privacy mode is disabled for the bot. Returned only in getMe */
        std::optional<bool> can_read_all_group_messages;
        
        /** @brief Optional. True, if the bot supports inline queries. Returned only in getMe */
        std::optional<bool> supports_inline_queries;
    };
}

#endif // TELEGRAM_TYPES_USER_H
