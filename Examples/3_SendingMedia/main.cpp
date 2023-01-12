#include "qcoreapplication.h"

#include "TestBot.h"

//	In this example we will create the bot that can send you every type of media in answer to a command

int main(int argc, char* argv[]) {

	QCoreApplication coreApplication(argc, argv);

	TestBot test_bot;

	return coreApplication.exec();
}
