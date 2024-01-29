#ifndef TELEGRAM_UTILITY_QJSONARRAYINSERTER_H
#define TELEGRAM_UTILITY_QJSONARRAYINSERTER_H

#include "Internal/Utility/Utility.h"

#include <iterator>
#include <functional>

#include "qvector.h"
#include "qjsonarray.h"
#include "qjsonvalue.h"

namespace Utility {

    /**
     *
     * @brief This is a helper class that makes the insertion of different objects in QJsonArray easier 
     *
     *
     */

    struct QJsonArrayInserter {

        QJsonArrayInserter(QJsonArray& qjson_array);


        /** @brief Creates a new QJsonArray with variadic amount of values. Args... should be insertable using QJsonArrayInserter */
        template<typename... Args>
        static QJsonArray make(Args&&... values);

        /** @brief Creates a new QJsonArray with the contents of the range [first, last) */
        template<typename Iterator>
            requires std::_Is_iterator_v<Iterator>
        static QJsonArray make(Iterator begin, Iterator end);


        /** @brief Inserts value that can be converted to QJsonValue */
        template<typename ValueType>
            requires std::is_constructible_v<QJsonValue, Utility::remove_pcvref<ValueType>>
        void insert(ValueType&& value);
        
        /** @brief Inserts value that has .toObject() method */
        template<typename ValueType>
            requires hasMethod_toObject<ValueType>
        void insert(ValueType&& value);

        /** @brief Inserts QVector. QVectorType should be insertable using QJsonArrayInserter */
        template<typename QVectorType>
        void insert(const QVector<QVectorType>& values);
      
    private:
        std::reference_wrapper<QJsonArray> qjson_array;
    };
}

#include "Internal/Utility/QJsonArrayInserter.hpp"

#endif // TELEGRAM_UTILITY_QJSONARRAYINSERTER_H