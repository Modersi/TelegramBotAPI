#ifndef TELEGRAM_TYPES_MESSAGEENTITY_H
#define TELEGRAM_TYPES_MESSAGEENTITY_H

#include <compare>
#include <optional>

#include "qmetaobject.h"
#include "qstring.h"
#include "qjsonobject.h"

#include "User.h"

namespace Telegram
{
    /**
     *
     * @brief This struct represents one special entity in a text message. For example, hashtags, usernames, URLs, etc.
     *
     */

    class MessageEntity
    { 
        Q_GADGET

    public:
        /** @brief Enum that represents all available types of message entity */
        enum class Type {
            MENTION,        // @username    
            HASHTAG,        // #hashtag
            CASHTAG,        // $USD
            BOT_COMMAND,    // /start@jobs_bot
            URL,            // https://telegram.org
            EMAIL,          // do-not-reply@telegram.org
            PHONE_NUMBER,   // +1-212-555-0123
            BOLD,           // bold text
            ITALIC,         // italic text
            UNDERLINE,      // underlined text
            STRIKETHROUGH,  // strikethrough text
            SPOILER,        // spoiler message
            CODE,           // monowidth string
            PRE,            // monowidth block
            TEXT_LINK,      // for clickable text URLs
            TEXT_MENTION,   // for users without usernames
            NULL_ENUMERATOR = -1
        };
        Q_ENUM(Type)

        /** @brief Default constructor. Constructs an empty MessageEntity object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        MessageEntity();

        /** @brief Constructs MessageEntity object from parameters */
        MessageEntity(const Type& type,
                      const qint32& offset,
                      const qint32& length,
                      const std::optional<QString>& url = std::nullopt,
                      const std::optional<User>& user = std::nullopt,
                      const std::optional<QString>& language = std::nullopt);

        /** @brief JSON constructor. Constructs MessageEntity object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has all key-value pairs related to MessageEntity class fields. For example it should contain pairs such as "type" = "...",
         * "offset" = "..." and so on, otherwise fields related to missing pairs will be setted to some default values(0, "", std::nullopt) */
        MessageEntity(const QJsonObject& json_object);


        /* @brief Returns MessageEntity in form of JSON object. Returns empty QJsonObject if MessageEntity is empty */
        QJsonObject toObject() const;

        /* @brief Returns true if MessageEntity is empty */
        bool isEmpty() const;


        std::partial_ordering operator <=> (const MessageEntity&) const = default;


    //** Fields **//

        /** @brief Type of the entity */
        Type type;
        
        /** @brief Offset in UTF-16 code units to the start of the entity */
        qint32 offset;
        
        /** @brief Length of the entity in UTF-16 code units */
        qint32 length;
        
        /** @brief Optional. For text_link only, url that will be opened after user taps on the text */
        std::optional<QString> url;
        
        /** @brief Optional. For text_mention only, the mentioned user */
        std::optional<User> user;
        
        /** @brief Optional. For pre only, the programming language of the entity text */
        std::optional<QString> language;
    };
}

#endif // TELEGRAM_TYPES_MESSAGEENTITY_H
