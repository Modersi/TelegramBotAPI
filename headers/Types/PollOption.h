#ifndef POLLOPTION_H
#define POLLOPTION_H

#include "Type.h"

class TELEGRAMAPI_EXPORT PollOption : public Type
{
public:
    PollOption();

    PollOption(QString text,
               qint32  voterCount);

    PollOption(QJsonObject jsonObject);

    QString text();
    void    setText(QString text);

    qint32  voterCount();
    void    setVoterCount(qint32 voterCount);
};

#endif // POLLOPTION_H
