#ifndef TELEGRAM_TYPES_ANIMATION_H
#define TELEGRAM_TYPES_ANIMATION_H

#include <compare>

#include "qstring.h"
#include "qjsonobject.h"

#include "PhotoSize.h"

namespace Telegram 
{
	/**
	 *
	 * @brief This structure represents an Animation file
	 *
	 * Animation can only be GIF or H.264/MPEG-4 AVC video without sound
	 *
	 */

	struct Animation
	{
		/** @brief Default constructor. Constructs an empty Animation object
		 * 
		 * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
		Animation();
	
		/** @brief Constructs Animation object from parameters */
		Animation(const QString& file_id,
				  const QString& file_unique_id,
				  const qint32& width,
				  const qint32& height,
				  const qint32& duration,
				  const std::optional<PhotoSize>& thumb = std::nullopt,
				  const std::optional<QString>& file_name = std::nullopt,
				  const std::optional<QString>& mime_type = std::nullopt,
				  const std::optional<qint32>& file_size = std::nullopt);
		
		/** @brief JSON constructor. Constructs Animation object from QJsonObject
		 *
		 * QJsonObject which is passed to constuctor has to has all key-value pairs related to Animation class fields. For example it should contain pairs such as "file_id" = "...",
         * "file_unique_id" = "..." and so on, otherwise fields related to missing pairs will be setted to some default values(0, "", std::nullopt) */
		Animation(const QJsonObject &json_object);


		/* @brief Returns Animation in form of JSON object. Returns empty QJsonObject if Animation is empty */
		QJsonObject toObject() const;

		/* @brief Returns true if Animation is empty */
		bool isEmpty() const;


        std::partial_ordering operator <=> (const Animation&) const = default;
		

//** Fields **//

		/** @brief Identifier for this file, which can be used to download or reuse the file */
		QString file_id;

		/** @brief Unique identifier for this file, which is supposed to be the same over time and for different bots. Can't be used to download or reuse the file */
		QString file_unique_id;

		/** @brief Animation width as defined by sender */
		qint32 width;

		/** @brief Animation height as defined by sender */
		qint32 height;

		/** @brief Duration of the animation in seconds as defined by sender */
		qint32 duration;

		/** @brief Optional. Animation thumbnail as defined by sender */
		std::optional<PhotoSize> thumb;

		/** @brief Optional. Original animation filename as defined by sender */
		std::optional<QString> file_name;

		/** @brief Optional. [MIME](https://en.wikipedia.org/wiki/Media_type) type of the file as defined by sender */
		std::optional<QString> mime_type;

		/** @brief Optional. File size */
		std::optional<qint32> file_size;
	};
}

#endif // TELEGRAM_TYPES_ANIMATION_H
