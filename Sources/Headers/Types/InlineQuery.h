#ifndef TELEGRAM_TYPES_INLINEQUERY_H
#define TELEGRAM_TYPES_INLINEQUERY_H

#include <optional>

#include "qmetaobject.h"
#include "qstring.h"
#include "qjsonobject.h"

#include "Types/Location.h"
#include "Types/User.h"

namespace Telegram
{
    /**
     *
     * @brief This struct represents an incoming inline query. When the user sends an empty query, your bot could return some default or trending results
     *
     */

    class InlineQuery
    {
        Q_GADGET

    public:
        /** @brief Enum that represents all available types of the chat, from which the inline query was sent.
         * 
         * The chat type should be always known for requests sent from official clients and most third-party clients, unless the request was sent from a secret chat */
        enum class ChatType
        {
            SENDER, // for a private chat with the inline query sender
            PRIVATE,
            GROUP,
            SUPERGROUP,
            CHANNEL,
            NULL_ENUMERATOR = -1
        };
        Q_ENUM(ChatType)


        /** @brief Default constructor. Constructs an empty InlineQuery object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        InlineQuery();

        /** @brief Constructs InlineQuery object from parameters */
        InlineQuery(const QString& id,
                    const User&	from,
                    const QString& query,
                    const QString& offset,
                    const std::optional<ChatType>& chat_type = std::nullopt,
                    const std::optional<Location>& location = std::nullopt);

        /** @brief JSON constructor. Constructs InlineQuery object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has all key-value pairs related to InlineQuery class fields. For example it should contain pairs such as "id" = "...",
         * "from" = "..." and so on, otherwise fields related to missing pairs will be setted to some default values(0, "", std::nullopt) */
        InlineQuery(const QJsonObject& json_object);


        /** @brief Returns InlineQuery in form of JSON object. Returns empty QJsonObject if Sticker is empty */
        QJsonObject toObject() const;

        /** @brief Returns true if InlineQuery is empty */
        bool isEmpty() const;


        std::partial_ordering operator <=> (const InlineQuery&) const = default;


//** Fields **//

        /** @brief Unique identifier for this query */
        QString id;

        /** @brief Sender */
        User from;

        /** @brief Text of the query (up to 256 characters) */
        QString query;

        /** @brief Offset of the results to be returned, can be controlled by the bot */
        QString offset;

        /** @brief Optional. Type of the chat, from which the inline query was sent. Can be either “SENDER” for a private chat with the inline query sender, “PRIVATE”, “GROUP”, “SUPERGROUP”, or “CHANNEL”
         *
         * The chat type should be always known for requests sent from official clients and most third-party clients, unless the request was sent from a secret chat */
        std::optional<ChatType> chat_type;

        /** @brief Optional. Sender location, only for bots that request user location */
        std::optional<Location> location;
    };
}

#endif // TELEGRAM_TYPES_INLINEQUERY_H
