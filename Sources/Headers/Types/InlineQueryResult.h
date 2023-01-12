#ifndef TELEGRAM_TYPES_INLINEQUERYRESULT_H
#define TELEGRAM_TYPES_INLINEQUERYRESULT_H

#include <compare>

#include "qjsonobject.h"
#include "qmetaobject.h"

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

    class InlineQueryResult
    {
        Q_GADGET

    public:
        /** @brief Enum that represents all available types of InlineQueryResult */
        enum class Type {
            ARTICLE,
            AUDIO,
            CONTACT,
            GAME,
            DOCUMENT,
            GIF,
            LOCATION,
            STICKER,
            MPEG4_GIF,
            PHOTO,
            VENUE,
            VIDEO,
            VOICE,
            NULL_ENUMERATOR = -1
        };
        Q_ENUM(Type)


        /* @brief Returns InlineQueryResult in form of JSON object */
        inline virtual QJsonObject toObject() const = 0;

        /** @brief Returns true if InlineQueryResult is empty */
        virtual bool isEmpty() const = 0;

        /** @brief Returns type of the InlineQueryResult */
        virtual Type getType() const = 0;


        /** @brief Virtual destructor */
        virtual ~InlineQueryResult() = default;


        std::partial_ordering operator <=> (const InlineQueryResult&) const = default;

    };
}

#include "InlineQueryResultCachedAudio.h"
#include "InlineQueryResultCachedDocument.h"
#include "InlineQueryResultCachedGif.h"
#include "InlineQueryResultCachedMpeg4Gif.h"
#include "InlineQueryResultCachedPhoto.h"
#include "InlineQueryResultCachedSticker.h"
#include "InlineQueryResultCachedVideo.h"
#include "InlineQueryResultCachedVoice.h"
#include "InlineQueryResultArticle.h"
#include "InlineQueryResultAudio.h"
#include "InlineQueryResultContact.h"
#include "InlineQueryResultGame.h"
#include "InlineQueryResultDocument.h"
#include "InlineQueryResultGif.h"
#include "InlineQueryResultLocation.h"
#include "InlineQueryResultMpeg4Gif.h"
#include "InlineQueryResultPhoto.h"
#include "InlineQueryResultVenue.h"
#include "InlineQueryResultVideo.h"
#include "InlineQueryResultVoice.h"

#endif // TELEGRAM_TYPES_INLINEQUERYRESULT_H
