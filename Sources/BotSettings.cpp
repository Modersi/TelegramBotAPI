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
	/* Check if default bot settings file is exists, if no - create new one */
	if (!QFile::exists(bot_settings_file_path.filePath(bot_settings_file_name)))
		CreateDefaultBotSettinngsFile();

	/* Open file and read all settings */
	QFile botSettingsFile(bot_settings_file_path.filePath(bot_settings_file_name));
	if (botSettingsFile.open(QIODevice::ReadOnly))
	{
		QJsonObject botSettingsJson = QJsonDocument::fromJson(botSettingsFile.readAll()).object();

		host_addres = botSettingsJson["host_addres"].toString();
		port = botSettingsJson["port"].toInt();
		ConfigureSSL(botSettingsJson["ssl_certificate_path"].toString(), botSettingsJson["private_key_path"].toString(), QJsonArrayToQVector<QString>(botSettingsJson["ca_ssl_certificates_path"].toArray()));
		bot_token = botSettingsJson["bot_token"].toString();
		payment_token = botSettingsJson["payment_token"].toString();
	}
}

Telegram::BotSettings::BotSettings(const QHostAddress& host_addres,
								   const quint16& port,
								   const QSslConfiguration& ssl_configuration,
								   const QString& bot_token,
								   const QString& payment_token) :
	host_addres(host_addres),
	port(port),
	ssl_configuration(ssl_configuration),
	bot_token(bot_token),
	payment_token()
{}

void Telegram::BotSettings::CreateDefaultBotSettinngsFile(const QDir& file_path, const QString& file_name)
{
	/* Check is bot_settings_file_path directory is existing, if no - create such directory */
	if (!file_path.exists())
		file_path.mkpath(file_path.absolutePath());

	/* Open(and create if not exists) bot settings file and write default settings */
	QFile botSettinsFile(file_path.filePath(file_name));
	if (botSettinsFile.open(QIODevice::WriteOnly))
		botSettinsFile.write(QJsonDocument({{"host_addres", "127.0.0.1"},
											{"port", "443"},
											{"ssl_certificate_path", ""},
											{"private_key_path", ""},
											{"ca_ssl_certificates_path", QJsonArray{""}},
											{"bot_token", ""},
											{"payment_token", ""}}).toJson());
}

void Telegram::BotSettings::ConfigureSSL(const QString& certificate_file_path, const QString& private_key_file_path, const QVector<QString>& ca_certificates_files_paths)
{
	QFile certificate_file(certificate_file_path);
	certificate_file.open(QIODevice::ReadOnly);
	ssl_configuration.setLocalCertificate(QSslCertificate(&certificate_file));

	QFile private_key_file(private_key_file_path);
	private_key_file.open(QIODevice::ReadOnly);
	ssl_configuration.setPrivateKey(QSslKey(&private_key_file, QSsl::KeyAlgorithm::Rsa));

	auto AddCaCertificateToSslConfiguration = [&](const QString& ca_certificate_file_path)
												{
													QFile ca_certificate_file(ca_certificate_file_path);
													ca_certificate_file.open(QIODevice::ReadOnly);
													ssl_configuration.addCaCertificate(QSslCertificate(&ca_certificate_file));
												};
	std::ranges::for_each(ca_certificates_files_paths, AddCaCertificateToSslConfiguration);

#ifdef DEBUG_MODE
	qDebug() << endl << "-| SSL configuration information |-"
		<< endl << "SSL certificate file is open: " << certificate_file.isOpen()
		<< endl << "SSL certificate is null: " << ssl_configuration.localCertificate().isNull()
		<< endl << "SSL private key file is open: " << private_key_file.isOpen()
		<< endl << "SSL private key is null: " << ssl_configuration.privateKey().isNull();
	std::ranges::for_each(ssl_configuration.caCertificates(), [](const QSslCertificate& caCertificate) { qDebug() << "CA SSL certificate is null: " << caCertificate.isNull(); });
#endif
}