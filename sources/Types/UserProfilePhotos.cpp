#include "Types/UserProfilePhotos.h"
#include "Internal/ConversionFunctions.h"

#include "qjsonobject.h"
#include "qjsonarray.h"

Telegram::UserProfilePhotos::UserProfilePhotos() :
	total_count(0),
	photos(QVector<QVector<PhotoSize>>())
{}

Telegram::UserProfilePhotos::UserProfilePhotos(const qint32& total_count,
											   const QVector<QVector<PhotoSize>>& photos) :
	total_count(total_count),
	photos(photos)
{}

Telegram::UserProfilePhotos::UserProfilePhotos(const QJsonObject& jsonObject)
{
	jsonObject.contains("total_count")  ? total_count = jsonObject["total_count"].toInt()									  : total_count = 0;
	jsonObject.contains("photos")		? photos = DoubleQJsonArrayToDoubleQVector<PhotoSize>(jsonObject["photos"].toArray()) : photos = QVector<QVector<PhotoSize>>();
}

QJsonObject Telegram::UserProfilePhotos::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	return QJsonObject{ {"total_count", total_count}, {"photos", DoubleQVectorToDoubleQJsonArray(photos)} };
}

bool Telegram::UserProfilePhotos::isEmpty() const
{
	return total_count == 0 and photos.isEmpty();
}
