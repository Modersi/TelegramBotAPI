#include "Types/BotCommandScopeChatAdministrators.h"

Telegram::BotCommandScopeChatAdministrators::BotCommandScopeChatAdministrators(const std::variant<qint32, QString>& chat_id) :
	chat_id(chat_id)
{}

Telegram::BotCommandScopeChatAdministrators::BotCommandScopeChatAdministrators(const QJsonObject& json_object) {
	if (json_object.contains("chat_id"))
		json_object["chat_id"].isString() ? chat_id = json_object["chat_id"].toString() : chat_id = json_object["chat_id"].toInt();
	else chat_id = "";
}

bool Telegram::BotCommandScopeChatAdministrators::isEmpty() const {
	return (std::holds_alternative<qint32>(chat_id) and std::get<qint32>(chat_id) == 0)
		   or
		   (std::holds_alternative<QString>(chat_id) and std::get<QString>(chat_id).isEmpty());
}

QJsonObject Telegram::BotCommandScopeChatAdministrators::toObject() const {
	
	if (isEmpty()) return {};

	QJsonObject bot_command_scope_chat_administrators_json_object{ {"type", "chat_administrators"} };
	
	if (std::holds_alternative<qint32>(chat_id))  bot_command_scope_chat_administrators_json_object.insert("chat_id", std::get<qint32>(chat_id));
	if (std::holds_alternative<QString>(chat_id)) bot_command_scope_chat_administrators_json_object.insert("chat_id", std::get<QString>(chat_id));

	return bot_command_scope_chat_administrators_json_object;
}

Telegram::BotCommandScope::Type Telegram::BotCommandScopeChatAdministrators::getType() const {
	return type;
}