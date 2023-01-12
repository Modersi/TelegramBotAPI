#include "qcoreapplication.h"

#include "TestBot.h"

//	In this example, we will create a bot that sends you examples of inline and reply buttons in answer to commands

int main(int argc, char* argv[]) {
	QCoreApplication coreApplication(argc, argv);

	TestBot test_bot;

	return coreApplication.exec();
}