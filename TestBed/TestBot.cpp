#include "TestBot.h"

#include "qdebug.h"

using namespace Telegram;

TestBot::TestBot(const QVector<BotCommand>& bot_commands, const std::shared_ptr<BotSettings>& bot_settings) : 
	QObject(),
	telegram_bot(bot_settings),
	bot_commands(bot_commands)
{
	//	Telegram::Bot::errorOccured is emitted every time when the negative response is received from the Telegram server and holds an Error object in arguments. Error class contains the occurred error description and code. See Error.h for details
	connect(&telegram_bot, &Bot::errorOccured, this, &TestBot::onErrorOccured);

	//	Telegram::Bot::networkErrorOccured is emitted every time when there is an error while receiving Updates from the Telegram. Error class contains the occurred error description and code. See Error.h for details
	connect(&telegram_bot, &Bot::networkErrorOccured, this, &TestBot::onNetworkErrorOccured);

	/* Setting bot commands to make them visible for the user in Telegram client */
	telegram_bot.setMyCommands(bot_commands);

	/* When any message is received - parse it for a command */
	QObject::connect(&telegram_bot, &Bot::messageReceived, [&](qint32 update_id, Message message) {

		if (message.text.has_value() and message.text->startsWith("/") and message.text->size() > 1)
			emit commandReceived(message.chat, *message.text);
	});

	/* Printing debug info about the webhook */
	auto webhook_info = telegram_bot.getWebhookInfo();

	qDebug() << "\n" << "---| Webhook information:"
			 << "\n" << "Webhook URL:" << webhook_info.url
			 << "\n" << "IP addres:" << webhook_info.ip_address.value_or("")
			 << "\n" << "Has custom certificate:" << webhook_info.has_custom_certificate
			 << "\n" << "Pending update count:" << webhook_info.pending_update_count
			 << "\n" << "Allowed updates:" << webhook_info.allowed_updates.value_or(QVector<QString>())
			 << "\n" << "Max connections:" << webhook_info.max_connections.value_or(0)
			 << "\n" << "Last error date" << webhook_info.last_error_date.value_or(0)
			 << "\n" << "Last erorr message:" << webhook_info.last_error_message.value_or("");
}

void TestBot::onErrorOccured(Error error) {
	qDebug() << "\n" << "--| Error occured:"
			 << "\n" << "Error code: " << error.error_code
			 << "\n" << "Description: " << error.description;
}

void TestBot::onNetworkErrorOccured(Error error) {
	qDebug() << "\n" << "--| Network error occured:"
			 << "\n" << "Error code: " << error.error_code
			 << "\n" << "Description: " << error.description;
}
