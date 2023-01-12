#include "Types/BotCommand.h"

Telegram::BotCommand::BotCommand() : 
    command(),
    description() {}

Telegram::BotCommand::BotCommand(const QString& command,
                                 const QString& description) :
    command(command),
    description(description) {}

Telegram::BotCommand::BotCommand(const QJsonObject& json_object) {
    json_object.contains("command")     ? command = json_object["command"].toString()         : command = "";
    json_object.contains("description") ? description = json_object["description"].toString() : description = "";
}

QJsonObject Telegram::BotCommand::toObject() const {
    if (isEmpty()) return {};

    return { {"command", command}, {"description", description} };
}

bool Telegram::BotCommand::isEmpty() const {
    return command.isEmpty() and description.isEmpty();
}
