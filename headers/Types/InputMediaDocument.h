#ifndef INPUTMEDIADOCUMENT_H
#define INPUTMEDIADOCUMENT_H

#include "Types/Type.h"

class InputMediaDocument : public Type
{
public:
    InputMediaDocument();

    InputMediaDocument(QString media);

    InputMediaDocument(QJsonObject jsonObject);

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
};

#endif // INPUTMEDIADOCUMENT_H
