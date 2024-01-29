#include "Types/BotCommandScopeChat.h"

Telegram::BotCommandScopeChat::BotCommandScopeChat(const std::variant<qint32, QString>& chat_id) :
	chat_id(chat_id)
{}

Telegram::BotCommandScopeChat::BotCommandScopeChat(const QJsonObject& json_object) {

	if (json_object.contains("chat_id"))
		json_object["chat_id"].isString() ? chat_id = json_object["chat_id"].toString() : chat_id = json_object["chat_id"].toInt();
	else chat_id = "";
}

bool Telegram::BotCommandScopeChat::isEmpty() const {
	return (std::holds_alternative<qint32>(chat_id) and std::get<qint32>(chat_id) == 0) 
		   or 
		   (std::holds_alternative<QString>(chat_id) and std::get<QString>(chat_id).isEmpty());
}

QJsonObject Telegram::BotCommandScopeChat::toObject() const {
	
	if (isEmpty()) return {};

	QJsonObject bot_command_scope_chat_json_object{ {"type", "chat"} };

	if (std::holds_alternative<qint32>(chat_id))  bot_command_scope_chat_json_object.insert("chat_id", std::get<qint32>(chat_id));
	if (std::holds_alternative<QString>(chat_id)) bot_command_scope_chat_json_object.insert("chat_id", std::get<QString>(chat_id));

	return bot_command_scope_chat_json_object;
}

Telegram::BotCommandScope::Type Telegram::BotCommandScopeChat::getType() const {
	return type;
}
