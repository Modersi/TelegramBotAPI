#ifndef TELEGRAM_UTILITY_QJSONOBJECTINSERTER_HPP
#define TELEGRAM_UTILITY_QJSONOBJECTINSERTER_HPP

#include "Internal/Utility/QJsonObjectInserter.h"


template<typename... Args>
static QJsonObject Utility::QJsonObjectInserter::make(std::span<QString> keys, Args&&... values) {

    auto&& result = QJsonObject();
    auto&& inserter = QJsonObjectInserter(result);
    auto&& keys_iterator = keys.begin();

    (inserter.insert(*keys_iterator++, std::forward<decltype(values)>(values)), ...);

    return result;
}

template<typename ValueType>
    requires std::is_constructible_v<QJsonValue, Utility::remove_pcvref<ValueType>>
void Utility::QJsonObjectInserter::insert(const QString& key, ValueType&& value) {

    if constexpr (std::is_pointer_v<ValueType>) {
        qjson_object.get().insert(key, *value);
    }
    else qjson_object.get().insert(key, value);
}

template<typename ValueType>
    requires Utility::hasMethod_toObject<ValueType>
void Utility::QJsonObjectInserter::insert(const QString& key, ValueType&& value) {

    if constexpr (std::is_pointer_v<ValueType>) {
        qjson_object.get().insert(key, value->toObject());
    }
    else qjson_object.get().insert(key, value.toObject()); 
}

template<typename QEnumType>
    requires std::is_enum_v<Utility::remove_pcvref<QEnumType>>
void Utility::QJsonObjectInserter::insert(const QString& key, QEnumType&& qenum) {

    if constexpr (std::is_pointer_v<QEnumType>) {
        qjson_object.get().insert(key, QString(QMetaEnum::fromType<Utility::remove_pcvref<QEnumType>>()
            .valueToKey(static_cast<int>(*qenum)))
            .toLower()
        );
    }
    else {
        qjson_object.get().insert(key, QString(QMetaEnum::fromType<Utility::remove_pcvref<QEnumType>>()
            .valueToKey(static_cast<int>(qenum)))
            .toLower()
        );
    }   
}

template<typename OptionalType>
void Utility::QJsonObjectInserter::insert(const QString& key, const std::optional<OptionalType>& optional) {

    if (optional.has_value()) {
        if constexpr (std::is_pointer_v<OptionalType>) {
            insert(key, *optional.value());
        }
        else insert(key, optional.value());
    }
}

template<typename QVectorType>
void Utility::QJsonObjectInserter::insert(const QString& key, const QVector<QVectorType>& qvector) {

    insert(key, QJsonArrayInserter::make(qvector.begin(), qvector.end()));
}

template<typename... VariantTypes>
void Utility::QJsonObjectInserter::insert(const QString& key, const std::variant<VariantTypes...>& variant) {

    std::visit([this, &key](auto&& value) {
        insert(key, value);
    }, variant);
}

#endif // TELEGRAM_UTILITY_QJSONOBJECTINSERTER_HPP