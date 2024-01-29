#include "Types/UserProfilePhotos.h"

#include "Internal/Utility/QJsonArrayInserter.h"
#include "Internal/Utility/QVectorInserter.h"

#include "qjsonarray.h"

Telegram::UserProfilePhotos::UserProfilePhotos() :
	total_count(),
	photos()
{}

Telegram::UserProfilePhotos::UserProfilePhotos(const qint32& total_count,
											   const QVector<QVector<PhotoSize>>& photos) :
	total_count(total_count),
	photos(photos)
{}

Telegram::UserProfilePhotos::UserProfilePhotos(const QJsonObject& json_object) {
	json_object.contains("total_count") ? total_count = json_object["total_count"].toInt()												: total_count = 0;
	json_object.contains("photos")		? photos = Utility::QVectorInserter<QVector<PhotoSize>>::make(json_object["photos"].toArray())	: photos = QVector<QVector<PhotoSize>>();
}

QJsonObject Telegram::UserProfilePhotos::toObject() const {
	if (isEmpty()) return {};

	return { {"total_count", total_count}, {"photos", Utility::QJsonArrayInserter::make(photos.begin(), photos.end())} };
}

bool Telegram::UserProfilePhotos::isEmpty() const {
	return total_count == 0 and photos.isEmpty();
}
