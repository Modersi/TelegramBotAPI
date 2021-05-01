#include "..\..\Headers\RequestManager\RequestManager.h"

RequestManager::RequestManager() :
    networkAccessManager(new QNetworkAccessManager()),
    asynchronousSystem(new Asynchronous())
{
    /* Connect request finish signal to lambda which write request reply data to our "buffer" and freeing reply variable memory */
    QObject::connect(RequestManager::GetInstance().networkAccessManager.get(), &QNetworkAccessManager::finished,
                     this, [this](QNetworkReply* reply)
                           {
                               if(reply->error() == QNetworkReply::NoError) // If no errors occured - write reply to buffer, otherwise - write error string to buffer
                                   asynchronousSystem->replyBuffer = reply->readAll();
                               else                  
                                   asynchronousSystem->replyBuffer = reply->errorString().toUtf8();

                               reply->deleteLater();
                           });
}

void RequestManager::Asynchronous::SendPostRequest(const QJsonDocument& requestJSON, const QUrl& requestURL)
{
    /* Creating request and setting its headers */
    QNetworkRequest request(requestURL);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    /* Sending request with JSON document in body */
    QNetworkReply* reply = RequestManager::GetInstance().networkAccessManager->post(request, requestJSON.toJson());
}

void RequestManager::Asynchronous::SendPostRequest(const QFile* file, const QUrl& requestURL)
{
}

void RequestManager::Asynchronous::SendPostRequest(const QUrlQuery& requestURLQuery, const QUrl& requestURL)
{
    /* Creating request and setting URL query string */
    QNetworkRequest request(requestURL);

    /* Sending request */
    QNetworkReply* reply = RequestManager::GetInstance().networkAccessManager->post(request, requestURLQuery.toString().toUtf8());
}

void RequestManager::Asynchronous::SendGetRequest(const QUrlQuery& requestURLQuery, const QUrl& requestURL)
{
    /* Creating request and setting URL query string */
    QNetworkRequest request(requestURL.toString() + '?' + requestURLQuery.toString());

    /* Sending request */
    QNetworkReply* reply = RequestManager::GetInstance().networkAccessManager->get(request);
}

QByteArray RequestManager::Asynchronous::GetLastRequestReply()
{
    return RequestManager::GetInstance().asynchronousSystem->replyBuffer;
}


