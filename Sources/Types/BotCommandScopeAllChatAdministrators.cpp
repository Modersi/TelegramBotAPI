#include "Types/BotCommandScopeAllChatAdministrators.h"

#include "qjsonobject.h"

QJsonObject Telegram::BotCommandScopeAllChatAdministrators::toObject() const
{
	return QJsonObject{ {"type", type} };
}
