#ifndef TELEGRAM_UTILITY_H
#define TELEGRAM_UTILITY_H

#include "qjsonobject.h"
#include "qjsondocument.h"
#include "qhttpmultipart.h"
#include "qurl.h"
#include "qurlquery.h"

#include <type_traits>
#include <span>
#include <chrono>

namespace Utility {

    template<typename Type>
    using remove_pcvref = std::remove_pointer_t<std::remove_cvref_t<Type>>;
    
    // Types that can be converted to QJsonObject via ValueType::toObject()
    template<typename ValueType>
    concept hasMethod_toObject = requires(remove_pcvref<ValueType> value) {
        value.toObject();
    };

    // Types that can be converted to QByteArray via ValueType::toByteArray()
    template<typename ValueType>
    concept hasMethod_toByteArray = requires(remove_pcvref<ValueType> value) {
        value.toByteArray();
    };

    namespace Network {

        // Timeout for all network requests
        static auto REQUEST_TIMEOUT = std::chrono::milliseconds(10000);

        // POST request with application/json content type
        QByteArray post(const QJsonDocument& body, const QUrl& url);

        // POST request with multipart/form-data content type
        QByteArray post(QHttpMultiPart* body, const QUrl& url);

        // GET request
        QByteArray get(const QUrl& request_url, const QUrlQuery& url_query = {});
    }
}

#endif // TELEGRAM_UTILITY_H