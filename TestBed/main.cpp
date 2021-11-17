#include "qcoreapplication.h"
#include "qsslkey.h"
#include "qjsonarray.h"

#include "TestBot.h"

using namespace Telegram;

int main(int argc, char* argv[])
{
	QCoreApplication coreApplication(argc, argv);

	QVector<BotCommand> bot_commands = {
		{"test_command", "Test description"}
	};

	TestBot test_bot(bot_commands);
#define telegram_bot test_bot.telegram_bot

	QObject::connect(&test_bot, &TestBot::commandReceived, [&](const User& from, const QString command) {

		if (command == "/test_command") {
			telegram_bot.sendMessage(from.id, "Test command received!");
		}

	});

	return coreApplication.exec();
}