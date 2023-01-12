#ifndef TELEGRAM_TYPES_INLINEQUERYRESULTGAME_H
#define TELEGRAM_TYPES_INLINEQUERYRESULTGAME_H

#include <compare>
#include <optional>

#include "qstring.h"
#include "qjsonobject.h"

#include "Types/InlineQueryResult.h"
#include "Types/InlineKeyboardMarkup.h"

namespace Telegram
{
    /**
     *
     * @brief This struct represents a Game
     *
     * > Note: This will only work in Telegram versions released after October 1, 2016. Older clients will not display any inline results if a game result is among them
     *
     */

    struct InlineQueryResultGame : public InlineQueryResult
    {
        /** @brief Default constructor. Constructs an empty InlineQueryResultGame object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        InlineQueryResultGame();

        /** @brief Constructs InlineQueryResultGame object from parameters */
        InlineQueryResultGame(const QString& id,
                              const QString& game_short_name,
                              const std::optional<InlineKeyboardMarkup>& reply_markup = std::nullopt);

        /* @brief Returns InlineQueryResultGame in form of JSON object. Returns empty QJsonObject if InlineQueryResultGame is empty */
        virtual QJsonObject toObject() const override;

        /* @brief Returns true if InlineQueryResultGame is empty */
        virtual bool isEmpty() const override;

        /** @brief Returns type of the InlineQueryResult */
        virtual Type getType() const override;

        std::partial_ordering operator <=> (const InlineQueryResultGame&) const = default;

//** Fields **//

        /** @brief Type of the result, must be game */
        const Type type = Type::GAME;

        /** @brief Unique identifier for this result, 1-64 Bytes */
        QString	id;

        /** @brief Short name of the game */
        QString	game_short_name;

        /** @brief Optional. Inline keyboard attached to the message */
        std::optional<InlineKeyboardMarkup> reply_markup;
    };
}

#endif // TELEGRAM_TYPES_INLINEQUERYRESULTGAME_H
