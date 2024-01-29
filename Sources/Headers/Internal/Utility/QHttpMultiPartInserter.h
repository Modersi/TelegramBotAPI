#ifndef TELEGRAM_UTILITY_QHTTPMULTIPARTINSERTER_H
#define TELEGRAM_UTILITY_QHTTPMULTIPARTINSERTER_H

#include "Internal/Utility/Utility.h"
#include "Internal/Utility/QJsonArrayInserter.h"

#include <optional>
#include <type_traits>
#include <span>
#include <variant>
#include <memory>

#include "qhttpmultipart.h"
#include "qjsonarray.h"
#include "qjsondocument.h"
#include "qvariant.h"
#include "qvector.h"
#include "qstring.h"
#include "qfile.h"
#include "qbytearray.h"
#include "qmetaobject.h"

namespace Utility {

    /**
     *
     * @brief This is a helper class that makes the insertion of different objects in QHttpMultiPartInserter easier
     *
     *
     */

    struct QHttpMultiPartInserter {
    
        QHttpMultiPartInserter(QHttpMultiPart* qhttp_multipart);
    

        /** @brief Creates a new QHttpMultiPart with variadic amount of key-value pairs. Args... should be insertable using QHttpMultiPartInserter */
        template<typename... Args>
        static std::unique_ptr<QHttpMultiPart> make(std::span<QString> keys, Args&&... values);


        /** @brief Inserts value that can be converted to QVariant */
        template<typename ValueType>
            requires std::is_constructible_v<QVariant, Utility::remove_pcvref<ValueType>>
        void insert(const QString& key, ValueType&& value);

        /** @brief Inserts value that has .toObject() method */
        template<typename ValueType>
            requires hasMethod_toObject<ValueType>
        void insert(const QString& key, ValueType&& value);

        /** @brief Inserts value that has .toByteArray() method */
        template<typename ValueType>
            requires hasMethod_toByteArray<ValueType>
        void insert(const QString& key, ValueType&& value);

        /** @brief Inserts QEnum value */
        template<typename QEnumType>
            requires std::is_enum_v<Utility::remove_pcvref<QEnumType>>
        void insert(const QString& key, QEnumType&& qenum);
    
        /** @brief Inserts QFile. QFile should be opened */
        void insert(const QString& key, QFile* qfile);
    
        /** @brief Inserts QVector. QVectorType should be insertable using QHttpMultiPartInserter */
        template<typename QVectorType>
        void insert(const QString& key, const QVector<QVectorType>& qvector);

        /** @brief Inserts std::optional. OptionalType should be insertable using QHttpMultiPartInserter */
        template<typename OptionalType>
        void insert(const QString& key, const std::optional<OptionalType>& optional);
    
        /** @brief Inserts std::variant. VariantTypes... should be insertable using QHttpMultiPartInserter */
        template<typename... VariantTypes>
        void insert(const QString& key, const std::variant<VariantTypes...>& variant);

    private:
        QHttpMultiPart* qhttp_multipart;
    };
}

#include "Internal/Utility/QHttpMultiPartInserter.hpp"

#endif // TELEGRAM_UTILITY_QHTTPMULTIPARTINSERTER_H