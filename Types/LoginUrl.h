#ifndef LOGINURL_H
#define LOGINURL_H

#include "Type.h"

class TELEGRAMAPI_EXPORT LoginUrl : public Type
{
public:
    LoginUrl();

    LoginUrl(QString url,
             QString forwardText = "",
             QString botUsername = "",
             bool    requestWriteAccess = false);

    LoginUrl(QJsonObject jsonObject);

    QString url();
    void    setUrl(QString url);

    QString forwardText();
    void    setForwardText(QString forwardText);
    bool    hasForwardText();

    QString botUsername();
    void    setBotUsername(QString botUsername);
    bool    hasBotUsername();

    bool    requestWriteAccess();
    void    setRequestWriteAccess(bool requestWriteAccess);
    bool    hasRequestWriteAccess();
};

#endif // LOGINURL_H
