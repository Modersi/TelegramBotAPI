#ifndef FILE_H
#define FILE_H

#include "Types/Type.h"

/*!
    \brief This class represents a file ready to be downloaded

    Fields of Document object
    -----------------------------------

    | Field             | Type          | Desription  |
    | :---:             | :----:        | :---- |
    | **fileId**        | `QString`     | Identifier for this file, which can be used to download or reuse the file |
    | **fileUniqueId**  | `QString`     | Unique identifier for this file, which is supposed to be the same over time and for different bots. Can't be used to download or reuse the file |
    | **fileSize**      | `QInt32`      | **Optional**. File size, if known |
    | **filePath**      | `QString`     | **Optional**. File path. Use `"https://api.telegram.org/file/bot<token>/<file_path>"` to get the file |

    The file can be downloaded via the link `"https://api.telegram.org/file/bot<token>/<file_path>"`.
    It is guaranteed that the link will be valid for at least 1 hour. When the link expires, a new one can be requested by calling [getFile](@ref getFile)

    > Maximum file size to download is 20 MB

    In order to set **optional** fields use "set" methods ([setFileSize](@ref setFileSize), [setFilePath](@ref setFilePath), etc.)
*/

class File : public Type
{
public:
    File();

    File(QString fileId,
         QString fileUniqueId);

    File(QJsonObject jsonObject);

    QString fileId();
    void    setFileId(QString fileId);

    QString fileUniqueId();
    void    setFileUniqueId(QString fileUniqueId);

    qint32  fileSize();
    void    setFileSize(qint32 fileSize);
    bool    hasFileSize();

    QString filePath();
    void    setFilePath(QString filePath);
    bool    hasFilePath();
};

#endif // FILE_H
