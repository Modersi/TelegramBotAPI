#ifndef TELEGRAM_TYPES_CALLBACKQUERY_H
#define TELEGRAM_TYPES_CALLBACKQUERY_H

#include <compare>
#include <optional>

#include "qstring.h"
#include "qjsonobject.h"

#include "User.h"
#include "Message.h"

namespace Telegram
{
    /**
     *
     * @brief This structure represents an incoming Callback Query from a callback button in an inline keyboard
     *
     * If the button that originated the query was attached to a message sent by the bot, the field message will be present.
     * If the button was attached to a message sent via the bot (in inline mode), the field inlineMessageId will be present.
     * Exactly one of the fields data or gameShortName will be present.
     * 
     * > **NOTE:** After the user presses a callback button, Telegram clients will display a progress bar until you call answerCallbackQuery
     * > It is, therefore, necessary to react by calling answerCallbackQuery even if no notification to the user is needed (e.g., without specifying any of the optional parameters)
     *
     */

    struct CallbackQuery
    {
        /** @brief Default constructor. Constructs an empty object
         *
         * All members setted to 0, "", etc... All optional fields setted to std::nullopt */
        CallbackQuery();

        /** @brief Constructs CallbackQuery object from parameters */
        CallbackQuery(const QString& id,
                      const User& from,
                      const QString& chat_instance,
                      const std::optional<Message>& message = std::nullopt,
                      const std::optional<QString>& inline_message_id = std::nullopt,
                      const std::optional<QString>& data = std::nullopt,
                      const std::optional<QString>& game_short_name = std::nullopt);

        /** @brief JSON constructor. Constructs CallbackQuery object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has all key-value pairs related to CallbackQuery class fields. For example it should contain pairs such as "id" = "...",
         * "from" = "..." and so on, otherwise fields related to missing pairs will be setted to some default values(0, "", std::nullopt) */
        CallbackQuery(const QJsonObject& json_object);


        /* @brief Returns CallbackQuery in form of JSON object. Returns empty QJsonObject if CallbackQuery is empty */
        QJsonObject toObject() const;

        /* @brief Returns true if CallbackQuery is empty */
        bool isEmpty() const;


        std::partial_ordering operator <=> (const CallbackQuery&) const = default;


//** Fields **//

        /** @brief Unique identifier for this query */
        QString id;

        /** @brief Sender */
        User from;
        
        /** @brief Global identifier, uniquely corresponding to the chat to which the message with the callback button was sent. Useful for high scores in games */
        QString chat_instance;
        
        /** @brief Optional. Message with the callback button that originated the query. Note that message content and message date will not be available if the message is too old */
        std::optional<Message> message;
        
        /** @brief Optional. Identifier of the message sent via the bot in inline mode, that originated the query */
        std::optional<QString> inline_message_id;
        
        /** @brief Optional. Data associated with the callback button. Be aware that a bad client can send arbitrary data in this field */
        std::optional<QString> data;
        
        /** @brief Optional. Short name of a Game to be returned, serves as the unique identifier for the game */
        std::optional<QString> game_short_name;
    };
}

#endif // TELEGRAM_TYPES_CALLBACKQUERY_H
