#ifndef INPUTMEDIAANIMATION_H
#define INPUTMEDIAANIMATION_H

#include "Types/Type.h"

class InputMediaAnimation : public Type
{
public:
    InputMediaAnimation();

    InputMediaAnimation(QString media);

    InputMediaAnimation(QJsonObject jsonObject);

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
};

#endif // INPUTMEDIAANIMATION_H
