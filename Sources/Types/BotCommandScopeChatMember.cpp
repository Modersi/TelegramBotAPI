#include "Types/BotCommandScopeChatMember.h"

#include "qjsonobject.h"

Telegram::BotCommandScopeChatMember::BotCommandScopeChatMember(const std::variant<qint32, QString>& chat_id, const qint32& user_id) :
	chat_id(chat_id),
	user_id(user_id)
{}

Telegram::BotCommandScopeChatMember::BotCommandScopeChatMember(const QJsonObject& jsonObject)
{
	jsonObject.contains("chat_id") ? (jsonObject["chat_id"].isString() ? chat_id = jsonObject["chat_id"].toString() : chat_id = jsonObject["chat_id"].toInt()) : chat_id = "";
    jsonObject.contains("user_id") ? user_id = jsonObject["user_id"].toInt() : user_id = 0;
}

bool Telegram::BotCommandScopeChatMember::isEmpty() const
{
	/* Check if std::variant<qint32, QString> chat_id contains any value */
	bool holdsChatId(false);
	if (std::holds_alternative<qint32>(chat_id))
		if (std::get<qint32>(chat_id) != 0) holdsChatId = true;

	if (std::holds_alternative<QString>(chat_id))
		if (std::get<QString>(chat_id) != "") holdsChatId = true;

	return holdsChatId and user_id == 0;
}

QJsonObject Telegram::BotCommandScopeChatMember::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	QJsonObject botCommandScopeChatMemberJsonObject{ {"type", type}, {"user_id", user_id} };

	if (std::holds_alternative<qint32>(chat_id))  botCommandScopeChatMemberJsonObject.insert("chat_id", std::get<qint32>(chat_id));
	if (std::holds_alternative<QString>(chat_id)) botCommandScopeChatMemberJsonObject.insert("chat_id", std::get<QString>(chat_id));

	return botCommandScopeChatMemberJsonObject;
}
