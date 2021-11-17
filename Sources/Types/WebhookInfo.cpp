#include "Types/WebhookInfo.h"

#include "qjsonobject.h"

#include "Internal/ConversionFunctions.h"

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

Telegram::WebhookInfo::WebhookInfo(const QJsonObject& jsonObject)
{
	jsonObject.contains("url")						? url = jsonObject["url"].toString()														: url = "";
	jsonObject.contains("has_custom_certificate")	? has_custom_certificate = jsonObject["has_custom_certificate"].toBool()					: has_custom_certificate = false;
	jsonObject.contains("pending_update_count")		? pending_update_count = jsonObject["pending_update_count"].toInt()							: pending_update_count = 0;
	jsonObject.contains("ip_address")				? ip_address = jsonObject["ip_address"].toString()											: ip_address = std::nullopt;
	jsonObject.contains("last_error_date")			? last_error_date = jsonObject["last_error_date"].toInt()									: last_error_date = std::nullopt;
	jsonObject.contains("last_error_message")		? last_error_message = jsonObject["last_error_message"].toString()							: last_error_message = std::nullopt;
	jsonObject.contains("max_connections")			? max_connections = jsonObject["max_connections"].toInt()									: max_connections = std::nullopt;
	jsonObject.contains("allowed_updates")			? allowed_updates = QJsonArrayToQVector<QString>(jsonObject["allowed_updates"].toArray())	: allowed_updates = std::nullopt;
}

QJsonObject Telegram::WebhookInfo::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	QJsonObject webhookInfoJsonObject{ {"url", url}, {"has_custom_certificate", has_custom_certificate}, {"pending_update_count", pending_update_count} };

	if (ip_address.has_value())			webhookInfoJsonObject.insert("ip_address", *ip_address);
	if (last_error_date.has_value())	webhookInfoJsonObject.insert("last_error_date", *last_error_date);
	if (last_error_message.has_value())	webhookInfoJsonObject.insert("last_error_message", *last_error_message);
	if (max_connections.has_value())	webhookInfoJsonObject.insert("max_connections", *max_connections);
	if (allowed_updates.has_value())	webhookInfoJsonObject.insert("allowed_updates", QVectorToQJsonArray(*allowed_updates));

	return webhookInfoJsonObject;
}

bool Telegram::WebhookInfo::isEmpty() const
{
	return url == ""
		   and has_custom_certificate == false
		   and pending_update_count == 0
		   and ip_address == std::nullopt
		   and last_error_date == std::nullopt
		   and last_error_message == std::nullopt
		   and max_connections == std::nullopt
		   and allowed_updates == std::nullopt;
}
