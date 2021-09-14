#include "Types/BotCommandScopeDefault.h"

#include "qjsonobject.h"

QJsonObject Telegram::BotCommandScopeDefault::toObject() const
{
	return QJsonObject{ {"type", type} };
}
