#ifndef TELEGRAM_UTILITY_QVECTORINSERTER_H
#define TELEGRAM_UTILITY_QVECTORINSERTER_H

#include <functional>
#include <type_traits>
#include <ranges>

#include "qvector.h"
#include "qjsonarray.h"
#include "qjsonvalue.h"

namespace Utility {

    /**
     *
     * @brief This is a helper class that makes the insertion of different objects in QVector easier
     *
     *
     */

    template<typename VectorType>
    struct QVectorInserter {

        QVectorInserter(QVector<VectorType>& qvector);


        /** @brief Creates a new QVector with variadic amount of values. Args... should be insertable using QJsonArrayInserter */
        template<typename... Args>
        static QVector<VectorType> make(Args&&... values);
        

        /** @brief Inserts value that can be .push_back() in QVector */
        template<typename ValueType>
            requires std::is_same_v<VectorType, std::remove_cvref_t<std::remove_pointer_t<ValueType>>>
        void insert(ValueType&& value);

        /** @brief Inserts QJsonValueConstRef in QVector */
        void insert(const QJsonValueConstRef& value);

        /** @brief Inserts QJsonArray in QVector */
        void insert(const QJsonArray& values);

    private:
        std::reference_wrapper<QVector<VectorType>> qvector;
    };
}

#include "Internal/Utility/QVectorInserter.hpp"

#endif // TELEGRAM_UTILITY_QVECTORINSERTER_H