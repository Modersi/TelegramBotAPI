#ifndef TELEGRAM_TYPES_FILE_H
#define TELEGRAM_TYPES_FILE_H

#include <compare>
#include <optional>

#include "qstring.h"
#include "qjsonobject.h"

namespace Telegram
{
    /**
     *
     * @brief This struct represents a file ready to be downloaded
     *
     * The file can be downloaded via the link "https://api.telegram.org/file/bot<token>/<file_path>"
     * It is guaranteed that the link will be valid for at least 1 hour. When the link expires, a new one can be requested by calling [getFile](@ref getFile)
     *
     * > Maximum file size to download is 20 MB
     * 
     */

    struct File
    {
        /** @brief Default constructor. Constructs an empty File object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        File();

        /** @brief Constructs File object from parameters */
        File(const QString& file_id,
             const QString& file_unique_id,
             const std::optional<qint32>& file_size = std::nullopt,
             const std::optional<QString>& file_path = std::nullopt);

        /** @brief JSON constructor. Constructs File object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has all key-value pairs related to File class fields. For example it should contain pairs such as "file_id" = "...",
         * "file_unique_id" = "..." and so on, otherwise fields related to missing pairs will be setted to some default values(0, "", std::nullopt) */
        File(const QJsonObject& json_object);


        /* @brief Returns File in form of JSON object. Returns empty QJsonObject if File is empty */
        QJsonObject toObject() const;

        /* @brief Returns true if File is empty */
        bool isEmpty() const;


        std::partial_ordering operator <=> (const File&) const = default;


//** Fields **//

        /** @brief Identifier for this file, which can be used to download or reuse the file */
        QString file_id;
        
        /** @brief Unique identifier for this file, which is supposed to be the same over timeand for different bots. Can't be used to download or reuse the file. */
        QString file_unique_id;
        
        /** @brief Optional. File size, if known */
        std::optional<qint32> file_size;
        
        /** @brief Optional. File path
         * 
         * Use https://api.telegram.org/file/bot<token>/<file_path> to get the file */
        std::optional<QString> file_path;
    };
}

#endif // TELEGRAM_TYPES_FILE_H
