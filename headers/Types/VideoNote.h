#ifndef VIDEONOTE_H
#define VIDEONOTE_H

#include "Types/Type.h"
#include "Types/PhotoSize.h"

class VideoNote : public Type
{
public:
    VideoNote();

    VideoNote(QString   fileId,
              QString   fileUniqueId,
              qint32    length,
              qint32    duration,
              PhotoSize thumb = PhotoSize(),
              qint32    fileSize = 0);

    VideoNote(QJsonObject jsonObject);

    QString fileId();
    void    setFileId(QString fileId);

    QString fileUniqueId();
    void    setFileUniqueId(QString fileUniqueId);

    qint32  length();
    void    setLength(qint32 length);

    qint32  duration();
    void    setDuration(qint32 duration);

    PhotoSize  thumb();
    void       setThumb(PhotoSize thumb);
    bool       hasThumb();

    qint32  fileSize();
    void    setFileSize(qint32 fileSize);
    bool    hasFileSize();
};

#endif // VIDEONOTE_H
