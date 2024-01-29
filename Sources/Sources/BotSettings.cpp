#include "BotSettings.h"

#include <exception>

#include "qsslkey.h"
#include "qsslcertificate.h"
#include "qfile.h"
#include "qjsondocument.h"
#include "qjsonobject.h"
#include "qjsonarray.h"

#include "Internal/Utility/QVectorInserter.h"

Telegram::BotSettings::BotSettings() :
	bot_token(),
	webhook_url(),
	ssl_configuration(),
	public_key(),
	webhook_ip_addres(),
	max_connections(),
	allowed_updates(),
	host_addres(),
	port(),
	payment_token() {}

Telegram::BotSettings::BotSettings(const QString& bot_token,
								   const std::optional<QString> webhook_url,
								   const std::optional<QSslConfiguration> ssl_configuration,
								   const std::optional<std::shared_ptr<QFile>> public_key,
								   const std::optional<QString> webhook_ip_addres,
								   const std::optional<qint32> max_connections,
								   const std::optional<QVector<QString>>& allowed_updates,
								   const std::optional<QHostAddress>& host_addres,
								   const std::optional<quint16> port,
								   const std::optional<QString> payment_token) :
	bot_token(bot_token),
	webhook_url(webhook_url),
	ssl_configuration(ssl_configuration),
	public_key(public_key),
	webhook_ip_addres(webhook_ip_addres),
	max_connections(max_connections),
	allowed_updates(allowed_updates),
	host_addres(host_addres),
	port(port),
	payment_token(payment_token)
{}

void createDefaultBotSettingsFile(const QDir& file_path, const QString& file_name)
{
	if (!file_path.exists()) file_path.mkpath(file_path.absolutePath());

	if (auto bot_settings_file = std::make_shared<QFile>(file_path.filePath(file_name));
		bot_settings_file->open(QIODevice::WriteOnly))
	{
		auto empty_settings_json = QJsonObject {
			{"bot_token", ""},
			{"webhook_url", QJsonValue::Type::Null},
			{"certificate_path", QJsonValue::Type::Null},
			{"ca_certificates_paths", QJsonValue::Type::Null},
			{"private_key_path", QJsonValue::Type::Null},
			{"public_key_path", QJsonValue::Type::Null},
			{"webhook_ip_addres", QJsonValue::Type::Null},
			{"max_connections", QJsonValue::Type::Null},
			{"allowed_updates", QJsonValue::Type::Null},
			{"drop_pending_updates", QJsonValue::Type::Null},
			{"host_addres", QJsonValue::Type::Null},
			{"port", QJsonValue::Type::Null},
			{"payment_token", QJsonValue::Type::Null}
		};

		bot_settings_file->write(QJsonDocument(empty_settings_json).toJson());
	}

}

std::shared_ptr<Telegram::BotSettings> Telegram::BotSettings::makeFromFile(const QDir& bot_settings_file_path, const QString& bot_settings_file_name)
{
	if (QFile::exists(bot_settings_file_path.filePath(bot_settings_file_name)) == false)
		createDefaultBotSettingsFile(bot_settings_file_path, bot_settings_file_name);

	auto bot_settings_file = std::make_shared<QFile>(bot_settings_file_path.filePath(bot_settings_file_name));
	if (bot_settings_file->open(QIODevice::ReadOnly) == false) {
		throw std::logic_error("Can't open BotSettings file");
		return nullptr;
	}

	auto bot_settings = std::make_shared<BotSettings>();
	auto bot_settings_json = QJsonDocument::fromJson(bot_settings_file->readAll()).object();

	bot_settings->bot_token = bot_settings_json["bot_token"].toString();
	bot_settings_json["webhook_url"].isNull()			? bot_settings->webhook_url = std::nullopt			: bot_settings->webhook_url = bot_settings_json["webhook_url"].toString();
	bot_settings_json["webhook_ip_addres"].isNull()		? bot_settings->webhook_ip_addres = std::nullopt	: bot_settings->webhook_ip_addres = bot_settings_json["webhook_ip_addres"].toString();
	bot_settings_json["max_connections"].isNull()		? bot_settings->max_connections = std::nullopt		: bot_settings->max_connections = bot_settings_json["max_connections"].toInt();
	bot_settings_json["allowed_updates"].isNull()		? bot_settings->allowed_updates = std::nullopt		: bot_settings->allowed_updates = Utility::QVectorInserter<QString>::make(bot_settings_json["allowed_updates"].toArray());
	bot_settings_json["drop_pending_updates"].isNull()	? bot_settings->drop_pending_updates = std::nullopt : bot_settings->drop_pending_updates = bot_settings_json["drop_pending_updates"].toBool();
	bot_settings_json["host_addres"].isNull()			? bot_settings->host_addres = std::nullopt			: bot_settings->host_addres = QHostAddress(bot_settings_json["host_addres"].toString());
	bot_settings_json["port"].isNull()					? bot_settings->port = std::nullopt					: bot_settings->port = bot_settings_json["port"].toInt();
	bot_settings_json["payment_token"].isNull()			? bot_settings->payment_token = std::nullopt		: bot_settings->payment_token = bot_settings_json["payment_token"].toString();

	if (auto is_bot_use_webhook = !bot_settings_json["certificate_path"].isNull() or !bot_settings_json["ca_certificates_paths"].isNull() or !bot_settings_json["private_key_path"].isNull() or !bot_settings_json["public_key_path"].isNull();
		is_bot_use_webhook == true)
	{
		bot_settings->ssl_configuration.emplace();

		if (bot_settings_json["certificate_path"].isNull() == false)
		{
			if (auto certificate_file = std::make_shared<QFile>(bot_settings_json["certificate_path"].toString());
				certificate_file->open(QIODevice::ReadOnly))
			{
				bot_settings->ssl_configuration->setLocalCertificate(QSslCertificate(certificate_file->readAll()));
			}
		}

		if (bot_settings_json["ca_certificates_paths"].isNull() == false)
		{
			for (auto&& ca_certificate_file_path : bot_settings_json["ca_certificates_paths"].toArray())
			{
				if (auto ca_certificate_file = std::make_shared<QFile>(ca_certificate_file_path.toString());
					ca_certificate_file->open(QIODevice::ReadOnly))
				{
					bot_settings->ssl_configuration->addCaCertificate(QSslCertificate(ca_certificate_file->readAll()));
				}
			}
		}

		if (bot_settings_json["public_key_path"].isNull() == false)
		{
			if (auto public_key = std::make_shared<QFile>(bot_settings_json["public_key_path"].toString());
				public_key->open(QIODevice::ReadOnly))
			{
				bot_settings->public_key = public_key;

				if (bot_settings_json["certificate_path"].isNull())
					bot_settings->ssl_configuration->setLocalCertificate(QSslCertificate(public_key->readAll()));
			}
		}

		if (bot_settings_json["private_key_path"].isNull() == false)
		{
			if (auto private_key_file = std::make_shared<QFile>(bot_settings_json["private_key_path"].toString());
				private_key_file->open(QIODevice::ReadOnly))
			{
				bot_settings->ssl_configuration->setPrivateKey(QSslKey(private_key_file->readAll(), QSsl::KeyAlgorithm::Rsa));
			}
		}
	}
	else bot_settings->ssl_configuration = std::nullopt;

	return bot_settings;
}