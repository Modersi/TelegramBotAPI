#include "PollOption.h"

PollOption::PollOption() {}

PollOption::PollOption(QString text, qint32 voterCount)
{
    _jsonObject.insert("text", QJsonValue(text));
    _jsonObject.insert("voter_count", QJsonValue(voterCount));
}

PollOption::PollOption(QJsonObject jsonObject)
{
    if(jsonObject.contains("text"))
        _jsonObject.insert("text", jsonObject.value("text"));

    if(jsonObject.contains("voter_count"))
        _jsonObject.insert("voter_count", jsonObject.value("voter_count"));
}

// "get", "set" methods for "text" field //

QString PollOption::text()
{
    return _jsonObject.value("text").toString();
}

void PollOption::setText(QString text)
{
    _jsonObject.insert("text", text);
}

// "get", "set" methods for "voter_count" field //

qint32 PollOption::voterCount()
{
    return _jsonObject.value("voter_count").toInt();
}

void PollOption::setVoterCount(qint32 voterCount)
{
    _jsonObject.insert("voter_count", voterCount);
}
