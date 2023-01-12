#ifndef TELEGRAM_REQUESTMANAGER_H
#define TELEGRAM_REQUESTMANAGER_H

#include "qfile.h"
#include "qurl.h"
#include "qurlquery.h"

namespace Telegram 
{
	namespace Internal 
	{
		struct RequestManager 
		{
			static QByteArray sendPostRequest(const QJsonDocument& request_json, const QUrl& request_url);

			static QByteArray sendPostRequest(const QVector<QPair<QString, QFile*>>& file_name_and_file_pairs, const QVector<QPair<QString, QVariant>>& key_value_pairs, const QUrl& request_url);

			static QByteArray sendGetRequest(const QUrl& request_url, const QUrlQuery& url_query = {});
		};
	}
}

#endif // TELEGRAM_REQUESTMANAGER_H
