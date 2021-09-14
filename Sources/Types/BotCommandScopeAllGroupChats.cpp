#include "Types/BotCommandScopeAllGroupChats.h"

#include "qjsonobject.h"

QJsonObject Telegram::BotCommandScopeAllGroupChats::toObject() const
{
	return QJsonObject{ {"type" , type} };
}
