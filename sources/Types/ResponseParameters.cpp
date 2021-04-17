#include "Types/ResponseParameters.h"

ResponseParameters::ResponseParameters() {}

ResponseParameters::ResponseParameters(QJsonObject jsonObject)
{
    if(jsonObject.contains("migrate_to_chat_id"))
        _jsonObject.insert("migrate_to_chat_id", jsonObject.value("migrate_to_chat_id"));

    if(jsonObject.contains("retry_after"))
        _jsonObject.insert("retry_after", jsonObject.value("retry_after"));
}

qint64 ResponseParameters::migrateToChatId()
{
    return _jsonObject.value("migrate_to_chat_id").toInt();
}

void ResponseParameters::setMigrateToChatId(qint64 migrateToChatId)
{
    _jsonObject.insert("migrate_to_chat_id", migrateToChatId);
}

qint32 ResponseParameters::retryAfter()
{
    return _jsonObject.value("retry_after").toInt();
}

void ResponseParameters::setRetryAfter(qint32 retryAfter)
{
    _jsonObject.insert("retry_after", retryAfter);
}
