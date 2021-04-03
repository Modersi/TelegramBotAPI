#ifndef POLL_H
#define POLL_H

#include "Type.h"
#include "PollOption.h"
#include "MessageEntity.h"

class TELEGRAMAPI_EXPORT Poll : public Type
{
public:
    Poll();

    Poll(QString                id,
         QString                question,
         QVector<PollOption>    options,
         qint32                 totalVoterCount,
         bool                   isClosed,
         bool                   isAnonymous,
         QString                type,
         bool                   allowsMultipleAnswers,
         qint32                 correctOptionId = -1,
         QString                explanation = "",
         QVector<MessageEntity> explanationEntities = QVector<MessageEntity>(),
         qint32                 openPeriod = 0,
         qint32                 closeDate = 0); // Переделать в QTime

    Poll(QJsonObject jsonObject);

    QString id();
    void    setId(QString id);

    QString question();
    void    setQuestion(QString question);

    QVector<PollOption> options();
    void                setOptions(QVector<PollOption> options);

    qint32  totalVoterCount();
    void    setTotalVoterCount(qint32 totalVoterCount);

    bool    isClosed();
    void    setIsClosed(bool isClosed);

    bool    isAnonymous();
    void    setIsAnonymous(bool isAnonymous);

    QString type();
    void    setType(QString type);

    bool    allowsMultipleAnswers();
    void    setAllowsMultipleAnswers(bool allowsMultipleAnswers);

    qint32  correctOptionId();
    void    setCorrectOptionId(qint32 correctOptionId);
    bool    hasCorrectOptionId();

    QString explanation();
    void    setExplanation(QString explanation);
    bool    hasExplanation();

    QVector<MessageEntity> explanationEntities();
    void                   setExplanationEntities(QVector<MessageEntity> explanationEntities);
    bool                   hasExplanationEntities();

    qint32  openPeriod();
    void    setOpenPeriod(qint32 openPeriod);
    bool    hasOpenPeriod();

    qint32  closeDate();
    void    setCloseDate(qint32 closeDate);
    bool    hasCloseDate();
};

#endif // POLL_H
