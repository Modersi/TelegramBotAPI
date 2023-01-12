#ifndef TELEGRAM_TYPES_USERPROFILEPHOTOS_H
#define TELEGRAM_TYPES_USERPROFILEPHOTOS_H

#include <compare>

#include "qvector.h"
#include "qjsonobject.h"

#include "PhotoSize.h"

namespace Telegram
{
    /**
     *
     * @brief This struct represent a user's profile pictures
     *
     */

    struct UserProfilePhotos
    {
        /** @brief Default constructor. Constructs an empty UserProfilePhotos object
         *
         * All fields setted to 0, "", etc... */
        UserProfilePhotos();

        /** @brief Constructs UserProfilePhotos object from parameters */
        UserProfilePhotos(const qint32& total_count,
                          const QVector<QVector<PhotoSize>>& photos);

        /** @brief JSON constructor. Constructs UserProfilePhotos object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has key-value pair "total_count" = "..." and double JSON Array of PhotoSize objects to construct correct UserProfilePhotos 
         * object, otherwise emtpy object will be constructed */
        UserProfilePhotos(const QJsonObject& json_object);


        /* @brief Returns UserProfilePhotos in form of JSON object. Returns empty QJsonObject if UserProfilePhotos is empty */
        QJsonObject toObject() const;

        /* @brief Returns true if UserProfilePhotos is empty */
        bool isEmpty() const;


        std::partial_ordering operator <=> (const UserProfilePhotos&) const = default;


//** Fields **//

        /** @brief Total number of profile pictures the target user has */
        qint32 total_count;

        /** @brief Requested profile pictures(in up to 4 sizes each) */
        QVector<QVector<PhotoSize>> photos;
    };
}

#endif // TELEGRAM_TYPES_USERPROFILEPHOTOS_H
