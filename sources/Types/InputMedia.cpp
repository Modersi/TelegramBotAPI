#include "Types/InputMedia.h"

Telegram::InputMedia::InputMedia()
{
}

QJsonObject Telegram::InputMedia::toObject() const
{
    return QJsonObject();
}

bool Telegram::InputMedia::isEmpty() const
{
    return false;
}
