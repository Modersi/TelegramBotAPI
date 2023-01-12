#include "qcoreapplication.h"

#include "TestBot.h"

using namespace Telegram;

/* A simple example of a Telegram bot that sends a message when it receives a command */

int main(int argc, char* argv[]) {

	QCoreApplication core_application(argc, argv);

	QVector<BotCommand> bot_commands = {
		{"test_command", "Test description!"}
	};

	TestBot test_bot(bot_commands);

	QObject::connect(&test_bot, &TestBot::commandReceived, [&test_bot](const std::shared_ptr<Chat>& chat, const QString& command) {

		if (command == "/test_command") {
			test_bot.telegram_bot.sendMessage(chat->id, "Test command received!");
		}

	});

	return core_application.exec();
}

