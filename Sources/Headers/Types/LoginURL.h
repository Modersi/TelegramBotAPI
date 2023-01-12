#ifndef TELEGRAM_TYPES_LOGINURL_H
#define TELEGRAM_TYPES_LOGINURL_H

#include <compare>
#include <optional>

#include "qstring.h"
#include "qjsonobject.h"

namespace Telegram
{
    /**
     *
     * @brief This struct represents a parameter of the inline keyboard button used to automatically authorize a user
     *
     *  Serves as a great replacement for the Telegram Login Widget when the user is coming from Telegram. All the user needs to do is tap/click a button and confirm that they want to log in
     *
     */

    struct LoginURL
    {
        /** @brief Default constructor. Constructs an empty LoginURL object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        LoginURL();

        /** @brief Constructs LoginURL object from parameters */
        LoginURL(const QString& url,
                 const std::optional<QString>& forward_text = std::nullopt,
                 const std::optional<QString>& bot_username = std::nullopt,
                 const std::optional<bool>& request_write_access = std::nullopt);

        /** @brief JSON constructor. Constructs LoginURL object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has all key-value pairs related to LoginURL class fields. For example it should contain pairs such as "url" = "...",
         * "forward_text" = "..." and so on, otherwise fields related to missing pairs will be setted to some default values(0, "", std::nullopt) */
        LoginURL(const QJsonObject& json_object);


        /* @brief Returns LoginURL in form of JSON object. Returns empty QJsonObject if LoginURL is empty */
        QJsonObject toObject() const;

        /* @brief Returns true if LoginURL is empty */
        bool isEmpty() const;


        std::partial_ordering operator <=> (const LoginURL&) const = default;


//** Fields **//

        /** @brief An HTTP URL to be opened with user authorization data added to the query string when the button is pressed
         *
         * If the user refuses to provide authorization data, the original URL without information about the user will be opened. The data added is the same as described in [Receiving authorization data](https://core.telegram.org/widgets/login#receiving-authorization-data)
         * > NOTE: You must always check the hash of the received data to verify the authentication and the integrity of the data as described in [Checking authorization](https://core.telegram.org/widgets/login#checking-authorization) */
        QString url;
        
        /** @brief Optional. New text of the button in forwarded messages */
        std::optional<QString> forward_text;
        
        /** @brief Optional. Username of a bot, which will be used for user authorization
         *
         * See [Setting up a bot](https://core.telegram.org/widgets/login#setting-up-a-bot) for more details. If not specified, the current bot's username will be assumed. The url's domain must be the same as the domain linked with the bot. See [Linking your domain to the bot](https://core.telegram.org/widgets/login#linking-your-domain-to-the-bot) for more details */
        std::optional<QString> bot_username;
        
        /** @brief Optional. Pass True to request the permission for your bot to send messages to the user */
        std::optional<bool> request_write_access;
    };
}

#endif // TELEGRAM_TYPES_LOGINURL_H
