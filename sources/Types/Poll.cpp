#include "Types/Poll.h"

Poll::Poll()
{

}

Poll::Poll(QString                 id,
           QString                 question,
           QVector<PollOption>     options,
           qint32                  totalVoterCount,
           bool                    isClosed,
           bool                    isAnonymous,
           QString                 type,
           bool                    allowsMultipleAnswers,
           qint32                  correctOptionId,
           QString                 explanation,
           QVector<MessageEntity>  explanationEntities,
           qint32                  openPeriod,
           qint32                  closeDate)
{
    _jsonObject.insert("id", QJsonValue(id));
    _jsonObject.insert("question", QJsonValue(question));
    _jsonObject.insert("options", QJsonValue(Type::QVectorToQJsonArray(options)));
    _jsonObject.insert("total_voter_count", QJsonValue(totalVoterCount));
    _jsonObject.insert("is_closed", QJsonValue(isClosed));
    _jsonObject.insert("is_anonymous", QJsonValue(isAnonymous));
    _jsonObject.insert("type", QJsonValue(type));
    _jsonObject.insert("allows_multiple_answers", QJsonValue(allowsMultipleAnswers));

    if(correctOptionId != -1)
        _jsonObject.insert("correct_option_id", QJsonValue(correctOptionId));
    if(!explanation.isEmpty())
        _jsonObject.insert("explanation", QJsonValue(explanation));
    if(!explanationEntities.isEmpty())
        _jsonObject.insert("explanation_entities", QJsonValue(Type::QVectorToQJsonArray(explanationEntities)));
    if(openPeriod != 0)
        _jsonObject.insert("open_period", QJsonValue(openPeriod));
    if(closeDate != 0)
        _jsonObject.insert("close_date", QJsonValue(closeDate));
}

Poll::Poll(QJsonObject jsonObject)
{
    if(jsonObject.contains("id"))
        _jsonObject.insert("id", jsonObject.value("id"));

    if(jsonObject.contains("question"))
        _jsonObject.insert("question", jsonObject.value("question"));

    if(jsonObject.contains("options"))
        _jsonObject.insert("options", jsonObject.value("options"));

    if(jsonObject.contains("total_voter_count"))
        _jsonObject.insert("total_voter_count", jsonObject.value("total_voter_count"));

    if(jsonObject.contains("is_closed"))
        _jsonObject.insert("is_closed", jsonObject.value("is_closed"));

    if(jsonObject.contains("is_anonymous"))
        _jsonObject.insert("is_anonymous", jsonObject.value("is_anonymous"));

    if(jsonObject.contains("type"))
        _jsonObject.insert("type", jsonObject.value("type"));

    if(jsonObject.contains("allows_multiple_answers"))
        _jsonObject.insert("allows_multiple_answers", jsonObject.value("allows_multiple_answers"));

    if(jsonObject.contains("correct_option_id"))
        _jsonObject.insert("correct_option_id", jsonObject.value("correct_option_id"));

    if(jsonObject.contains("explanation"))
        _jsonObject.insert("explanation", jsonObject.value("explanation"));

    if(jsonObject.contains("explanation_entities"))
        _jsonObject.insert("explanation_entities", jsonObject.value("explanation_entities"));

    if(jsonObject.contains("open_period"))
        _jsonObject.insert("open_period", jsonObject.value("open_period"));

    if(jsonObject.contains("close_date"))
        _jsonObject.insert("close_date", jsonObject.value("close_date"));
}

// "get", "set" methods for "id" field //

QString Poll::id()
{
    return _jsonObject.value("id").toString();
}

void Poll::setId(QString id)
{
    _jsonObject.insert("id", id);
}

// "get", "set" methods for "question" field //

QString Poll::question()
{
    return _jsonObject.value("question").toString();
}

void Poll::setQuestion(QString question)
{
    _jsonObject.insert("question", question);
}

// "get", "set" methods for "options" field //

QVector<PollOption> Poll::options()
{
    return Type::QJsonArrayToQVector(_jsonObject.value("options").toArray(), PollOption());
}

void Poll::setOptions(QVector<PollOption> options)
{
    _jsonObject.insert("options", Type::QVectorToQJsonArray(options));
}

// "get", "set" methods for "total_voter_count" field //

qint32 Poll::totalVoterCount()
{
    return _jsonObject.value("total_voter_count").toInt();
}

void Poll::setTotalVoterCount(qint32 totalVoterCount)
{
    _jsonObject.insert("total_voter_count", totalVoterCount);
}

// "get", "set" methods for "is_closed" field //

bool Poll::isClosed()
{
    return _jsonObject.value("is_closed").toBool();
}

void Poll::setIsClosed(bool isClosed)
{
    _jsonObject.insert("is_closed", isClosed);
}

// "get", "set" methods for "is_anonymous" field //

bool Poll::isAnonymous()
{
    return _jsonObject.value("is_anonymous").toBool();
}

void Poll::setIsAnonymous(bool isAnonymous)
{
    _jsonObject.insert("is_anonymous", isAnonymous);
}

// "get", "set" methods for "type" field //

QString Poll::type()
{
    return _jsonObject.value("type").toString();
}

void Poll::setType(QString type)
{
    _jsonObject.insert("type", type);
}

// "get", "set" methods for "allows_multiple_answers" field //

bool Poll::allowsMultipleAnswers()
{
    return _jsonObject.value("allows_multiple_answers").toBool();
}

void Poll::setAllowsMultipleAnswers(bool allowsMultipleAnswers)
{
    _jsonObject.insert("allows_multiple_answers", allowsMultipleAnswers);
}

// "get", "set", "has" methods for "correct_option_id" field //

qint32 Poll::correctOptionId()
{
    return _jsonObject.value("correct_option_id").toInt();
}

void Poll::setCorrectOptionId(qint32 correctOptionId)
{
    _jsonObject.insert("correct_option_id", correctOptionId);
}

bool Poll::hasCorrectOptionId()
{
    return _jsonObject.contains("correct_option_id");
}

// "get", "set", "has" methods for "explanation" field //

QString Poll::explanation()
{
    return _jsonObject.value("explanation").toString();
}

void Poll::setExplanation(QString explanation)
{
    _jsonObject.insert("explanation", explanation);
}

bool Poll::hasExplanation()
{
    return _jsonObject.contains("explanation");
}

// "get", "set", "has" methods for "explanation_entities" field //

QVector<MessageEntity> Poll::explanationEntities()
{
    return Type::QJsonArrayToQVector(_jsonObject.value("explanation_entities").toArray(), MessageEntity());
}

void Poll::setExplanationEntities(QVector<MessageEntity> explanationEntities)
{
    _jsonObject.insert("explanation_entities", Type::QVectorToQJsonArray(explanationEntities));
}

bool Poll::hasExplanationEntities()
{
    return _jsonObject.contains("explanation_entities");
}

// "get", "set", "has" methods for "open_period" field //

qint32 Poll::openPeriod()
{
    return _jsonObject.value("open_period").toInt();
}

void Poll::setOpenPeriod(qint32 openPeriod)
{
    _jsonObject.insert("open_period", openPeriod);
}

bool Poll::hasOpenPeriod()
{
    return _jsonObject.contains("open_period");
}

// "get", "set", "has" methods for "close_date" field //

qint32 Poll::closeDate()
{
    return _jsonObject.value("close_date").toInt();
}

void Poll::setCloseDate(qint32 closeDate)
{
    _jsonObject.insert("close_date", closeDate);
}

bool Poll::hasCloseDate()
{
    return _jsonObject.contains("close_date");
}
