#ifndef TELEGRAM_TYPES_INLINEQUERYRESULTLOCATION_H
#define TELEGRAM_TYPES_INLINEQUERYRESULTLOCATION_H

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
     * @brief This struct represents a location on a map. By default, the location will be sent by the user
     *
     * Alternatively, you can use input_message_content to send a message with the specified content instead of the location
     *
     * > Note: This will only work in Telegram versions released after 9 April, 2016. Older clients will ignore them
     *
     */

    struct InlineQueryResultLocation : public InlineQueryResult
    {
        /** @brief Default constructor. Constructs an empty InlineQueryResultLocation object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        InlineQueryResultLocation();

        /** @brief Constructs InlineQueryResultLocation object from parameters */
        InlineQueryResultLocation(const QString& id,	                  
                                  const float& latitude,	          
                                  const float& longitude,	          
                                  const QString& title,
                                  const std::optional<float>& horizontal_accuracy = std::nullopt,	  
                                  const std::optional<qint32>& live_period = std::nullopt,	          
                                  const std::optional<qint32>& heading = std::nullopt,	              
                                  const std::optional<qint32>& proximity_alert_radius = std::nullopt,
                                  const std::optional<InlineKeyboardMarkup>& reply_markup = std::nullopt,	      
                                  const std::optional<std::shared_ptr<InputMessageContent>>& input_message_content = std::nullopt,
                                  const std::optional<QString>& thumb_url = std::nullopt,	          
                                  const std::optional<qint32>& thumb_width = std::nullopt,	          
                                  const std::optional<qint32>& thumb_height = std::nullopt);


        /* @brief Returns InlineQueryResultLocation in form of JSON object. Returns empty QJsonObject if InlineQueryResultLocation is empty */
        virtual QJsonObject toObject() const override;

        /* @brief Returns true if InlineQueryResultLocation is empty */
        virtual bool isEmpty() const override;

        /** @brief Returns type of the InlineQueryResult */
        virtual Type getType() const override;


        std::partial_ordering operator <=> (const InlineQueryResultLocation&) const = default;


//** Fields **//

        /** @brief Type of the result, must be location */
        const Type type = Type::LOCATION;

        /** @brief Unique identifier for this result, 1-64 Bytes */
        QString id;
        
        /** @brief Location latitude in degrees */
        float latitude;
        
        /** @brief Location longitude in degrees */
        float longitude;
        
        /** @brief Location title */
        QString title;
       	
        /** @brief Optional. The radius of uncertainty for the location, measured in meters; 0-1500 */
        std::optional<float> horizontal_accuracy;
       	
        /** @brief Optional. Period in seconds for which the location can be updated, should be between 60 and 86400 */
        std::optional<qint32> live_period;
       	
        /** @brief Optional. For live locations, a direction in which the user is moving, in degrees. Must be between 1 and 360 if specified */
        std::optional<qint32> heading;
        
        /** @brief Optional. For live locations, a maximum distance for proximity alerts about approaching another chat member, in meters. Must be between 1 and 100000 if specified */
        std::optional<qint32> proximity_alert_radius;
        
        /** @brief Optional. Inline keyboard attached to the message */
        std::optional<InlineKeyboardMarkup> reply_markup;
        
        /** @brief Optional. Content of the message to be sent instead of the location */
        std::optional<std::shared_ptr<InputMessageContent>> input_message_content;
        
        /** @brief Optional. Url of the thumbnail for the result */
        std::optional<QString>	thumb_url;
       	
        /** @brief Optional. Thumbnail width */
        std::optional<qint32> thumb_width;
        
        /** @brief Optional. Thumbnail height */
        std::optional<qint32> thumb_height;
    };
}

#endif // TELEGRAM_TYPES_INLINEQUERYRESULTLOCATION_H
