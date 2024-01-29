#include "Types/BotCommandScopeChatMember.h"

Telegram::BotCommandScopeChatMember::BotCommandScopeChatMember(const std::variant<qint32, QString>& chat_id, const qint32& user_id) :
	chat_id(chat_id),
	user_id(user_id)
{}

Telegram::BotCommandScopeChatMember::BotCommandScopeChatMember(const QJsonObject& json_object) {
	json_object.contains("chat_id") ? (json_object["chat_id"].isString() ? chat_id = json_object["chat_id"].toString() : chat_id = json_object["chat_id"].toInt()) : chat_id = "";
	json_object.contains("user_id") ? user_id = json_object["user_id"].toInt() : user_id = 0;
}

bool Telegram::BotCommandScopeChatMember::isEmpty() const {
	return (std::holds_alternative<qint32>(chat_id) and std::get<qint32>(chat_id) == 0)
		   or
		   (std::holds_alternative<QString>(chat_id) and std::get<QString>(chat_id).isEmpty());
}

QJsonObject Telegram::BotCommandScopeChatMember::toObject() const {
	
	if (isEmpty()) return {};

	QJsonObject bot_command_scope_chat_member_json_object{ {"type", "chat_member"}, {"user_id", user_id}};

	if (std::holds_alternative<qint32>(chat_id))  bot_command_scope_chat_member_json_object.insert("chat_id", std::get<qint32>(chat_id));
	if (std::holds_alternative<QString>(chat_id)) bot_command_scope_chat_member_json_object.insert("chat_id", std::get<QString>(chat_id));

	return bot_command_scope_chat_member_json_object;
}

Telegram::BotCommandScope::Type Telegram::BotCommandScopeChatMember::getType() const {
	return type;
}