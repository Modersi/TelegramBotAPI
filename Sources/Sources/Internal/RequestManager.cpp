#include "Internal/RequestManager.h"

#include "qnetworkreply.h"
#include "qnetworkrequest.h"
#include "qhttpmultipart.h"
#include "qmimedatabase.h"
#include "qmimetype.h"
#include "qurl.h"
#include "qurlquery.h"
#include "qfile.h"
#include "qjsondocument.h"
#include "qbytearray.h"

#define REQUEST_TIMEOUT_MS 15000

Telegram::RequestManager::RequestManager() :
    networkAccessManager(std::make_unique<QNetworkAccessManager>()),
    eventLoop(std::make_unique<QEventLoop>()),
    requestTimeoutTimer(std::make_unique<QTimer>()),
    QObject()
{
    /* If request is finished and reply is received - quit the event loop where request was handled */
    QObject::connect(networkAccessManager.get(), &QNetworkAccessManager::finished,
        eventLoop.get(), &QEventLoop::quit);

    /* If request is finished and reply is received - stop request timeout timer(thus prevent troubles with sending couple requests in a row) */
    QObject::connect(networkAccessManager.get(), &QNetworkAccessManager::finished,
        requestTimeoutTimer.get(), &QTimer::stop);

    /* If request timeout timer over - quit the event loop where request was handled(thus stop request) */
    QObject::connect(requestTimeoutTimer.get(), &QTimer::timeout,
        eventLoop.get(), &QEventLoop::quit);
}

QByteArray Telegram::RequestManager::SendPostRequest(const QJsonDocument& requestBody, const QUrl& requestURL) const
{
    /* Creating request and setting it's headers */
    QNetworkRequest request(requestURL);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    /* Sending request and executing event loop in which request is proceed */
    requestTimeoutTimer->start(REQUEST_TIMEOUT_MS); // Request timeout timer. Stop the request if there is no response within REQUEST_TIMEOUT_MS
    QNetworkReply* reply = networkAccessManager->post(request, requestBody.toJson());
    eventLoop->exec();

    reply->deleteLater();
    return reply->readAll();
}

QByteArray Telegram::RequestManager::SendPostRequest(const QVector<QPair<QString, QFile*>>& filesToUpload, const QVector<QPair<QString, QVariant>>& parameters, const QUrl& requestURL) const
{
    /* Creating multipart/form-data request */
    QNetworkRequest request(requestURL);
    QHttpMultiPart* requestBody = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    /* Adding files to request body */
    for (auto& file : filesToUpload)
    {
        QHttpPart filePart;

        filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QString("form-data; name=\"%1\"; filename=\"%2\"").arg(file.first).arg(file.second->fileName()));
        filePart.setBodyDevice(file.second);
        
        requestBody->append(filePart);
    }

    /* Adding parameters to request body */
    for (auto& parametr : parameters)
    {
        QHttpPart parametrPart;
        parametrPart.setHeader(QNetworkRequest::ContentDispositionHeader, QString("form-data; name=\"%1\"").arg(parametr.first));

        if (parametr.second.canConvert<QJsonObject>())      parametrPart.setBody(QJsonDocument(parametr.second.toJsonObject()).toJson());
        else if (parametr.second.canConvert<QJsonArray>())  parametrPart.setBody(QJsonDocument(parametr.second.toJsonArray()).toJson());
        else                                                parametrPart.setBody(parametr.second.toByteArray());

        requestBody->append(parametrPart);
    }

    /* Sending request and executing event loop in which request is proceed */
    requestTimeoutTimer->start(REQUEST_TIMEOUT_MS); // Request timeout timer. Stop the request if there is no response within REQUEST_TIMEOUT_MS
    QNetworkReply* reply = networkAccessManager->post(request, requestBody);;
    eventLoop->exec();   

    /* Deleting requestBody via setting reply as it parent; Deleting reply later */
    requestBody->setParent(reply);
    reply->deleteLater();

    return reply->readAll();
}

//QByteArray Telegram::RequestManager::SendPostRequest(const QVector<QPair<QVariant, QVariant>>& parameters, const QUrl& requestURL) const
//{
//    /* Creating request and setting its headers */
//    QNetworkRequest request(requestURL);
//    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
//
//    /* Creating request body and adding key-value parameters pairs to it. e.g: chat_id=2123123&message_type=default */
//    QString requestBody("");
//    for (const auto& parameter : parameters)
//        requestBody += parameter.first.toString() + '=' + parameter.second.toString() + '&';
//
//    /* Sending request and executing event loop in which request is proceed */
//    requestTimeoutTimer->start(REQUEST_TIMEOUT_MS); // Request timeout timer. Stop the request if there is no response within REQUEST_TIMEOUT_MS
//    QNetworkReply* reply = networkAccessManager->post(request, requestBody.toUtf8());
//    eventLoop->exec();
//
//    reply->deleteLater();
//    return reply->readAll();
//}

QByteArray Telegram::RequestManager::SendGetRequest(const QUrlQuery& requestURLQuery, const QUrl& requestURL) const
{
    /* Creating request and setting URL query string */
    QNetworkRequest request(requestURL.toString() + '?' + requestURLQuery.toString());

    /* Sending request and executing event loop in which request is proceed */
    requestTimeoutTimer->start(REQUEST_TIMEOUT_MS); // Request timeout timer. Stop the request if there is no response within REQUEST_TIMEOUT_MS
    QNetworkReply* reply = networkAccessManager->get(request);
    eventLoop->exec();

    reply->deleteLater();
    return reply->readAll();
}