#ifndef INPUTMEDIAVIDEO_H
#define INPUTMEDIAVIDEO_H

#include "Type.h"

class TELEGRAMAPI_EXPORT InputMediaVideo : public Type
{
public:
    InputMediaVideo();

    InputMediaVideo(QString media);

    InputMediaVideo(QJsonObject jsonObject);

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

    qint32  width();
    void    setWidth(qint32 width);
    bool    hasWidth();

    qint32  height();
    void    setHeight(qint32 height);
    bool    hasHeight();

    qint32  duration();
    void    setDuration(qint32 duration);
    bool    hasDuration();

    bool    supportsStreaming();
    void    setSupportsStreaming(bool supportsStreaming);
    bool    hasSupportsStreaming();
};

#endif // INPUTMEDIAVIDEO_H
