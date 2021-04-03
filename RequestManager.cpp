#include "RequestManager.h"

RequestManager::RequestManager(const QString _botToken)
{
    botToken = new QString();
    *botToken = _botToken;

    networkAccessManager = new QNetworkAccessManager();

    eventLoop = new QEventLoop();
    connect(networkAccessManager, SIGNAL(finished(QNetworkReply*)),
            eventLoop, SLOT(quit())
            );
}

RequestManager::~RequestManager()
{
    delete botToken;
    delete networkAccessManager;
    delete eventLoop;
}

void RequestManager::setBotToken(const QString _botToken)
{
    *botToken = _botToken;
}

QJsonDocument RequestManager::sendMultiPartRequest(const QString methodName, const QJsonDocument jsonDocument, QFile *file)
{
    QString url = "https://api.telegram.org/bot" + *botToken + '/';

    QNetworkRequest* request = new QNetworkRequest(QUrl(url + methodName));

    QHttpMultiPart multiPartBody(QHttpMultiPart::FormDataType);

    QHttpPart textPart;
    textPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"chat_id\""));
    textPart.setBody("424830375");

    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/png"));
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"photo\"; filename=\"\""));
    imagePart.setBody(file->readAll());

    multiPartBody.append(textPart);
    multiPartBody.append(imagePart);

    QNetworkReply *reply = networkAccessManager->post(*request, &multiPartBody);
    eventLoop->exec();

    if(reply->error() != QNetworkReply::NoError)
        emit error();

    reply->deleteLater();
    delete request;

    qDebug() << reply->readAll();

    return QJsonDocument::fromJson(reply->readAll());
}

QJsonDocument RequestManager::sendRequest(const QString methodName, const QJsonDocument jsonDocument)
{
    QString url = "https://api.telegram.org/bot" + *botToken + '/';

    QNetworkRequest* request = new QNetworkRequest(QUrl(url + methodName));
    request->setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = networkAccessManager->post(*request, jsonDocument.toJson());
    eventLoop->exec();

    if(reply->error() != QNetworkReply::NoError)
        emit error();

    reply->deleteLater();
    delete request;

    return QJsonDocument::fromJson(reply->readAll());
}
