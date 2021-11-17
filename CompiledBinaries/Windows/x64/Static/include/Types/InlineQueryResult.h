#ifndef TELEGRAM_TYPES_INLINEQUERYRESULT_H
#define TELEGRAM_TYPES_INLINEQUERYRESULT_H

class QJsonObject;

namespace Telegram
{
    /**
    * 
    * @brief This struct represents one result of an inline query. This is an abstract class, it's only base for classes listed below
    * 
    * Telegram clients currently support results of the following 20 types:
    *   • InlineQueryResultCachedAudio
    *   • InlineQueryResultCachedDocument
    *   • InlineQueryResultCachedGif
    *   • InlineQueryResultCachedMpeg4Gif
    *   • InlineQueryResultCachedPhoto
    *   • InlineQueryResultCachedSticker
    *   • InlineQueryResultCachedVideo
    *   • InlineQueryResultCachedVoice
    *   • InlineQueryResultArticle
    *   • InlineQueryResultAudio
    *   • InlineQueryResultContact
    *   • InlineQueryResultGame
    *   • InlineQueryResultDocument
    *   • InlineQueryResultGif
    *   • InlineQueryResultLocation
    *   • InlineQueryResultMpeg4Gif
    *   • InlineQueryResultPhoto
    *   • InlineQueryResultVenue
    *   • InlineQueryResultVideo
    *   • InlineQueryResultVoice
    * 
    * > Note: All URLs passed in inline query results will be available to end users and therefore must be assumed to be public
    * 
    */

    struct InlineQueryResult
    {
        /* @brief Returns InlineQueryResult in form of JSON object */
        inline virtual QJsonObject toObject() const = 0;

        /** @brief Returns true if InlineQueryResult is empty */
        virtual bool isEmpty() const = 0;

        /** @brief Virtual destructor */
        virtual ~InlineQueryResult() = default;
    };
}

#endif // TELEGRAM_TYPES_INLINEQUERYRESULT_H
