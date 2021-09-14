#include "Types/BotCommandScopeAllPrivateChats.h"

QJsonObject Telegram::BotCommandScopeAllPrivateChats::toObject() const
{
	return QJsonObject{ {"type", type} };
}
