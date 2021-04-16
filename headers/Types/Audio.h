#ifndef AUDIO_H
#define AUDIO_H

#include "Types/Type.h"
#include "Types/PhotoSize.h"

/*!
    \brief This class represents an Audio file to be treated as music by the Telegram clients

    Fields of Audio object
    -----------------------------------

    | Field             | Type          | Desription  |
    | :---:             | :----:        | :---- |
    | **fileId**        | `QString`     | Identifier for this file, which can be used to download or reuse the file |
    | **fileUniqueId**  | `QString`     | Unique identifier for this file, which is supposed to be the same over time and for different bots. Can't be used to download or reuse the file |
    | **duration**      | `QInt32`      | Duration of the audio in seconds as defined by sender |
    | **performer**     | `QString`     | **Optional**. Performer of the audio as defined by sender or by audio tags |
    | **title**         | `QString`     | **Optional**. Title of the audio as defined by sender or by audio tags |
    | **mimeType**      | `QString`     | **Optional**. [MIME](https://en.wikipedia.org/wiki/Media_type) type of the file as defined by sender |
    | **fileSize**      | `QInt32`      | **Optional**. File size |
    | **thumb**         | `PhotoSize`   | **Optional**. Thumbnail of the album cover to which the music file belongs |

    In order to set **optional** fields use "set" methods ([setThumb](@ref setThumb), [setMimeType](@ref setMimeType), etc.)
*/

class Audio : public Type
{
public:
    Audio();

    Audio(QString   fileId,
          QString   fileUniqueId,
          qint32    duration);

    Audio(QJsonObject jsonObject);

    QString fileId();
    void    setFileId(QString fileId);

    QString fileUniqueId();
    void    setFileUniqueId(QString fileUniqueId);

    qint32  duration();
    void    setDuration(qint32 duration);

    QString performer();
    void    setPerformer(QString performer);
    bool    hasPerformer();

    QString title();
    void    setTitle(QString title);
    bool    hasTitle();

    QString mimeType();
    void    setMimeType(QString mimeType);
    bool    hasMimeType();

    qint32  fileSize();
    void    setFileSize(qint32 fileSize);
    bool    hasFileSize();

    PhotoSize  thumb();
    void       setThumb(PhotoSize thumb);
    bool       hasThumb();
};

#endif // AUDIO_H
