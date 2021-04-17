#ifndef INPUTMEDIAPHOTO_H
#define INPUTMEDIAPHOTO_H

#include "Types/Type.h"

class InputMediaPhoto : public Type
{
public:
    InputMediaPhoto();

    InputMediaPhoto(QString media);

    InputMediaPhoto(QJsonObject jsonObject);

    QString media();
    void    setMedia(QString media);

    QString caption(); // добавить проверки на хуйню
    void    setCaption(QString caption);
    bool    hasCaption();

    QString parseMode();
    void    setParseMode(QString parseMode);
    bool    hasParseMode();
};

#endif // INPUTMEDIAPHOTO_H
