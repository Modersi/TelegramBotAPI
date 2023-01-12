#ifndef TELEGRAM_TYPES_INPUTMEDIA_H
#define TELEGRAM_TYPES_INPUTMEDIA_H

#include <compare>

#include "qjsonobject.h"
#include "qmetaobject.h"

namespace Telegram
{
	/**
     *
     * @brief This struct represents the content of a media message to be sent. This class cannot be created, it's only base class for classes listed below. 
     * 
     * It should be one of:
     *	• InputMediaAnimation
	 *  • InputMediaDocument
	 *  • InputMediaAudio
	 *  • InputMediaPhoto
	 *  • InputMediaVideo
     *
     */

	class InputMedia
	{
        Q_GADGET

    public:
        /** @brief Enum that represents all available types of InlineQueryResult */
        enum class Type {
			ANIMATION,
			DOCUMENT,
			AUDIO,
			PHOTO,
			VIDEO,
            NULL_ENUMERATOR = -1
        };
        Q_ENUM(Type)

		/** @brief Returns InputMedia in form of JSON object. Returns empty QJsonObject if InputMedia is empty */
		virtual QJsonObject toObject() const = 0;

		/** @brief Returns true if InputMedia is empty */
		virtual bool isEmpty() const = 0;

		/** @brief Returns type of the InputMedia */
		virtual Type getType() const = 0;

		/** @brief Virtual destructor */
		virtual ~InputMedia() = default;

	    std::partial_ordering operator <=> (const InputMedia&) const = default;

	};
}

#include "InputMediaAnimation.h"
#include "InputMediaDocument.h"
#include "InputMediaAudio.h"
#include "InputMediaPhoto.h"
#include "InputMediaVideo.h"

#endif // TELEGRAM_TYPES_INPUTMEDIA_H
