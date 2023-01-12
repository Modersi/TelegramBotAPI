#ifndef TELEGRAM_TYPES_INPUTTEXTMESSAGECONTENT_H
#define TELEGRAM_TYPES_INPUTTEXTMESSAGECONTENT_H

#include <compare>
#include <optional>

#include "qstring.h"
#include "qjsonobject.h"
#include "qvector.h"

#include "Types/InputMessageContent.h"
#include "Types/MessageEntity.h"

namespace Telegram
{
    /**
    *
    * @brief This struct represents the content of a text message to be sent as the result of an inline query
    *
    */

    struct InputTextMessageContent : public InputMessageContent
    {
        /** @brief Default constructor. Constructs an empty InputTextMessageContent object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        InputTextMessageContent();

        /** @brief Constructs InputTextMessageContent object from parameters */
        InputTextMessageContent(const QString& message_text,
                                const std::optional<QString>& parse_mode = std::nullopt,
                                const std::optional<QVector<MessageEntity>>& entities = std::nullopt,
                                const std::optional<bool>& disable_web_page_preview = std::nullopt);


        /* @brief Returns InputTextMessageContent in form of JSON object. Returns empty QJsonObject if InputTextMessageContent is empty */
        virtual QJsonObject toObject() const override;

        /* @brief Returns true if InputTextMessageContent is empty */
        virtual bool isEmpty() const override;


        std::partial_ordering operator <=> (const InputTextMessageContent&) const = default;


//** Fields **//

        /** @brief Text of the message to be sent, 1-4096 characters */
        QString	message_text;

        /** @brief Optional. Mode for parsing entities in the message text. See formatting options for more details */
        std::optional<QString> parse_mode;

        /** @brief Optional. List of special entities that appear in message text, which can be specified instead of parse_mode */
        std::optional<QVector<MessageEntity>> entities;
       
        /** @brief Optional. Disables link previews for links in the sent message */
        std::optional<bool>	disable_web_page_preview;
    };
}

#endif // TELEGRAM_TYPES_INPUTTEXTMESSAGECONTENT_H
