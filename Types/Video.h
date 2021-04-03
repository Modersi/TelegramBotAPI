#ifndef VIDEO_H
#define VIDEO_H

#include "Type.h"
#include "PhotoSize.h"

class TELEGRAMAPI_EXPORT Video : public Type
{
public:
    Video();

    Video(QString   fileId,
          QString   fileUniqueId,
          qint32    width,
          qint32    height,
          qint32    duration,
          PhotoSize thumb = PhotoSize(),
          QString   mimeType = "",
          qint32    fileSize = 0);

    Video(QJsonObject jsonObject);

    QString fileId();
    void    setFileId(QString fileId);

    QString fileUniqueId();
    void    setFileUniqueId(QString fileUniqueId);

    qint32  width();
    void    setWidth(qint32 width);

    qint32  height();
    void    setHeight(qint32 height);

    qint32  duration();
    void    setDuration(qint32 duration);

    PhotoSize  thumb();
    void       setThumb(PhotoSize thumb);
    bool       hasThumb();

    QString mimeType();
    void    setMimeType(QString mimeType);
    bool    hasMimeType();

    qint32  fileSize();
    void    setFileSize(qint32 fileSize);
    bool    hasFileSize();
};

#endif // VIDEO_H
