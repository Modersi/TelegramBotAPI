#ifndef TELEGRAM_TYPES_INPUTMEDIA_H
#define TELEGRAM_TYPES_INPUTMEDIA_H

namespace Telegram
{
	struct InputMedia
	{
		InputMedia();

		/* @brief Returns InputMedia in form of JSON object. Returns empty QJsonObject if InputMedia is empty */
		QJsonObject toObject() const;

		/* @brief Returns true if InputMedia is empty */
		bool isEmpty() const;
	};
}

#endif // TELEGRAM_TYPES_INPUTMEDIA_H
