#include "Internal/Utility/Utility.h"

#include <memory>

#include "qnetworkaccessmanager.h"
#include "qnetworkrequest.h"
#include "qnetworkreply.h"
#include "qeventloop.h"


QByteArray Utility::Network::post(const QJsonDocument& body, const QUrl& url) {
    QNetworkAccessManager network_access_manager;

    QNetworkRequest request(url);
    request.setTransferTimeout(REQUEST_TIMEOUT.count());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QEventLoop event_loop;
    std::unique_ptr<QNetworkReply> reply(network_access_manager.post(request, body.toJson()));

    QObject::connect(reply.get(), &QNetworkReply::finished, &event_loop, &QEventLoop::quit);
    event_loop.exec();

    return reply->readAll();
}

QByteArray Utility::Network::post(QHttpMultiPart* body, const QUrl& url) {
    QNetworkAccessManager network_access_manager;

    QNetworkRequest request(url);
    request.setTransferTimeout(REQUEST_TIMEOUT.count());

    QEventLoop event_loop;
    std::unique_ptr<QNetworkReply> reply(network_access_manager.post(request, body));

    QObject::connect(reply.get(), &QNetworkReply::finished, &event_loop, &QEventLoop::quit);
    event_loop.exec();

    return reply->readAll();
}

QByteArray Utility::Network::get(const QUrl& request_url, const QUrlQuery& url_query) {
    QNetworkAccessManager network_access_manager;

    QUrl request_url_with_query = request_url;
    request_url_with_query.setQuery(url_query);

    QEventLoop event_loop;
    std::shared_ptr<QNetworkReply> reply(network_access_manager.get(QNetworkRequest(request_url)));

    QObject::connect(reply.get(), &QNetworkReply::finished, &event_loop, &QEventLoop::quit);
    event_loop.exec();

    return reply->readAll();
}