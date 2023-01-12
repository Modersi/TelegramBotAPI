#include "Internal/RequestManager.h"

#include <memory>

#include "qnetworkaccessmanager.h"
#include "qnetworkreply.h"
#include "qnetworkrequest.h"
#include "qhttpmultipart.h"
#include "qeventloop.h"
#include "qjsondocument.h"
#include "qjsonobject.h"
#include "qjsonarray.h"
#include "qbytearray.h"

#define REQUEST_TIMEOUT_MS 1500

QByteArray Telegram::Internal::RequestManager::sendPostRequest(const QJsonDocument& request_json, const QUrl& request_url) {
    QNetworkAccessManager network_access_manager;

    QNetworkRequest request(request_url);
    request.setTransferTimeout(REQUEST_TIMEOUT_MS);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QEventLoop event_loop;
    std::shared_ptr<QNetworkReply> reply(network_access_manager.post(request, request_json.toJson()));

    QObject::connect(reply.get(), &QNetworkReply::finished, &event_loop, &QEventLoop::quit);
    event_loop.exec();

    return reply->readAll();
}

QByteArray Telegram::Internal::RequestManager::sendPostRequest(const QVector<QPair<QString, QFile*>>& file_name_and_file_pairs, const QVector<QPair<QString, QVariant>>& key_value_pairs, const QUrl& request_url) {    
    QNetworkAccessManager network_access_manager;

    QNetworkRequest request(request_url);
    request.setTransferTimeout(REQUEST_TIMEOUT_MS);

    QHttpMultiPart* requestBody = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    for (auto&&[file_name, file] : file_name_and_file_pairs) {
        QHttpPart file_part;

        file_part.setHeader(QNetworkRequest::ContentDispositionHeader, QString("form-data; name=\"%1\"; filename=\"%2\"").arg(file_name).arg(file->fileName()));
        file_part.setBodyDevice(file);

        requestBody->append(file_part);
    }
    for (auto&&[key, value] : key_value_pairs) {
        QHttpPart parameter_part;
        parameter_part.setHeader(QNetworkRequest::ContentDispositionHeader, QString("form-data; name=\"%1\"").arg(key));

        if (value.canConvert<QJsonObject>())      parameter_part.setBody(QJsonDocument(value.toJsonObject()).toJson());
        else if (value.canConvert<QJsonArray>())  parameter_part.setBody(QJsonDocument(value.toJsonArray()).toJson());
        else                                      parameter_part.setBody(value.toByteArray());

        requestBody->append(parameter_part);
    }

    QEventLoop event_loop;
    std::shared_ptr<QNetworkReply> reply(network_access_manager.post(request, requestBody));

    QObject::connect(reply.get(), &QNetworkReply::finished, &event_loop, &QEventLoop::quit);
    event_loop.exec();

    requestBody->setParent(reply.get());
    return reply->readAll();
}

QByteArray Telegram::Internal::RequestManager::sendGetRequest(const QUrl& request_url, const QUrlQuery& url_query) {
    QNetworkAccessManager network_access_manager;
    
    QUrl request_url_with_query = request_url;
    request_url_with_query.setQuery(url_query);

    QEventLoop event_loop;
    std::shared_ptr<QNetworkReply> reply(network_access_manager.get(QNetworkRequest(request_url)));

    QObject::connect(reply.get(), &QNetworkReply::finished, &event_loop, &QEventLoop::quit);
    event_loop.exec();

    return reply->readAll();
}