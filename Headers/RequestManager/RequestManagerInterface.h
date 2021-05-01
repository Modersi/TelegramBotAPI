#ifndef REQUESTMANAGERINTERFACE_H
#define REQUESTMANAGERINTERFACE_H

//class QByteArray;
//class QUrl;
//class QJsonDocument;
//class QFile;

struct RequestManagerInterface
{
    /*! 
        \brief application/json type request
        \param QString          String which is contain request URL, should look like this: https://api.telegram.org/bot123456:ABC-DEF1234ghIkl-zyx57W2v1u123ew11/getMe
        \param QJsonDocument    Request body in form of JSON
    */
    virtual QByteArray SendPostRequest(const QUrl requestURL, const QJsonDocument *requestJSON) const = 0;

    /*!
        \brief multipart/form-data type request
        \param QString          String which is contain request URL, should look like this: https://api.telegram.org/bot123456:ABC-DEF1234ghIkl-zyx57W2v1u123ew11/getMe
        \param QJsonDocument    Request body in form of JSON
        \param QFile            File to attach to request
    */
    virtual QByteArray SendPostRequest(const QUrl requestURL, const QFile *file) const = 0;

    /*!
        \brief application/x-www-form-urlencoded type request
        \param QString          String which is contain request URL, should look like this: https://api.telegram.org/bot123456:ABC-DEF1234ghIkl-zyx57W2v1u123ew11/getMe
        \param QJsonDocument    Request body in form of JSON
        \param QFile            File to attach to request
    */
    virtual QByteArray SendPostRequest(const QUrl requestURL, const QUrlQuery requestURLQuery) const = 0; // Раздуплить использовать ли здесь init_list или не выебываца и просто передавать QUrlQuery у которого в свою очередь есть конструктор пригнимающий init_list и вообще нахуй надо ли надо этот метод да
};

#endif // REQUESTMANAGERINTERFACE_H
