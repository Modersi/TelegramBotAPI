#include "Types/BotCommandScopeChatAdministrators.h"

#include "qjsonobject.h"

Telegram::BotCommandScopeChatAdministrators::BotCommandScopeChatAdministrators(const std::variant<qint32, QString>& chat_id) :
	chat_id(chat_id)
{}

Telegram::BotCommandScopeChatAdministrators::BotCommandScopeChatAdministrators(const QJsonObject& jsonObject)
{
	jsonObject.contains("chat_id") ? (jsonObject["chat_id"].isString() ? chat_id = jsonObject["chat_id"].toString() : chat_id = jsonObject["chat_id"].toInt()) : chat_id = "";
}

bool Telegram::BotCommandScopeChatAdministrators::isEmpty() const
{
	/* Check if std::variant<qint32, QString> chat_id contains any value */
	bool holdsChatId(false);
	if (std::holds_alternative<qint32>(chat_id))
		if (std::get<qint32>(chat_id) != 0) holdsChatId = true;

	if (std::holds_alternative<QString>(chat_id))
		if (std::get<QString>(chat_id) != "") holdsChatId = true;

	return holdsChatId;
}

QJsonObject Telegram::BotCommandScopeChatAdministrators::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	QJsonObject botCommandScopeChatAdministratorsJsonObject{ {"type", type} };
	
	if (std::holds_alternative<qint32>(chat_id))  botCommandScopeChatAdministratorsJsonObject.insert("chat_id", std::get<qint32>(chat_id));
	if (std::holds_alternative<QString>(chat_id)) botCommandScopeChatAdministratorsJsonObject.insert("chat_id", std::get<QString>(chat_id));

	return botCommandScopeChatAdministratorsJsonObject;
}
