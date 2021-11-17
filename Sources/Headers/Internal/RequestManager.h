#ifndef TELEGRAM_REQUESTMANAGER_H
#define TELEGRAM_REQUESTMANAGER_H

#include <memory>

#include "qobject.h"
#include "qtimer.h"
#include "qnetworkaccessmanager.h"
#include "qeventloop.h"
class QFile;
class QUrl;
class QUrlQuery;

namespace Telegram
{
	class RequestManager : public QObject
	{
		Q_OBJECT

	public:
		RequestManager();

		/** @brief Sends application/json type post request, used to send most of requests
		 *
		 * @param QJsonDocument    Request body in form of JSON. Pass Telegram API methods parameters(e.g chat_id="1023521", message_id="565132135") in it
		 * @param QUrl             Request URL, it should look like this: https://api.telegram.org/bot<token>/METHOD_NAME */
		QByteArray SendPostRequest(const QJsonDocument& requestBody, const QUrl& requestURL) const;

		/** @brief Sends multipart/form-data type post request, used to upload files
		 *
		 * @param QFile												File to upload. Should be opened
		 * @param std::initializer_list<QPair<QVariant, QVariant>>	Telegram API methods parameters(e.g chat_id="1023521", message_id="565132135")
		 * @param QUrl												Request URL, it should look like this: https://api.telegram.org/bot<token>/METHOD_NAME */
		QByteArray SendPostRequest(const QVector<QPair<QString, QFile*>>& filesToUpload, const QVector<QPair<QString, QVariant>>& parameters, const QUrl& requestURL) const;

		///** @brief Sends application/x-www-form-urlencoded type post request
		// *
		// * @param std::initializer_list<QPair<QVariant, QVariant>>	Telegram API methods parameters(e.g chat_id="1023521", message_id="565132135")
		// * @param QUrl												Request URL, it should look like this: https://api.telegram.org/bot<token>/METHOD_NAME */
		//QByteArray SendPostRequest(const QVector<QPair<QVariant, QVariant>>& parameters, const QUrl& requestURL) const;

		/** @brief Sends get request
		 *
		 * @param QUrlQuery	Query string. Used to pass Telegram API methods parameters(e.g chat_id="1023521", message_id="565132135")
		 * @param QUrl		Request URL, it should look like this: https://api.telegram.org/bot<token>/METHOD_NAME */
		QByteArray SendGetRequest(const QUrlQuery& requestURLQuery, const QUrl& requestURL) const;

	private:
		std::unique_ptr<QNetworkAccessManager> networkAccessManager;
		std::unique_ptr<QEventLoop> eventLoop;
		std::unique_ptr<QTimer> requestTimeoutTimer; // ћб заменить на локальные и убрать указатели, хз
	};
}

#endif // TELEGRAM_REQUESTMANAGER_H
