#ifndef USER_H
#define USER_H

#include "Types/Type.h"

class User : public Type
{
public:
    User();

    User(qint32   id,
         bool     isBot,
         QString  firstName,
         QString  lastName = "",
         QString  username = "",
         QString  languageCode = "");

    User(QJsonObject jsonObject);

    qint32  id();
    void    setId(qint32 id);

    bool    isBot();
    void    setIsBot(bool isBot);

    QString firstName();
    void    setFirstName(QString firstName);

    QString lastName();
    void    setLastName(QString lastName);
    bool    hasLastName();

    QString username();
    void    setUsername(QString username);
    bool    hasUsername();

    QString languageCode();
    void    setLanguageCode(QString languageCode);
    bool    hasLanguageCode();

    bool    canJoinGroups();
    void    setCanJoinGroups(bool canJoinGroups);
    bool    hasCanJoinGroups();

    bool    canReadAllGroupMessages();
    void    setCanReadAllGroupMessages(bool canReadAllGroupMessages);
    bool    hasCanReadAllGroupMessages();

    bool    supportsInlineQueries();
    void    setSupportsInlineQueries(bool supportsInlineQueries);
    bool    hasSupportsInlineQueries();
};

#endif // USER_H
