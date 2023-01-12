#ifndef TELEGRAM_TYPES_INPUTLOCATIONMESSAGECONTENT_H
#define TELEGRAM_TYPES_INPUTLOCATIONMESSAGECONTENT_H

#include <compare>
#include <optional>

#include "qjsonobject.h"

#include "Types/InputMessageContent.h"

namespace Telegram
{
    /**
    *
    * @brief This struct represents the content of a location message to be sent as the result of an inline query.
    *
    */

    struct InputLocationMessageContent : public InputMessageContent
    {
        /** @brief Default constructor. Constructs an empty InputLocationMessageContent object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        InputLocationMessageContent();

        /** @brief Constructs InputLocationMessageContent object from parameters */
        InputLocationMessageContent(const float& latitude,
                                    const float& longitude,
                                    const std::optional<float>& horizontal_accuracy = std::nullopt,
                                    const std::optional<qint32>& live_period = std::nullopt,
                                    const std::optional<qint32>& heading = std::nullopt,
                                    const std::optional<qint32>& proximity_alert_radius = std::nullopt);

        /* @brief Returns InputLocationMessageContent in form of JSON object. Returns empty QJsonObject if InputLocationMessageContent is empty */
        virtual QJsonObject toObject() const override;

        /* @brief Returns true if InputLocationMessageContent is empty */
        virtual bool isEmpty() const override;

        std::partial_ordering operator <=> (const InputLocationMessageContent&) const = default;

//** Fields **//

        /* @brief Latitude of the location in degrees */
        float latitude;

        /* @brief Longitude of the location in degrees */
        float longitude;
        
        /* @brief Optional. The radius of uncertainty for the location, measured in meters; 0-1500 */
        std::optional<float> horizontal_accuracy;
        
        /* @brief Optional. Period in seconds for which the location can be updated, should be between 60 and 86400 */
        std::optional<qint32> live_period;

        /* @brief Optional. For live locations, a direction in which the user is moving, in degrees. Must be between 1 and 360 if specified */
        std::optional<qint32> heading;

        /* @brief Optional. For live locations, a maximum distance for proximity alerts about approaching another chat member, in meters. Must be between 1 and 100000 if specified */
        std::optional<qint32> proximity_alert_radius;
    };
}

#endif // TELEGRAM_TYPES_INPUTLOCATIONMESSAGECONTENT_H
