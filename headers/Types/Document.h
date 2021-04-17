#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "Types/Type.h"
#include "Types/PhotoSize.h"

/*!
    \brief This class represents a general file (as opposed to [photos](@ref PhotoSize), [voice messages](@ref Voice) and [audio](@ref Audio) files)

    Fields of Document object
    -----------------------------------

    | Field             | Type          | Desription  |
    | :---:             | :----:        | :---- |
    | **fileId**        | `QString`     | Identifier for this file, which can be used to download or reuse the file |
    | **fileUniqueId**  | `QString`     | Unique identifier for this file, which is supposed to be the same over time and for different bots. Can't be used to download or reuse the file |
    | **thumb**         | `PhotoSize`   | **Optional**. Document thumbnail as defined by sender |
    | **fileName**      | `QString`     | **Optional**. Original filename as defined by sender |
    | **mimeType**      | `QString`     | **Optional**. [MIME](https://en.wikipedia.org/wiki/Media_type) type of the file as defined by sender |
    | **fileSize**      | `QInt32`      | **Optional**. File size |

    In order to set **optional** fields use "set" methods ([setThumb](@ref setThumb), [setFileName](@ref setFileName), etc.)
*/

class Document : public Type
{
public:
    Document();

    Document(QString   fileId,
             QString   fileUniqueId);

    Document(QJsonObject jsonObject);

    QString fileId();
    void    setFileId(QString fileId);

    QString fileUniqueId();
    void    setFileUniqueId(QString fileUniqueId);

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

#endif // DOCUMENT_H
