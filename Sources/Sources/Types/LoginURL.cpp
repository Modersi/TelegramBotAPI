#include "Types/LoginURL.h"

#include "qjsonobject.h"

Telegram::LoginURL::LoginURL() :
	url(),
	forward_text(),
	bot_username(),
	request_write_access()
{}

Telegram::LoginURL::LoginURL(const QString& url,
							 const std::optional<QString>& forward_text,
							 const std::optional<QString>& bot_username,
							 const std::optional<bool>& request_write_access) :
	url(url),
	forward_text(forward_text),
	bot_username(bot_username),
	request_write_access(request_write_access)
{}

Telegram::LoginURL::LoginURL(const QJsonObject& json_object) {
	json_object.contains("url")					 ? url = json_object["url"].toString()									: url = "";
	json_object.contains("forward_text")		 ? forward_text = json_object["forward_text"].toString()				: forward_text = std::nullopt;
	json_object.contains("bot_username")		 ? bot_username = json_object["bot_username"].toString()				: bot_username = std::nullopt;
	json_object.contains("request_write_access") ? request_write_access = json_object["request_write_access"].toBool()	: request_write_access = std::nullopt;
}

QJsonObject Telegram::LoginURL::toObject() const {
	if (isEmpty()) return {};

	QJsonObject login_url_json_object{ {"url", url} };

	if (forward_text.has_value())			login_url_json_object.insert("forward_text", *forward_text);
	if (bot_username.has_value())			login_url_json_object.insert("bot_username", *bot_username);
	if (request_write_access.has_value())	login_url_json_object.insert("request_write_access", *request_write_access);

	return login_url_json_object;
}

bool Telegram::LoginURL::isEmpty() const {
	return url == ""
		   and forward_text == std::nullopt
		   and bot_username == std::nullopt
		   and request_write_access == std::nullopt;
}
