#include "Types/WebhookInfo.h"

#include "Internal/Utility/QJsonArrayInserter.h"
#include "Internal/Utility/QVectorInserter.h"

Telegram::WebhookInfo::WebhookInfo() :
	url(),
	has_custom_certificate(),
	pending_update_count(),
	ip_address(),
	last_error_date(),
	last_error_message(),
	max_connections(),
	allowed_updates()
{}

Telegram::WebhookInfo::WebhookInfo(const QString& url,
								   const bool& has_custom_certificate,
								   const qint32& pending_update_count,
								   const std::optional<QString>& ip_address,
								   const std::optional<qint32>& last_error_date,
								   const std::optional<QString>& last_error_message,
								   const std::optional<qint32>& max_connections,
								   const std::optional<QVector<QString>>& allowed_updates) :
	url(url),
	has_custom_certificate(has_custom_certificate),
	pending_update_count(pending_update_count),
	ip_address(ip_address),
	last_error_date(last_error_date),
	last_error_message(last_error_message),
	max_connections(max_connections),
	allowed_updates(allowed_updates)
{}

Telegram::WebhookInfo::WebhookInfo(const QJsonObject& json_object)
{
	json_object.contains("url")						? url = json_object["url"].toString()																	: url = "";
	json_object.contains("has_custom_certificate")	? has_custom_certificate = json_object["has_custom_certificate"].toBool()								: has_custom_certificate = false;
	json_object.contains("pending_update_count")	? pending_update_count = json_object["pending_update_count"].toInt()									: pending_update_count = 0;
	json_object.contains("ip_address")				? ip_address = json_object["ip_address"].toString()														: ip_address = std::nullopt;
	json_object.contains("last_error_date")			? last_error_date = json_object["last_error_date"].toInt()												: last_error_date = std::nullopt;
	json_object.contains("last_error_message")		? last_error_message = json_object["last_error_message"].toString()										: last_error_message = std::nullopt;
	json_object.contains("max_connections")			? max_connections = json_object["max_connections"].toInt()												: max_connections = std::nullopt;
	json_object.contains("allowed_updates")			? allowed_updates = Utility::QVectorInserter<QString>::make(json_object["allowed_updates"].toArray())	: allowed_updates = std::nullopt;
}

QJsonObject Telegram::WebhookInfo::toObject() const {
	if (isEmpty()) return {};

	QJsonObject webhook_info_json_object{ {"url", url}, {"has_custom_certificate", has_custom_certificate}, {"pending_update_count", pending_update_count} };

	if (ip_address.has_value())			webhook_info_json_object.insert("ip_address", *ip_address);
	if (last_error_date.has_value())	webhook_info_json_object.insert("last_error_date", *last_error_date);
	if (last_error_message.has_value())	webhook_info_json_object.insert("last_error_message", *last_error_message);
	if (max_connections.has_value())	webhook_info_json_object.insert("max_connections", *max_connections);
	if (allowed_updates.has_value())	webhook_info_json_object.insert("allowed_updates", Utility::QJsonArrayInserter::make(*allowed_updates));

	return webhook_info_json_object;
}

bool Telegram::WebhookInfo::isEmpty() const {
	return url == ""
		   and has_custom_certificate == false
		   and pending_update_count == 0
		   and ip_address == std::nullopt
		   and last_error_date == std::nullopt
		   and last_error_message == std::nullopt
		   and max_connections == std::nullopt
		   and allowed_updates == std::nullopt;
}
