#ifndef KEYBOARDBUTTON_H
#define KEYBOARDBUTTON_H

#include "Type.h"

class TELEGRAMAPI_EXPORT KeyboardButton : public Type
{
public:
    KeyboardButton();

    KeyboardButton(QString text);

    KeyboardButton(QJsonObject jsonObject);

    QString text();
    void    setText(QString text);

    bool    requestContact();
    void    setRequestContact(bool requestContact);
    bool    hasRequestContact();

    bool    requestLocation();
    void    setRequestLocation(bool requestLocation);
    bool    hasRequestLocation();

    //KeyboardButtonPollType  requestPoll();
    //void                    setRequestPoll(KeyboardButtonPollType requestPoll);
    //bool                    hasRequestPoll();
};

#endif // KEYBOARDBUTTON_H
