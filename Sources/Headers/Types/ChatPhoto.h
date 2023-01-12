#ifndef TELEGRAM_TYPES_CHATPHOTO_H
#define TELEGRAM_TYPES_CHATPHOTO_H

#include <compare>

#include "qstring.h"
#include "qjsonobject.h"

namespace Telegram
{
    /**
     *
     * @brief This struct represents a chat photo
     *
     */

    struct ChatPhoto
    {
        /** @brief Default constructor. Constructs an empty object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        ChatPhoto();

        /** @brief Constructs ChatPhoto object from parameters */
        ChatPhoto(const QString& small_file_id,
                  const QString& small_file_unique_id,
                  const QString& big_file_id,
                  const QString& big_file_unique_id);

        /** @brief JSON constructor. Constructs ChatPhoto object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has all key-value pairs related to ChatPhoto class fields. For example it should contain pairs such as "small_file_id" = "...",
         * "small_file_unique_id" = "..." and so on, otherwise fields related to missing pairs will be setted to some default values(0, "", std::nullopt) */
        ChatPhoto(const QJsonObject& json_object);


        /* @brief Returns ChatPhoto in form of JSON object. Returns empty QJsonObject if ChatPhoto is empty */
        QJsonObject toObject() const;

        /* @brief Returns true if ChatPhoto is empty */
        bool isEmpty() const;


        std::partial_ordering operator <=> (const ChatPhoto&) const = default;


//** Fields **//

        /** @brief File identifier of small(160x160) chat photo
         * 
         * This file_id can be used only for photo downloadand only for as long as the photo is not changed */
        QString small_file_id;
        
        /** @brief Unique file identifier of small(160x160) chat photo
         *
         * Supposed to be the same over time and for different bots. Can't be used to download or reuse the file */
        QString small_file_unique_id;
        
        /** @brief File identifier of big(640x640) chat photo
         *
         * This file_id can be used only for photo downloadand only for as long as the photo is not changed */
        QString big_file_id;
        
        /** @brief Unique file identifier of big(640x640) chat photo
         * 
         * Supposed to be the same over timeand for different bots. Can't be used to download or reuse the file */
        QString big_file_unique_id;
    };
}

#endif // CHATPHOTO_H
