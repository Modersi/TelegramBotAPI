#include <iostream>

#include "qjsonobject.h"

#include "TestBot.h"

TestBot::TestBot(const QVector<Telegram::BotCommand>& bot_commands, const Telegram::BotSettings& bot_settings) :
	telegram_bot(bot_settings),
	bot_commands(bot_commands),
	QObject()
{
	/* When any error occured - print error description to console */
	connect(&telegram_bot, &Telegram::Bot::errorOccured,
			this, &TestBot::onErrorOccured);

	/* Setting bot commands */
	telegram_bot.setMyCommands(bot_commands);

	/* When any message received - parce it for command */
	QObject::connect(&telegram_bot, &Telegram::Bot::messageReceived, [&](qint32 update_id, Telegram::Message message) {

		if (message.text.has_value() and (message.text.value().startsWith("/") and message.text.value().size() != 1))
			emit commandReceived(message.from.value_or(Telegram::User()), message.text.value());

	});

	/* Printing debug info about the webhook */
	Telegram::WebhookInfo webhook_info = telegram_bot.getWebhookInfo();

	qDebug() << endl << "---| Webhook information:"
		<< endl << "Webhook URL:" << webhook_info.url
		<< endl << "IP addres:" << webhook_info.ip_address.value_or("")
		<< endl << "Has custom certificate:" << webhook_info.has_custom_certificate
		<< endl << "Pending update count:" << webhook_info.pending_update_count
		<< endl << "Allowed updates:" << webhook_info.allowed_updates.value_or(QVector<QString>())
		<< endl << "Max connections:" << webhook_info.max_connections.value_or(0)
		<< endl << "Last error date" << webhook_info.last_error_date.value_or(0)
		<< endl << "Last erorr message:" << webhook_info.last_error_message.value_or("");
}

void TestBot::onErrorOccured(Telegram::Error error)
{
	qDebug() << endl << "--| Error occured:"
		<< endl << "Error code: " << error.error_code
		<< endl << "Description: " << error.description << endl;
}
