#ifndef TELEGRAM_TYPES_INLINEQUERYRESULTVIDEO_H
#define TELEGRAM_TYPES_INLINEQUERYRESULTVIDEO_H

#include <compare>
#include <optional>
#include <memory>

#include "qstring.h"
#include "qjsonobject.h"
#include "qvector.h"

#include "Types/InputMessageContent.h"
#include "Types/InlineQueryResult.h"
#include "Types/InlineKeyboardMarkup.h"
#include "Types/MessageEntity.h"

namespace Telegram
{
    /**
     *
     * @brief This struct represents a link to a page containing an embedded video player or a video file
     *
     * By default, this video file will be sent by the user with an optional caption. Alternatively, you can use input_message_content to send a message with the specified content instead of the video
     * 
     * > If an InlineQueryResultVideo message contains an embedded video (e.g., YouTube), you **must** replace its content using input_message_content
     * 
     */

    struct InlineQueryResultVideo : public InlineQueryResult
    {
        /** @brief Default constructor. Constructs an empty InlineQueryResultVideo object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        InlineQueryResultVideo();

        /** @brief Constructs InlineQueryResultVideo object from parameters */
        InlineQueryResultVideo(const QString& id,	                 
                               const QString& video_url,	         
                               const QString& mime_type,	         
                               const QString& thumb_url,	         
                               const QString& title,	             
                               const std::optional<QString>& caption = std::nullopt,	             
                               const std::optional<QString>& parse_mode = std::nullopt,	         
                               const std::optional<QVector<MessageEntity>>& caption_entities = std::nullopt,	 
                               const std::optional<qint32>& video_width = std::nullopt,	         
                               const std::optional<qint32>& video_height = std::nullopt,	     
                               const std::optional<qint32>& video_duration = std::nullopt,	     
                               const std::optional<QString>& description = std::nullopt,	         
                               const std::optional<InlineKeyboardMarkup>& reply_markup = std::nullopt,	     
                               const std::optional<std::shared_ptr<InputMessageContent>>& input_message_content = std::nullopt);


         /* @brief Returns InlineQueryResultVideo in form of JSON object. Returns empty QJsonObject if InlineQueryResultVideo is empty */
        virtual QJsonObject toObject() const override;

        /* @brief Returns true if InlineQueryResultVideo is empty */
        virtual bool isEmpty() const override;

        /** @brief Returns type of the InlineQueryResult */
        virtual Type getType() const override;


        std::partial_ordering operator <=> (const InlineQueryResultVideo&) const = default;


//** Fields **//

        /** @brief Type of the result, must be video */
        const Type type = Type::VIDEO;
        
        /** @brief Unique identifier for this result, 1-64 bytes */
        QString id;
        
        /** @brief A valid URL for the embedded video player or video file */
        QString video_url;
        
        /** @brief Mime type of the content of video url, “text/html” or “video/mp4” */
        QString mime_type;
        
        /** @brief URL of the thumbnail (jpeg only) for the video */
        QString thumb_url;
        
        /** @brief Title for the result */
        QString title;
        
        /** @brief Optional. Caption of the video to be sent, 0-1024 characters after entities parsing */
        std::optional<QString> caption;
        
        /** @brief Optional. Mode for parsing entities in the video caption */
        std::optional<QString> parse_mode;
        
        /** @brief Optional. List of special entities that appear in the caption, which can be specified instead of parse_mode */
        std::optional<QVector<MessageEntity>> caption_entities;
        
        /** @brief Optional. Video width */
        std::optional<qint32> video_width;
        
        /** @brief Optional. Video height */
        std::optional<qint32> video_height;
        
        /** @brief Optional. Video duration in seconds */
        std::optional<qint32> video_duration;
        
        /** @brief Optional. Short description of the result */
        std::optional<QString> description;
        
        /** @brief Optional. Inline keyboard attached to the message */
        std::optional<InlineKeyboardMarkup> reply_markup;
        
        /** @brief Optional. Content of the message to be sent instead of the video
         * 
         * This field is required if InlineQueryResultVideo is used to send an HTML-page as a result (e.g., a YouTube video) */
        std::optional<std::shared_ptr<InputMessageContent>> input_message_content;
    };
}

#endif // TELEGRAM_TYPES_INLINEQUERYRESULTVIDEO_H
