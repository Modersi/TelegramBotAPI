#include "Types/BotCommand.h"

#include "qjsonobject.h"

Telegram::BotCommand::BotCommand() : 
    command(""),
    description("")
{}

Telegram::BotCommand::BotCommand(const QString& command,
                                 const QString& description) :
    command(command),
    description(description)
{}

Telegram::BotCommand::BotCommand(const QJsonObject& jsonObject) 
{
    jsonObject.contains("command")     ? command = jsonObject["command"].toString()         : command = "";
    jsonObject.contains("description") ? description = jsonObject["description"].toString() : description = "";
}

QJsonObject Telegram::BotCommand::toObject() const
{
	if (isEmpty())
		return QJsonObject();

    return QJsonObject{ {"command", command}, {"description", description} };
}

bool Telegram::BotCommand::isEmpty() const
{
    return command == "" and description == "";
}
