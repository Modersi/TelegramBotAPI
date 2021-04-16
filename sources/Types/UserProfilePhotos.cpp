#include "Types/UserProfilePhotos.h"

UserProfilePhotos::UserProfilePhotos()
{

}

UserProfilePhotos::UserProfilePhotos(qint32                      totalCount,
                                     QVector<QVector<PhotoSize>> photos)
{
    _jsonObject.insert("total_count", QJsonValue(totalCount));

    QJsonArray tempJsonArray;
    for(int i = 0; i < photos.size(); i++)
        tempJsonArray.insert(tempJsonArray.end(), Type::QVectorToQJsonArray(photos[i]));

    _jsonObject.insert("photos", QJsonValue(tempJsonArray));
}

UserProfilePhotos::UserProfilePhotos(QJsonObject jsonObject)
{
    if(jsonObject.contains("total_count"))
        _jsonObject.insert("total_count", jsonObject.value("total_count"));

    if(jsonObject.contains("photos"))
        _jsonObject.insert("photos", jsonObject.value("photos"));
}

// "get", "set" methods for "total_count" field //

qint32 UserProfilePhotos::totalCount()
{
    return _jsonObject.value("total_count").toInt();
}

void UserProfilePhotos::setTotalCount(qint32 totalCount)
{
    _jsonObject.insert("total_count", totalCount);
}

// "get", "set" methods for "photos" field //

QVector<QVector<PhotoSize>> UserProfilePhotos::photos()
{
    QJsonArray photosArray = _jsonObject.value("photos").toArray();
    QVector<QVector<PhotoSize>> tempQVector;

    for(QJsonArray::const_iterator i = photosArray.begin(); i < photosArray.end(); i++)
        tempQVector.insert(tempQVector.end(), Type::QJsonArrayToQVector(i->toArray(), PhotoSize()));

    return tempQVector;
}

void UserProfilePhotos::setPhotos(QVector<QVector<PhotoSize> > photos)
{
    QJsonArray tempJsonArray;

    for(int i = 0; i < photos.size(); i++)
        tempJsonArray.insert(tempJsonArray.end(), Type::QVectorToQJsonArray(photos[i]));

    _jsonObject.insert("photos", tempJsonArray);
}
