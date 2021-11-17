#ifndef TELEGRAM_TYPES_INPUTMEDIA_H
#define TELEGRAM_TYPES_INPUTMEDIA_H

class QJsonObject;

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

	struct InputMedia
	{
		/** @brief Returns InputMedia in form of JSON object. Returns empty QJsonObject if InputMedia is empty */
		virtual QJsonObject toObject() const  = 0;

		/** @brief Returns true if InputMedia is empty */
		virtual bool isEmpty() const  = 0;

		/** @brief Virtual destructor */
		virtual ~InputMedia() = default;
	};
}

#endif // TELEGRAM_TYPES_INPUTMEDIA_H
