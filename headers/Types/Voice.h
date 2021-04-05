#ifndef VOICE_H
#define VOICE_H

#include "Type.h"

class TELEGRAMAPI_EXPORT Voice : public Type
{
public:
    Voice();

    Voice(QString   fileId,
          QString   fileUniqueId,
          qint32    duration,
          QString   mimeType = "",
          qint32    fileSize = 0);

    Voice(QJsonObject jsonObject);

    QString fileId();
    void    setFileId(QString fileId);

    QString fileUniqueId();
    void    setFileUniqueId(QString fileUniqueId);

    qint32  duration();
    void    setDuration(qint32 duration);

    QString mimeType();
    void    setMimeType(QString mimeType);
    bool    hasMimeType();

    qint32  fileSize();
    void    setFileSize(qint32 fileSize);
    bool    hasFileSize();
};

#endif // VOICE_H
