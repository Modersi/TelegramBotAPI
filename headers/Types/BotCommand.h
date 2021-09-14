#ifndef TELEGRAM_TYPES_BOTCOMMAND_H
#define TELEGRAM_TYPES_BOTCOMMAND_H

#include "qstring.h"
class QJsonObject;

namespace Telegram
{
    /**
     *
     * @brief This class represents a Bot Command
     *
     */

    struct BotCommand
    {
        /** @brief Default constructor. Constructs an empty object
         *
         * All fields setted to "" */
        BotCommand();

        /** @brief Constructs BotCommand object from parameters */
        BotCommand(const QString& command,
                   const QString& description);

        /** @brief JSON constructor. Constructs BotCommand object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has key-value pairs such as "command" = "...", "description" = "..." to construct correct 
         * object, otherwise if this pairs are missing empty object will be created */
        BotCommand(const QJsonObject& jsonObject);

        /* @brief Returns BotCommand in form of JSON object. Returns empty QJsonObject if BotCommand is empty */
        QJsonObject toObject() const;

        /* @brief Returns true if BotCommand is empty */
        bool isEmpty() const;

//** Fields **//

        /** @brief Text of the command 
         * 
         * Must be 1-32 characters. Can contain only lowercase English letters, digits and underscores */
        QString command;

        /** @brief Description of the command
         *
         * Must be 3-256 characters */
        QString description;
    };
}

#endif // TELEGRAM_TYPES_BOTCOMMAND_H
