#ifndef PHOTOSIZE_H
#define PHOTOSIZE_H

#include "Type.h"

class TELEGRAMAPI_EXPORT PhotoSize : public Type
{
public:
    PhotoSize();

    PhotoSize(QString fileId,
              QString fileUniqueId,
              qint32  width,
              qint32  height,
              qint32  fileSize = 0);

    PhotoSize(QJsonObject jsonObject);

    QString fileId();
    void    setFileId(QString fileId);

    QString fileUniqueId();
    void    setFileUniqueId(QString fileUniqueId);

    qint32  width();
    void    setWidth(qint32 width);

    qint32  height();
    void    setHeight(qint32 height);

    qint32  fileSize();
    void    setFileSize(qint32 fileSize);
    bool    hasFileSize();
};

#endif // PHOTOSIZE_H
