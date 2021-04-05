#ifndef KEYBOARDBUTTONPOLLTYPE_H
#define KEYBOARDBUTTONPOLLTYPE_H

#include "Type.h"

class TELEGRAMAPI_EXPORT KeyboardButtonPollType : public Type
{
public:
    KeyboardButtonPollType(); // Раздуплить с этой хуетой

    KeyboardButtonPollType(QString type = "");

    KeyboardButtonPollType(QJsonObject jsonObject);

    QString type();
    void    setType(QString type);
};

#endif // KEYBOARDBUTTONPOLLTYPE_H
