#include "qcoreapplication.h"
#include "qsslkey.h"

//	Including library main header */
#include "TelegramBotAPI.h"

QSslConfiguration configureSimpleSSL(const QString& certificate_file_path, const QString& private_key_file_path, const QVector<QString>& ca_certificates_files_paths);

int main(int argc, char* argv[])
{
	QCoreApplication core_application(argc, argv);

	//	Bot has to be initialized using the object of class BotSettings. BotSettings holds all required data to launch your bot. Look BotSettings.h for details 
	//	
	//	BotSettings can be constructed in 2 ways:
	//	1. Using a file with bot settings. By default, BotSettings.json file is located in the project root directory but you can specify another directory and file name in arguments
	// 
	// 		This file should contain JSON object with key-value pairs listed below:
	//			• bot_token					- Your bot token
	//			• webhook_url				- Optional. Your HTTPS url for the Telegram to send updates to. Required if you use webhooks, specify null is you want to get updates via getUpdates()
	//			
	//			SSL:
	//				• certificate_path			- Optional. Path to your SSL certificate file. Required if you use webhooks, specify null is you want to get updates via getUpdates()
	//				• private_key_path			- Optional. Path to your SSL private key file. Required if you use webhooks, specify null is you want to get updates via getUpdates()
	//				• ca_certificates_paths		- Optional. JSON array of paths to your SSL CA certificates files. Required if you use webhooks, specify empty array is you want to get updates via getUpdates() 
	//				• public_key_path			- Optional. Required only if you use a self-signed certificate, set to null otherwise. Path to your SSL public key. In essence public key it is your self-signed certificate
	//			
	//			• webhook_ip_addres			- Optional. The fixed IP address which will be used to send webhook requests instead of the IP address resolved through DNS
	//			• max_connections			- Optional. Maximum allowed number of simultaneous HTTPS connections to the webhook for update delivery, 1-100. Defaults to 40
	//			• allowed_updates			- Optional. JSON array with of the update types you want your bot to receive. For example, specify [“message”, “edited_channel_post”, “callback_query”] to only receive updates of these types
	//			• drop_pending_updates		- Optional. Set "true" to drop all pending updates
	//			• host_addres				- Optional. Local IP address for webhook server to be listening for incoming connections. Defaults to "127.0.0.1"
	// 			• port						- Optional. Local port for webhook server to be listening for incoming connections. Defaults to 443
	//			• payment_token				- Optional. Your payment token
	// 
	//	2. By setting its fields. Look BotSettings.h for all arguments and their meanings


	// #1  
	// Will initialize bot settings from file "BotSettings.json" located in the project root directory
	Telegram::BotSettings settings_from_file;
	// Will initialize bot with settings from file "SpecificFileName.json" from "Specific/Directory"
	Telegram::BotSettings settings_from_custom_file(QDir("Specific/File/Directory"), QStringLiteral("SpecificFileName.json"));


	// #2
	// Will initialize bot settings "from code". Use this way if you need to set particular settings to your SSL configuration
	Telegram::BotSettings settings_from_code;
	settings_from_code.bot_token = "BOT_TOKEN";
	settings_from_code.webhook_url = "WEBHOOK_URL";
	settings_from_code.ssl_configuration = configureSimpleSSL("Your SSL certificate file path", "Private key file path", { "CA certificate file paths" });

	// Then create your bot with any of these BotSettings
	Telegram::Bot test_bot(settings_from_file);
	//Telegram::Bot test_bot(settings_from_custom_file);
	//Telegram::Bot test_bot(settings_from_code);

	// After setting your bot up you can ensure the bot is working properly using:
	qDebug() << test_bot.getMe().toObject();			// To get basic data about your bot in form of a User object
	qDebug() << test_bot.getWebhookInfo().toObject();	// To get data about your Webhook connection if a form of WebhookInfo object

	return core_application.exec();
}

QSslConfiguration configureSimpleSSL(const QString& certificate_file_path, const QString& private_key_file_path, const QVector<QString>& ca_certificates_files_paths)
{
	QSslConfiguration ssl_configuration;

	// Adding certificate to SSL configuration
	QFile certificate_file(certificate_file_path);
	certificate_file.open(QIODevice::ReadOnly);
	ssl_configuration.setLocalCertificate(QSslCertificate(&certificate_file));

	// Adding private key to SSL configuration
	QFile private_key_file(private_key_file_path);
	private_key_file.open(QIODevice::ReadOnly);
	ssl_configuration.setPrivateKey(QSslKey(&private_key_file, QSsl::KeyAlgorithm::Rsa));

	// Adding CA certificates to SSL configuration
	auto AddCaCertificateToSslConfiguration = [&](const QString& ca_certificate_file_path)
	{
		QFile ca_certificate_file(ca_certificate_file_path);
		ca_certificate_file.open(QIODevice::ReadOnly);
		ssl_configuration.addCaCertificate(QSslCertificate(&ca_certificate_file));
	};
	std::ranges::for_each(ca_certificates_files_paths, AddCaCertificateToSslConfiguration);

	return ssl_configuration;
}
