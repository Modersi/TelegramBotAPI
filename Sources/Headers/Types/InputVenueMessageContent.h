#ifndef TELEGRAM_TYPES_INPUTVENUEMESSAGECONTENT_H
#define TELEGRAM_TYPES_INPUTVENUEMESSAGECONTENT_H

#include <compare>
#include <optional>

#include "qstring.h"
#include "qjsonobject.h"

#include "Types/InputMessageContent.h"

namespace Telegram
{
    /**
    *
    * @brief This struct represents the content of a venue message to be sent as the result of an inline query.
    *
    */

    struct InputVenueMessageContent : public InputMessageContent
    {
        /** @brief Default constructor. Constructs an empty InputVenueMessageContent object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        InputVenueMessageContent();

        /** @brief Constructs InputVenueMessageContent object from parameters */
        InputVenueMessageContent(const float& latitude,
                                 const float& longitude,
                                 const QString& title,
                                 const QString& address,
                                 const std::optional<QString>& foursquare_id = std::nullopt,
                                 const std::optional<QString>& foursquare_type = std::nullopt,
                                 const std::optional<QString>& google_place_id = std::nullopt,
                                 const std::optional<QString>& google_place_type = std::nullopt);


        /* @brief Returns InputVenueMessageContent in form of JSON object. Returns empty QJsonObject if InputVenueMessageContent is empty */
        virtual QJsonObject toObject() const override;

        /* @brief Returns true if InputVenueMessageContent is empty */
        virtual bool isEmpty() const override;


        std::partial_ordering operator <=> (const InputVenueMessageContent&) const = default;


 //** Fields **//

         /* @brief Latitude of the venue in degrees */
        float latitude;

        /* @brief Longitude of the venue in degrees */
        float longitude;

        /* @brief Name of the venue */
        QString title;

        /* @brief Address of the venue */
        QString address;

        /* @brief Optional. Foursquare identifier of the venue, if known */
        std::optional<QString> foursquare_id;

        /* @brief Optional. Foursquare type of the venue, if known. (For example, “arts_entertainment/default”, “arts_entertainment/aquarium” or “food/icecream”) */
        std::optional<QString> foursquare_type;

        /* @brief Optional. Google Places identifier of the venue */
        std::optional<QString> google_place_id;

        /* @brief Optional. Google Places type of the venue */
        std::optional<QString> google_place_type;
    };
}

#endif // TELEGRAM_TYPES_INPUTVENUEMESSAGECONTENT_H
