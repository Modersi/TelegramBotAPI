#ifndef TELEGRAM_UTILITY_QVECTORINSERTER_HPP
#define TELEGRAM_UTILITY_QVECTORINSERTER_HPP

#include "Internal/Utility/QVectorInserter.h"

template<typename VectorType>
Utility::QVectorInserter<VectorType>::QVectorInserter(QVector<VectorType>& qvector) :
	qvector(qvector)
{}

template<typename VectorType> 
template<typename... Args>
QVector<VectorType> Utility::QVectorInserter<VectorType>::make(Args&& ...values) {

    auto&& result = QVector<VectorType>();
    auto&& inserter = QVectorInserter<VectorType>(result);
    
    (inserter.insert(std::forward<decltype(values)>(values)), ...);
    
    return result;
}

template<typename VectorType>
template<typename ValueType>
    requires std::is_same_v<VectorType, std::remove_cvref_t<std::remove_pointer_t<ValueType>>>
void Utility::QVectorInserter<VectorType>::insert(ValueType&& value) {
    
    if constexpr (std::is_pointer_v<ValueType>) {
        qvector.get().push_back(*value);
    }
    else qvector.get().push_back(value);
}

template<typename VectorType>
void Utility::QVectorInserter<VectorType>::insert(const QJsonValueConstRef& value) {

    if constexpr (std::is_same_v<VectorType, bool>) {
        qvector.get().push_back(value.toBool());
    }
    else if constexpr (std::is_same_v<VectorType, double>) {
        qvector.get().push_back(value.toDouble());
    }
    else if constexpr (std::is_same_v<VectorType, int>) {
        qvector.get().push_back(value.toInt());
    }
    else if constexpr (std::is_same_v<VectorType, qint64>) {
        qvector.get().push_back(value.toInteger());
    }
    else if constexpr (std::is_same_v<VectorType, QString>) {
        qvector.get().push_back(value.toString());
    }
    else if constexpr (std::is_constructible_v<VectorType, QJsonObject>) {
        qvector.get().push_back(VectorType(value.toObject()));
    }
}

template<typename VectorType>
void Utility::QVectorInserter<VectorType>::insert(const QJsonArray& values) {

    for (auto&& value : values)
       insert(value);
}

template<typename NestedVectorType>
struct Utility::QVectorInserter<QVector<NestedVectorType>> {

    QVectorInserter(QVector<QVector<NestedVectorType>>& nested_qvector) :
        qvector(nested_qvector)
    {}

    static QVector<QVector<NestedVectorType>> make(const QJsonArray& double_json_array) {

        auto&& result = QVector<QVector<NestedVectorType>>();

        for (auto&& nested_array : double_json_array) {
            if (nested_array.isArray()) {
                result.push_back(QVectorInserter<NestedVectorType>::make(nested_array.toArray()));
            }
        }

        return result;
    }

private:
    std::reference_wrapper<QVector<QVector<NestedVectorType>>> qvector;
};

#endif // TELEGRAM_UTILITY_QVECTORINSERTER_HPP