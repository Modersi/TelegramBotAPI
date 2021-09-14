#include "Types/VoiceChatStarted.h"

Telegram::VoiceChatStarted::VoiceChatStarted()
{}

QJsonObject Telegram::VoiceChatStarted::toObject() const
{
    return QJsonObject();
}

bool Telegram::VoiceChatStarted::isEmpty() const
{
    return true;
}
