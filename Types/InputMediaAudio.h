#ifndef INPUTMEDIAAUDIO_H
#define INPUTMEDIAAUDIO_H

#include "Type.h"

class TELEGRAMAPI_EXPORT InputMediaAudio : public Type
{
public:
    InputMediaAudio();

    InputMediaAudio(QString media);

    InputMediaAudio(QJsonObject jsonObject);

    QString media();
    void    setMedia(QString media);

    //InputFile thumb();
    QString   thumb();
    //void      setThumb(InputFile thumb);
    void      setThumb(QString thumb);
    bool      hasThumb();

    QString caption(); // добавить проверки на хуйню
    void    setCaption(QString caption);
    bool    hasCaption();

    QString parseMode();
    void    setParseMode(QString parseMode);
    bool    hasParseMode();

    qint32  duration();
    void    setDuration(qint32 duration);
    bool    hasDuration();

    QString performer();
    void    setPerformer(QString performer);
    bool    hasPerformer();

    QString title();
    void    setTitle(QString title);
    bool    hasTitle();
};

#endif // INPUTMEDIAAUDIO_H
