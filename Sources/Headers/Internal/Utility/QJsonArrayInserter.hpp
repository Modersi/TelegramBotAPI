#ifndef TELEGRAM_UTILITY_QJSONARRAYINSERTER_HPP
#define TELEGRAM_UTILITY_QJSONARRAYINSERTER_HPP

#include "Internal/Utility/QJsonArrayInserter.h"

template<typename ...Args>
QJsonArray Utility::QJsonArrayInserter::make(Args&& ...values) {

    auto&& result = QJsonArray();
    auto&& inserter = QJsonArrayInserter(result);
    
    (inserter.insert(std::forward<decltype(values)>(values)), ...);

    return result;
}

template<typename Iterator>
    requires std::_Is_iterator_v<Iterator>
QJsonArray Utility::QJsonArrayInserter::make(Iterator begin, Iterator end) {

    auto&& result = QJsonArray();
    auto&& inserter = QJsonArrayInserter(result);
 
    std::ranges::for_each(begin, end, [&inserter](auto&& element) {
        
        using IteratorValueType = typename std::iterator_traits<Iterator>::value_type;
        if constexpr (std::is_pointer_v<IteratorValueType>) {
            inserter.insert(*element);
        }
        else inserter.insert(element);
    });

    return result;
}

template<typename ValueType>
    requires std::is_constructible_v<QJsonValue, Utility::remove_pcvref<ValueType>>
void Utility::QJsonArrayInserter::insert(ValueType&& value) {

    if constexpr (std::is_pointer_v<ValueType>) {
        qjson_array.get().push_back(*value);
    }
    else qjson_array.get().push_back(value);
}

template<typename ValueType>
    requires Utility::hasMethod_toObject<ValueType>
void Utility::QJsonArrayInserter::insert(ValueType&& value) {

    if constexpr (std::is_pointer_v<ValueType>) {
        qjson_array.get().push_back(value->toObject());
    }
    else qjson_array.get().push_back(value.toObject());
}

template<typename QVectorType>
void Utility::QJsonArrayInserter::insert(const QVector<QVectorType>& qvector) {

    qjson_array.get().push_back(QJsonArrayInserter::make(qvector.begin(), qvector.end()));
}

#endif // TELEGRAM_UTILITY_QJSONARRAYINSERTER_HPP