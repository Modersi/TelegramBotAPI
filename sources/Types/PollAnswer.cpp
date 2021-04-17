#include "Types/PollAnswer.h"

PollAnswer::PollAnswer() {}

PollAnswer::PollAnswer(QString      pollId,
                       User         user,
                       QVector<int> optionIds)
{
    _jsonObject.insert("poll_id", QJsonValue(pollId));
    _jsonObject.insert("user", QJsonValue(user.toObject()));

    QJsonArray tempArray;
    for(int i = 0; i < optionIds.size(); i++)
        tempArray.push_back(optionIds[i]);
    _jsonObject.insert("option_ids", QJsonValue(tempArray));
}

PollAnswer::PollAnswer(QJsonObject jsonObject)
{
    if(jsonObject.contains("poll_id"))
        _jsonObject.insert("poll_id", jsonObject.value("poll_id"));

    if(jsonObject.contains("user"))
        _jsonObject.insert("user", jsonObject.value("user"));

    if(jsonObject.contains("option_ids"))
        _jsonObject.insert("option_ids", jsonObject.value("option_ids"));
}

// "get", "set" methods for "poll_id" field //

QString PollAnswer::pollId()
{
    return _jsonObject.value("poll_id").toString();
}

void PollAnswer::setPollId(QString pollId)
{
    _jsonObject.insert("poll_id", pollId);
}

// "get", "set" methods for "user" field //

User PollAnswer::user()
{
    return User(_jsonObject.value("user").toObject());
}

void PollAnswer::setUser(User user)
{
    _jsonObject.insert("user", user.toObject());
}

// "get", "set" methods for "option_ids" field //

QVector<int> PollAnswer::optionIds()
{
    QVector<int> tempQVector;

    for(QJsonArray::const_iterator i = _jsonObject.value("option_ids").toArray().begin(); i < _jsonObject.value("option_ids").toArray().end(); i++)
        tempQVector.push_back(i->toInt());

    return tempQVector;
}

void PollAnswer::setOptionIds(QVector<int> optionIds)
{
    QJsonArray tempArray;

    for(int i = 0; i < optionIds.size(); i++)
        tempArray.insert(tempArray.end(), optionIds[i]);

    _jsonObject.insert("option_ids", tempArray);
}
