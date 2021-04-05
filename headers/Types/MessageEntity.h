#ifndef MESSAGEENTITY_H
#define MESSAGEENTITY_H

#include "Type.h"
#include "User.h"

class TELEGRAMAPI_EXPORT MessageEntity : public Type
{
public:
    MessageEntity();

    MessageEntity(QString  type,
                  qint32   offset,
                  qint32   length,
                  QString  url = "",
                  User     user = User(),
                  QString  language = "");

    MessageEntity(QJsonObject jsonObject);

    QString type();
    void    setType(QString type);

    qint32  offset();
    void    setOffset(qint32 offset);

    qint32  length();
    void    setLength(qint32 length);

    QString url();
    void    setUrl(QString url);
    bool    hasUrl();

    User    user();
    void    setUser(User user);
    bool    hasUser();

    QString language();
    void    setLanguage(QString language);
    bool    hasLanguage();

};

#endif // MESSAGEENTITY_H
