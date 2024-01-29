#include "Internal/Utility/QJsonObjectInserter.h"

Utility::QJsonObjectInserter::QJsonObjectInserter(QJsonObject& qjson_object) :
    qjson_object(qjson_object)
{}

void Utility::QJsonObjectInserter::insert(const QString& key, const std::string& value) {
    qjson_object.get().insert(key, value.c_str());
}