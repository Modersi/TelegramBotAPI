#include "BotSettings.h"

#include "qsslkey.h"
#include "qsslcertificate.h"
#include "qfile.h"
#include "qjsondocument.h"
#include "qjsonobject.h"
#include "qjsonarray.h"

#include "Internal/ConversionFunctions.h"

Telegram::BotSettings::BotSettings(const QDir& bot_settings_file_path, const QString& bot_settings_file_name)
{
	/* Check if the bot settings file exists, if no - create new one */
	if (!QFile::exists(bot_settings_file_path.filePath(bot_settings_file_name)))  {
#ifdef DEBUG_MODE
		qDebug() << "Bot settings file(file path:" << bot_settings_file_path.path() << ", file name:" << bot_settings_file_name << ") is not found. Creating a new one!";
#endif

		CreateDefaultBotSettinngsFile(bot_settings_file_path, bot_settings_file_name);
	}

	/* Open file and read all settings */
	QFile bot_settings_file(bot_settings_file_path.filePath(bot_settings_file_name));
	if (bot_settings_file.open(QIODevice::ReadOnly))
	{
		QJsonObject bot_settings_json = QJsonDocument::fromJson(bot_settings_file.readAll()).object();

		/* Setting the bot token */
		bot_token = bot_settings_json["bot_token"].toString();

		/* Reading all optional fields */
		bot_settings_json["webhook_url"].isNull()					? webhook_url = std::nullopt			: webhook_url = bot_settings_json["webhook_url"].toString();	
		bot_settings_json["webhook_ip_addres"].isNull()				? webhook_ip_addres = std::nullopt		: webhook_ip_addres = bot_settings_json["webhook_ip_addres"].toString();
		bot_settings_json["max_connections"].isNull()				? max_connections = std::nullopt		: max_connections = bot_settings_json["max_connections"].toInt();
		bot_settings_json["allowed_updates"].toArray().isEmpty()	? allowed_updates = std::nullopt		: allowed_updates = QJsonArrayToQVector<QString>(bot_settings_json["allowed_updates"].toArray());
		bot_settings_json["drop_pending_updates"].isNull()			? drop_pending_updates = std::nullopt	: drop_pending_updates = bot_settings_json["drop_pending_updates"].toBool();
		bot_settings_json["host_addres"].isNull()					? host_addres = std::nullopt			: host_addres = bot_settings_json["host_addres"].toString();
		bot_settings_json["port"].isNull()							? port = std::nullopt					: port = bot_settings_json["port"].toInt();
		bot_settings_json["payment_token"].isNull()					? payment_token = std::nullopt			: payment_token = bot_settings_json["payment_token"].toString();
		
		/* Opening a SSL public key if specified */
		if (!bot_settings_json["public_key_path"].isNull()) {
			public_key = std::make_shared<QFile>(bot_settings_json["public_key_path"].toString());
			(*public_key)->open(QIODevice::ReadOnly);
		}
		else public_key = std::nullopt;

		/* Configuring SSL if specified */
		if (bot_settings_json["certificate_path"].isNull() and bot_settings_json["private_key_path"].isNull() and bot_settings_json["ca_certificates_paths"].toArray().isEmpty())
			ssl_configuration = std::nullopt;
		else 
		{
			ssl_configuration = QSslConfiguration();
			if (!bot_settings_json["certificate_path"].isNull()) {
				QFile certificate_file(bot_settings_json["certificate_path"].toString());
				certificate_file.open(QIODevice::ReadOnly);
				ssl_configuration->setLocalCertificate(QSslCertificate(&certificate_file));
			}

			if (!bot_settings_json["private_key_path"].isNull()) {
				QFile private_key_file(bot_settings_json["private_key_path"].toString());
				private_key_file.open(QIODevice::ReadOnly);
				ssl_configuration->setPrivateKey(QSslKey(&private_key_file, QSsl::KeyAlgorithm::Rsa));
			}

			if (!bot_settings_json["ca_certificates_paths"].toArray().isEmpty()) {
				for (auto&& ca_certificate_file_path : bot_settings_json["ca_certificates_paths"].toArray())
				{
					QFile ca_certificate_file(ca_certificate_file_path.toString());
					ca_certificate_file.open(QIODevice::ReadOnly);
					ssl_configuration->addCaCertificate(QSslCertificate(&ca_certificate_file));
				}
			}
		}
	}
#ifdef DEBUG_MODE 
	else qDebug() << "Bot settings file can not be opened!";
#endif
}

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

void Telegram::BotSettings::CreateDefaultBotSettinngsFile(const QDir& file_path, const QString& file_name)
{
	/* Check is bot_settings_file_path directory is existing, if no - create such directory */
	if (!file_path.exists())
		file_path.mkpath(file_path.absolutePath());

	/* Open(and create if not exists) bot settings file and write default settings */
	QFile botSettinsFile(file_path.filePath(file_name));
	if (botSettinsFile.open(QIODevice::WriteOnly))
		botSettinsFile.write(QJsonDocument({{"bot_token", ""},
											{"webhook_url", QJsonValue::Type::Null},
											{"certificate_path", QJsonValue::Type::Null},
											{"ca_certificates_paths", QJsonArray()},
											{"private_key_path", QJsonValue::Type::Null},
											{"public_key_path", QJsonValue::Type::Null},
											{"webhook_ip_addres", QJsonValue::Type::Null},
											{"max_connections", QJsonValue::Type::Null},
											{"allowed_updates", QJsonArray()},
											{"drop_pending_updates", QJsonValue::Type::Null},
											{"host_addres", QJsonValue::Type::Null},
											{"port", QJsonValue::Type::Null},
											{"payment_token", QJsonValue::Type::Null} }).toJson());
												
}