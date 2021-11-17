#ifndef TELEGRAM_TYPES_MASKPOSITION_H
#define TELEGRAM_TYPES_MASKPOSITION_H

#include "qstring.h"

namespace Telegram
{
    /**
     *
     * @brief This structure describes the position on faces where a mask should be placed by default
     *
     */

    struct MaskPosition
    {
        /** @brief Enum that represents all available face parts that can be used for mask to be placed */
        enum class Point
        {
            UNINITIALIZED_VALUE,
            FOREHEAD,
            EYES,
            MOUTH,
            CHIN
        };

        /** @brief Default constructor. Constructs an empty MaskPosition object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        MaskPosition();

        /** @brief Constructs MaskPosition object from parameters */
        MaskPosition(const Point& point,
                     const float& x_shift,
                     const float& y_shift,
                     const float& scale);

        /** @brief JSON constructor. Constructs MaskPosition object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has all key-value pairs related to MaskPosition class fields. For example it should contain pairs such as "point" = "...",
         * "x_shift" = "..." and so on, otherwise fields related to missing pairs will be setted to some default values(0, "", std::nullopt) */
        MaskPosition(const QJsonObject& jsonObject);

        /** @brief Returns MaskPosition in form of JSON object. Returns empty QJsonObject if MaskPosition is empty */
        QJsonObject toObject() const;

        /** @brief Returns true if MaskPosition is empty */
        bool isEmpty() const;

//** Fields **//

        /**
         * @brief The part of the face relative to which the mask should be placed. One of “forehead”, “eyes”, “mouth”, or “chin”.
         */
        Point point;

        /** @brief Shift by X-axis measured in widths of the mask scaled to the face size, from left to right. For example, choosing -1.0 will place mask just to the left of the default mask position */
        float x_shift;

        /** @brief Shift by Y-axis measured in heights of the mask scaled to the face size, from top to bottom. For example, 1.0 will place the mask just below the default mask position */
        float y_shift;

        /** @brief Mask scaling coefficient. For example, 2.0 means double size */
        float scale;
    };
}

#endif // TELEGRAM_TYPES_MASKPOSITION_H
