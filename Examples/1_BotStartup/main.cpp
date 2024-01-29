#include "qcoreapplication.h"
#include "qsslkey.h"

#include "TelegramBotAPI.h"

using namespace Telegram;

QSslConfiguration configureSimpleSSL(const QString& certificate_file_path, const QString& private_key_file_path, const QVector<QString>& ca_certificates_files_paths);

int main(int argc, char* argv[]) {

	QCoreApplication core_application(argc, argv);

	//	Bot has to be initialized using the object of class BotSettings. BotSettings holds all the required data to launch your bot. Look BotSettings.h for details 
	//	
	//	BotSettings can be constructed in 2 ways:
	//	1. Using a file with bot settings. By default, BotSettings.json file is located in the project root directory but you can specify another directory and file name in BotSettings constructor
	// 
	// 		This file should contain JSON object with key-value pairs listed below:
	//			● bot_token					- Your bot token
	//			● webhook_url				- Optional. Your HTTPS URL for the Telegram to send updates to. Required if you use webhooks, specify null if you want to get updates via getUpdates()
	//			
	//			SSL:
	//				● certificate_path			- Optional. Path to your SSL certificate file. Required if you use webhooks, specify null if you want to get updates via getUpdates()
	//				● private_key_path			- Optional. Path to your SSL private key file. Required if you use webhooks, specify null if you want to get updates via getUpdates()
	//				● ca_certificates_paths		- Optional. JSON array of paths to your SSL CA certificates files. Required if you use webhooks, specify null if you want to get updates via getUpdates() 
	//				● public_key_path			- Optional. Required only if you use a self-signed certificate, set to null otherwise. Path to your SSL public key. In essence, public key is your self-signed certificate
	//			
	//			● webhook_ip_addres			- Optional. The fixed IP address which will be used to send webhook requests instead of the IP address resolved through DNS
	//			● max_connections			- Optional. Maximum allowed number of simultaneous HTTPS connections to the webhook for update delivery, 1-100. Defaults to 40
	//			● allowed_updates			- Optional. JSON array with the update types you want your bot to receive. For example, specify ["message", "edited_channel_post", "callback_query"] to only receive updates of these types
	//			● drop_pending_updates		- Optional. Set "true" to drop all pending updates
	//			● host_addres				- Optional. Local IP address for webhook server to be listening for incoming connections. Defaults to "127.0.0.1"
	// 			● port						- Optional. Local port for webhook server to be listening for incoming connections. Defaults to 443
	//			● payment_token				- Optional. Your payment token
	// 
	//	2. By setting its fields. Look BotSettings.h for all fields and their meanings


	// #1  
	// Will initialize bot with settings from the file "BotSettings.json" located in the project root directory
	auto settings_from_file = BotSettings::makeFromFile();
	// Will initialize the bot with settings from file "SpecificFileName.json" in "Specific/Directory"
	auto settings_from_custom_file = BotSettings::makeFromFile(QDir("Specific/File/Directory"), QStringLiteral("SpecificFileName.json"));

	// #2
	// Initializes bot settings "from code". Use this way if you need to set particular settings for your SSL configuration
	auto settings_from_code = std::make_shared<BotSettings>("BOT_TOKEN", "WEBHOOK_URL");
	settings_from_code->ssl_configuration = configureSimpleSSL("Your SSL certificate file path", "Private key file path", { "CA certificate file paths" });


	// Then, using any of these BotSettings, initialize your bot
	Bot test_bot(settings_from_file);
	//Bot test_bot(settings_from_custom_file);
	//Bot test_bot(settings_from_code);

	// After setting up your bot you can ensure the bot is working properly using:
	qDebug() << test_bot.getMe().get().toObject();			// To get basic data about your bot in form of a User object
	qDebug() << test_bot.getWebhookInfo().get().toObject();	// To get data about your Webhook connection if a form of WebhookInfo object

	return core_application.exec();
}

QSslConfiguration configureSimpleSSL(const QString& certificate_file_path, const QString& private_key_file_path, const QVector<QString>& ca_certificates_files_paths) {

	QSslConfiguration ssl_configuration;

	// Adding certificate to the SSL configuration
	if (auto certificate_file = std::make_shared<QFile>(certificate_file_path);
		certificate_file->open(QIODevice::ReadOnly))
	{
		ssl_configuration.setLocalCertificate(QSslCertificate(certificate_file->readAll()));
	}

	// Adding private key to the SSL configuration
	if (auto private_key_file = std::make_shared<QFile>(private_key_file_path);
		private_key_file->open(QIODevice::ReadOnly))
	{
		ssl_configuration.setPrivateKey(QSslKey(private_key_file->readAll(), QSsl::KeyAlgorithm::Rsa));
	}

	// Adding CA certificates to the SSL configuration
	std::ranges::for_each(ca_certificates_files_paths, [&ssl_configuration](const QString& ca_certificate_file_path) {
		if (auto ca_certificate_file = std::make_shared<QFile>(ca_certificate_file_path);
			ca_certificate_file->open(QIODevice::ReadOnly))
		{
			ssl_configuration.addCaCertificate(QSslCertificate(ca_certificate_file->readAll()));
		}
	});

	return ssl_configuration;
}