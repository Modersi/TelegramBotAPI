#ifndef POLLANSWER_H
#define POLLANSWER_H

#include "Types/Type.h"
#include "Types/User.h"

class PollAnswer : public Type
{
public:
    PollAnswer();

    PollAnswer(QString      pollId,
               User         user,
               QVector<int> optionIds);

    PollAnswer(QJsonObject jsonObject);

    QString      pollId();
    void         setPollId(QString pollId);

    User         user();
    void         setUser(User user);

    QVector<int> optionIds();
    void         setOptionIds(QVector<int> optionIds);
};

#endif // POLLANSWER_H
