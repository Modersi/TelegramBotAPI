#ifndef RESPONSEPARAMETERS_H
#define RESPONSEPARAMETERS_H

#include "Type.h"

class TELEGRAMAPI_EXPORT ResponseParameters : public Type
{
public:
    ResponseParameters();

    ResponseParameters(QJsonObject jsonObject);

    qint64  migrateToChatId();
    void    setMigrateToChatId(qint64 migrateToChatId);

    qint32  retryAfter();
    void    setRetryAfter(qint32 retryAfter);
};

#endif // RESPONSEPARAMETERS_H
