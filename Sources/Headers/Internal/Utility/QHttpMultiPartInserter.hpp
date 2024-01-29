#ifndef TELEGRAM_UTILITY_QHTTPMULTIPARTINSERTER_HPP
#define TELEGRAM_UTILITY_QHTTPMULTIPARTINSERTER_HPP

#include "Internal/Utility/QHttpMultiPartInserter.h"

template<typename... Args>
static std::unique_ptr<QHttpMultiPart> Utility::QHttpMultiPartInserter::make(std::span<QString> keys, Args&&... values) {

    auto&& result = std::make_unique<QHttpMultiPart>(QHttpMultiPart::FormDataType);
    auto&& http_multi_part_inserter = QHttpMultiPartInserter(result.get());
    auto&& keys_iterator = keys.begin();

    (http_multi_part_inserter.insert(*keys_iterator++, std::forward<decltype(values)>(values)), ...);

    return std::move(result);
}

template<typename ValueType>
    requires std::is_constructible_v<QVariant, Utility::remove_pcvref<ValueType>>
void Utility::QHttpMultiPartInserter::insert(const QString& key, ValueType&& value) {

    QHttpPart part;
    part.setHeader(QNetworkRequest::ContentDispositionHeader, QStringLiteral("form-data; name=\"%1\"").arg(key));

    QByteArray body;

    if constexpr (std::is_same_v<QJsonDocument, Utility::remove_pcvref<ValueType>>
        or std::is_same_v<QJsonObject, Utility::remove_pcvref<ValueType>>
        or std::is_same_v<QJsonArray, Utility::remove_pcvref<ValueType>>) 
    {
        if constexpr (std::is_pointer_v<ValueType>) {
            body = QJsonDocument(*value).toJson();
        }
        else body = QJsonDocument(std::forward<ValueType>(value)).toJson();
    }
    else if constexpr (std::is_same_v<QStringList, Utility::remove_pcvref<ValueType>>) 
    {
        if constexpr (std::is_pointer_v<ValueType>) {
            body = QJsonDocument(QJsonArrayInserter::make(value->begin(), value->end())).toJson();
        }
        else body = QJsonDocument(QJsonArrayInserter::make(value.begin(), value.end())).toJson();
    }
    else
    {
        if constexpr (std::is_pointer_v<ValueType>) {
            body = QVariant(*value).toByteArray();
        }
        else body = QVariant(std::forward<ValueType>(value)).toByteArray();
    }

    part.setBody(body);

    qhttp_multipart->append(part);
}

template<typename ValueType>
    requires Utility::hasMethod_toObject<ValueType>
void Utility::QHttpMultiPartInserter::insert(const QString& key, ValueType&& value) {

    QHttpPart part;
    part.setHeader(QNetworkRequest::ContentDispositionHeader, QStringLiteral("form-data; name=\"%1\"").arg(key));

    if constexpr (std::is_pointer_v<ValueType>) {
        part.setBody(QJsonDocument(value->toObject()).toJson());
    }
    else part.setBody(QJsonDocument(value.toObject()).toJson());

    qhttp_multipart->append(part);
}

template<typename ValueType>
    requires Utility::hasMethod_toByteArray<ValueType>
void Utility::QHttpMultiPartInserter::insert(const QString& key, ValueType&& value) {

    QHttpPart part;
    part.setHeader(QNetworkRequest::ContentDispositionHeader, QStringLiteral("form-data; name=\"%1\"").arg(key));
    
    if constexpr (std::is_pointer_v<ValueType>) {
        part.setBody(value.toByteArray());
    }
    else part.setBody(value->toByteArray());

    qhttp_multipart->append(part);
}

template<typename QEnumType>
    requires std::is_enum_v<Utility::remove_pcvref<QEnumType>>
void Utility::QHttpMultiPartInserter::insert(const QString& key, QEnumType&& qenum) {

    QHttpPart part;
    part.setHeader(QNetworkRequest::ContentDispositionHeader, QStringLiteral("form-data; name=\"%1\"").arg(key));
    
    if constexpr (std::is_pointer_v<QEnumType>) {
        part.setBody(QString(QMetaEnum::fromType<Utility::remove_pcvref<QEnumType>>()
            .valueToKey(static_cast<int>(*qenum)))
            .toLower()
            .toUtf8()
        );
    }
    else {
        part.setBody(QString(QMetaEnum::fromType<Utility::remove_pcvref<QEnumType>>()
            .valueToKey(static_cast<int>(qenum)))
            .toLower()
            .toUtf8()
        );
    }

    qhttp_multipart->append(part);
}

template<typename QVectorType>
void Utility::QHttpMultiPartInserter::insert(const QString& key, const QVector<QVectorType>& qvector) {
    
    insert(key, QJsonArrayInserter::make(qvector.begin(), qvector.end()));
}

template<typename OptionalType>
void Utility::QHttpMultiPartInserter::insert(const QString& key, const std::optional<OptionalType>& optional) {
    
    if (optional.has_value()) {

        if constexpr (std::is_pointer_v<OptionalType>) {
            insert(key, *optional.value());
        }
        else insert(key, optional.value());
    }
}

template<typename... VariantTypes>
void Utility::QHttpMultiPartInserter::insert(const QString& key, const std::variant<VariantTypes...>& variant) {
    
    std::visit([this, &key](auto&& value) {
        insert(key, value);
    }, variant);
}

#endif // TELEGRAM_UTILITY_QHTTPMULTIPARTINSERTER_H