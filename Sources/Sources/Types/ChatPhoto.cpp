#include "Types/ChatPhoto.h"

#include "qjsonobject.h"

Telegram::ChatPhoto::ChatPhoto() :
    small_file_id(),
    small_file_unique_id(),
    big_file_id(),
    big_file_unique_id()
{}

Telegram::ChatPhoto::ChatPhoto(const QString& small_file_id,
                               const QString& small_file_unique_id,
                               const QString& big_file_id,
                               const QString& big_file_unique_id) :
    small_file_id(small_file_id),
    small_file_unique_id(small_file_unique_id),
    big_file_id(big_file_id),
    big_file_unique_id(big_file_unique_id)
{}

Telegram::ChatPhoto::ChatPhoto(const QJsonObject& jsonObject)
{
    jsonObject.contains("small_file_id")        ? small_file_id = jsonObject["small_file_id"].toString()                : small_file_id = "";
    jsonObject.contains("small_file_unique_id") ? small_file_unique_id = jsonObject["small_file_unique_id"].toString()  : small_file_unique_id = "";
    jsonObject.contains("big_file_id")          ? big_file_id = jsonObject["big_file_id"].toString()                    : big_file_id = "";
    jsonObject.contains("big_file_unique_id")   ? big_file_unique_id = jsonObject["big_file_unique_id"].toString()      : big_file_unique_id = "";
}

QJsonObject Telegram::ChatPhoto::toObject() const
{
    if (isEmpty())
        return QJsonObject();

    return QJsonObject{ {"small_file_id", small_file_id}, {"small_file_unique_id", small_file_unique_id}, {"big_file_id", big_file_id}, {"big_file_unique_id", big_file_unique_id} };
}

bool Telegram::ChatPhoto::isEmpty() const
{
    return small_file_id == ""
           and small_file_unique_id == ""
           and big_file_id == ""
           and big_file_unique_id == "";
}
