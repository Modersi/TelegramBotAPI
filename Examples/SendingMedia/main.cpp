#include "qcoreapplication.h"

#include "TestBot.h"

int main(int argc, char* argv[])
{
	QCoreApplication coreApplication(argc, argv);

	//	In this example we will create a bot that has different commands and reply with test messages on them
	//
	//	See example how you can handle commands and send messages in TestBot.h/TestBot.cpp

	TestBot test_bot;

	return coreApplication.exec();
}
