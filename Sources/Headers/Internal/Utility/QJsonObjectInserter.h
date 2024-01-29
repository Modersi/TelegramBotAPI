#ifndef TELEGRAM_UTILITY_QJSONOBJECTINSERTER_H
#define TELEGRAM_UTILITY_QJSONOBJECTINSERTER_H

#include "Internal/Utility/Utility.h"
#include "Internal/Utility/QJsonArrayInserter.h"

#include <functional>
#include <string>
#include <variant>
#include <span>
#include <type_traits>
#include <optional>

#include "qjsonobject.h"
#include "qstring.h"
#include "qvector.h"
#include "qmetaobject.h"
#include "qjsonarray.h"

namespace Utility { 
    
    /**
     *
     * @brief This is a helper class that makes the insertion of different objects in QHttpMultiPartInserter easier
     *
     *
     */

    struct QJsonObjectInserter {
  
        QJsonObjectInserter(QJsonObject& qjson_object);
    

        /** @brief Creates a new QJsonObject with variadic amount of key-value pairs. Args... should be insertable using QJsonArrayInserter */
        template<typename... Args>
        static QJsonObject make(std::span<QString> keys, Args&&... values);


        /** @brief Inserts value that can be converted to QJsonValue */
        template<typename ValueType>
            requires std::is_constructible_v<QJsonValue, Utility::remove_pcvref<ValueType>>
        void insert(const QString& key, ValueType&& value);
        
        /** @brief Inserts value that has .toObject() method */
        template<typename ValueType>
            requires hasMethod_toObject<ValueType>
        void insert(const QString& key, ValueType&& value);
        
        /** @brief Inserts QEnum value */
        template<typename QEnumType>
            requires std::is_enum_v<Utility::remove_pcvref<QEnumType>>
        void insert(const QString& key, QEnumType&& value);
        
        /** @brief Inserts QVector. QVectorType should be insertable using QJsonArrayInserter */
        template<typename QVectorType>
        void insert(const QString& key, const QVector<QVectorType>& qvector);
        
        /** @brief Inserts std::optional. OptionalType should be insertable using QJsonArrayInserter */
        template<typename OptionalType>
        void insert(const QString& key, const std::optional<OptionalType>& optional);
        
        /** @brief Inserts std::variant. VariantTypes should be insertable using QJsonArrayInserter */
        template<typename... VariantTypes>
        void insert(const QString& key, const std::variant<VariantTypes...>& variant_value);
        
        /** @brief Inserts std::string */
        void insert(const QString& key, const std::string& value);

    private:
        std::reference_wrapper<QJsonObject> qjson_object;
    };
}

#include "Internal/Utility/QJsonObjectInserter.hpp"

#endif // TELEGRAM_UTILITY_QJSONOBJECTINSERTER_H