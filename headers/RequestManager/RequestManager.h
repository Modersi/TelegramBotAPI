#ifndef REQUESTMANAGER_H
#define REQUESTMANAGER_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QEventLoop>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QtNetwork/QHttpMultiPart>

// Ебануть приватные поля классов как std_unique ptr

class RequestManager
{
public:
    RequestManager(const QString);
    ~RequestManager();
    void setBotToken (const QString);
    QJsonDocument sendMultiPartRequest(const QString methodName, const QJsonDocument jsonDocument, QFile *file);
    QJsonDocument sendRequest(const QString methodName, const QJsonDocument jsonDocument);

private:
    QEventLoop* eventLoop;
    QString* botToken;
    QNetworkAccessManager* networkAccessManager;
};

#endif // REQUESTMANAGER_H
