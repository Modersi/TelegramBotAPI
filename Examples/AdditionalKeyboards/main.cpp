#include "qcoreapplication.h"

#include "TestBot.h"

int main(int argc, char* argv[])
{
	QCoreApplication coreApplication(argc, argv);

	//	In this example, we will create a bot that sends you examples of inline and reply buttons in answer to commands

	TestBot test_bot;

	return coreApplication.exec();
}