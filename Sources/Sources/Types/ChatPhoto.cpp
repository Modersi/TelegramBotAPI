#include "Types/ChatPhoto.h"

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

Telegram::ChatPhoto::ChatPhoto(const QJsonObject& json_object) {
    json_object.contains("small_file_id")        ? small_file_id = json_object["small_file_id"].toString()                : small_file_id = "";
    json_object.contains("small_file_unique_id") ? small_file_unique_id = json_object["small_file_unique_id"].toString()  : small_file_unique_id = "";
    json_object.contains("big_file_id")          ? big_file_id = json_object["big_file_id"].toString()                    : big_file_id = "";
    json_object.contains("big_file_unique_id")   ? big_file_unique_id = json_object["big_file_unique_id"].toString()      : big_file_unique_id = "";
}

QJsonObject Telegram::ChatPhoto::toObject() const {
    if (isEmpty()) return {};

    return QJsonObject{ {"small_file_id", small_file_id}, {"small_file_unique_id", small_file_unique_id}, {"big_file_id", big_file_id}, {"big_file_unique_id", big_file_unique_id} };
}

bool Telegram::ChatPhoto::isEmpty() const {
    return small_file_id == ""
           and small_file_unique_id == ""
           and big_file_id == ""
           and big_file_unique_id == "";
}
