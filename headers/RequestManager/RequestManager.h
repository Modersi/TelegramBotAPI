#ifndef DEFAULTREQUESTMANAGER_H
#define DEFAULTREQUESTMANAGER_H

#include "RequestManagerInterface.h"

#include <QObject>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QtNetwork>
#include "qbytearray.h"

class RequestManager : public QObject
{
	Q_OBJECT

public:
	inline static RequestManager& GetInstance() { static RequestManager requestManagerInstance; return requestManagerInstance; }

	RequestManager(const RequestManager&) = delete;
	void operator = (const RequestManager&) = delete;

protected:
	QScopedPointer<QNetworkAccessManager> networkAccessManager;

	/* @brief Asynchronous requests. To get request reply u should use GetLastRepquestReply(); */
	struct Asynchronous
	{
		friend class RequestManager;

		/**
		 * @brief Send application/json type post request, used to send most of requests
		 * @param QJsonDocument    Request body in form of JSON 
		 * @param QUrl             Request URL, it should look like this: https://api.telegram.org/bot<token>/METHOD_NAME
		 */
		static void SendPostRequest(const QJsonDocument& requestJSON, const QUrl& requestURL);

		/**
		 * @brief Send multipart/form-data type post request, used to upload files
		 * @param QFile		File to upload
		 * @param QUrl		Request URL, it should look like this: https://api.telegram.org/bot<token>/METHOD_NAME
		 */
		static void SendPostRequest(const QFile* file, const QUrl& requestURL);

		/**
		 * @briefbrief Send application/x-www-form-urlencoded type post request
		 * @paramparam QUrlQuery		
		 * @paramparam QUrl             Request URL, it should look like this: https://api.telegram.org/bot<token>/METHOD_NAME
		 */
		static void SendPostRequest(const QUrlQuery& requestURLQuery, const QUrl& requestURL);

		/**
		 * @brief Send get request
		 * @param QUrl			Request URL, it should look like this: https://api.telegram.org/bot<token>/METHOD_NAME
		 * @param QUrlQuery		Request body in form of JSON
		 */
		static void SendGetRequest(const QUrlQuery& requestURLQuery, const QUrl& requestURL);

		/**
		 * @brief Get last sended request reply
		 * @returns Reply given on last request, in form of QByteArray
		 */
		static QByteArray GetLastRequestReply();


	private:
		Asynchronous() : replyBuffer("Reply buffer is empty") {};

		QByteArray replyBuffer; // Holds reply given to last request
	};

	/* @brief Synchronous requests. Struct method's return request reply  */
	struct Synchronous
	{
		/**
		 * @brief Send application/json type post request, used to send most of requests
		 * @param QUrl             Request URL, it should look like this: https://api.telegram.org/bot<token>/METHOD_NAME
		 * @param QJsonDocument    Request body in form of JSON
		 */

		static void SendPostRequest(const QJsonDocument& requestJSON, const QUrl& requestURL);

		/**
		 * @brief Send multipart/form-data type post request, used to upload files
		 * @param QUrl		Request URL, it should look like this: https://api.telegram.org/bot<token>/METHOD_NAME
		 * @param QFile	File to upload
		 */
		static void SendPostRequest(const QFile* file, const QUrl& requestURL);

		/**
		 * @briefbrief Send application/x-www-form-urlencoded type post request
		 * @paramparam QUrl             Request URL, it should look like this: https://api.telegram.org/bot<token>/METHOD_NAME
		 * @paramparam QJsonDocument    Request body in form of JSON
		 */
		static void SendPostRequest(const QUrlQuery& requestURLQuery, const QUrl& requestURL);

		/**
		 * @brief Send get request
		 * @param QUrl			Request URL, it should look like this: https://api.telegram.org/bot<token>/METHOD_NAME
		 * @param QUrlQuery	Request body in form of JSON
		 */
		static void SendGetRequest(const QUrlQuery& requestURLQuery, const QUrl& requestURL);
	};

private:
	RequestManager();

	QScopedPointer<Asynchronous> asynchronousSystem;
};

#endif // DEFAULTREQUESTMANAGER_H
