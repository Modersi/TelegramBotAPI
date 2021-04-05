#ifndef ANIMATION_H
#define ANIMATION_H

#include "Type.h"
#include "PhotoSize.h"

/*!
    \brief This class represents an Animation file

    Animation can be only GIF or H.264/MPEG-4 AVC video without sound

    Fields of Animation object
    -----------------------------------

    | Field             | Type          | Desription  |
    | :---:             | :----:        | :---- |
    | **fileId**        | `QString`     | Identifier for this file, which can be used to download or reuse the file |
    | **fileUniqueId**  | `QString`     | Unique identifier for this file, which is supposed to be the same over time and for different bots. Can't be used to download or reuse the file |
    | **width**         | `QInt32`      | Animation width as defined by sender |
    | **height**        | `QInt32`      | Animation height as defined by sender |
    | **duration**      | `QInt32`      | Duration of the animation in seconds as defined by sender |
    | **thumb**         | `PhotoSize`   | **Optional**. Animation thumbnail as defined by sender |
    | **fileName**      | `QString`     | **Optional**. Original animation filename as defined by sender |
    | **mimeType**      | `QString`     | **Optional**. [MIME](https://en.wikipedia.org/wiki/Media_type) type of the file as defined by sender |
    | **fileSize**      | `QInt32`      | **Optional**. File size |

    In order to set **optional** fields use "set" methods ([setThumb](@ref setThumb), [setMimeType](@ref setMimeType), etc.)
*/


class Animation : public Type
{
public:
    Animation();

    Animation(QString   fileId,
              QString   fileUniqueId,
              qint32    width,
              qint32    height,
              qint32    duration);

    Animation(QJsonObject jsonObject);

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

    QString fileName();
    void    setFileName(QString fileName);
    bool    hasFileName();

    QString mimeType();
    void    setMimeType(QString mimeType);
    bool    hasMimeType();

    qint32  fileSize();
    void    setFileSize(qint32 fileSize);
    bool    hasFileSize();
};

#endif // ANIMATION_H
