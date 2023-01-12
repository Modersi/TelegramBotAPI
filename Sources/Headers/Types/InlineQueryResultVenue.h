#ifndef TELEGRAM_TYPES_INLINEQUERYRESULTVENUE_H
#define TELEGRAM_TYPES_INLINEQUERYRESULTVENUE_H

#include <compare>
#include <optional>
#include <memory>

#include "qstring.h"
#include "qjsonobject.h"

#include "Types/InputMessageContent.h"
#include "Types/InlineQueryResult.h"
#include "Types/InlineKeyboardMarkup.h"

namespace Telegram
{
    /**
     *
     * @brief This struct represents a venue. By default, the venue will be sent by the user
     *
     * Alternatively, you can use input_message_content to send a message with the specified content instead of the venue
     *
     * > Note: This will only work in Telegram versions released after 9 April, 2016. Older clients will ignore them
     *
     */

    struct InlineQueryResultVenue : public InlineQueryResult
    {
        /** @brief Default constructor. Constructs an empty InlineQueryResultVenue object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        InlineQueryResultVenue();

        /** @brief Constructs InlineQueryResultVenue object from parameters */
        InlineQueryResultVenue(const QString& id,
                               const float& latitude,
                               const float& longitude,
                               const QString& title,
                               const QString& address,
                               const std::optional<QString>& foursquare_id = std::nullopt,
                               const std::optional<QString>& foursquare_type = std::nullopt,
                               const std::optional<QString>& google_place_id = std::nullopt,
                               const std::optional<QString>& google_place_type = std::nullopt,
                               const std::optional<InlineKeyboardMarkup>& reply_markup = std::nullopt,
                               const std::optional<std::shared_ptr<InputMessageContent>>& input_message_content = std::nullopt,
                               const std::optional<QString>& thumb_url = std::nullopt,
                               const std::optional<qint32>& thumb_width = std::nullopt,
                               const std::optional<qint32>& thumb_height = std::nullopt);


        /* @brief Returns InlineQueryResultVenue in form of JSON object. Returns empty QJsonObject if InlineQueryResultVenue is empty */
        virtual QJsonObject toObject() const override;

        /* @brief Returns true if InlineQueryResultVenue is empty */
        virtual bool isEmpty() const override;

        /** @brief Returns type of the InlineQueryResult */
        virtual Type getType() const override;


        std::partial_ordering operator <=> (const InlineQueryResultVenue&) const = default;


//** Fields **//

        /** @brief Type of the result, must be venue */
        const Type type = Type::VENUE;

        /** @brief Unique identifier for this result, 1-64 Bytes */
        QString id;
        
        /** @brief Latitude of the venue location in degrees */
        float latitude;
        
        /** @brief Longitude of the venue location in degrees */
        float longitude;
        
        /** @brief Title of the venue */
        QString title;
        
        /** @brief Address of the venue */
        QString address;
        
        /** @brief Optional. Foursquare identifier of the venue if known */
        std::optional<QString> foursquare_id;
        
        /** @brief Optional. Foursquare type of the venue, if known. (For example, “arts_entertainment/default”, “arts_entertainment/aquarium” or “food/icecream”.) */
        std::optional<QString> foursquare_type;
        
        /** @brief Optional. Google Places identifier of the venue */
        std::optional<QString> google_place_id;
        
        /** @brief Optional. Google Places type of the venue. See supported types - https://developers.google.com/places/web-service/supported_types */
        std::optional<QString> google_place_type;
        
        /** @brief Optional. Inline keyboard attached to the message */
        std::optional<InlineKeyboardMarkup> reply_markup;
        
        /** @brief Optional. Content of the message to be sent instead of the venue */
        std::optional<std::shared_ptr<InputMessageContent>> input_message_content;
        
        /** @brief Optional. Url of the thumbnail for the result */
        std::optional<QString> thumb_url;
        
        /** @brief Optional. Thumbnail width */
        std::optional<qint32> thumb_width;
        
        /** @brief Optional. Thumbnail height */
        std::optional<qint32> thumb_height;
    };
}

#endif // TELEGRAM_TYPES_INLINEQUERYRESULTVENUE_H
