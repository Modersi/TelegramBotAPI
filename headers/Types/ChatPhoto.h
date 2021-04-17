#ifndef CHATPHOTO_H
#define CHATPHOTO_H

#include "Types/Type.h"

/*!
    \brief This class represents a Chat Photo

    Fields of ChatPhoto object
    -----------------------------------

    | Field                  | Type       | Desription  |
    | :---:                  | :----:     | :---- |
    | **smallFileId**        | `QString`  | File identifier of small (160x160) chat photo. This fileId can be used only for photo download and only for as long as the photo is not changed |
    | **smallFileUniqueId**  | `QString`  | Unique file identifier of small (160x160) chat photo, which is supposed to be the same over time and for different bots. Can't be used to download or reuse the file. |
    | **bigFileId**          | `QString`  | File identifier of big (640x640) chat photo. This fileId can be used only for photo download and only for as long as the photo is not changed |
    | **bigFileUniqueId**    | `QString`  | Unique file identifier of big (640x640) chat photo, which is supposed to be the same over time and for different bots. Can't be used to download or reuse the file |

*/

class ChatPhoto : public Type
{
public:
    ChatPhoto();

    ChatPhoto(QString smallFileId,
              QString smallFileUniqueId,
              QString bigFileId,
              QString bigFileUniqueId);

    ChatPhoto(QJsonObject);

    QString smallFileId();
    void    setSmallFileId(QString smallFileId);

    QString smallFileUniqueId();
    void    setSmallFileUniqueId(QString smallFileUniqueId);

    QString bigFileId();
    void    setBigFileId(QString bigFileId);

    QString bigFileUniqueId();
    void    setBigFileUniqueId(QString bigFileUniqueId);
};

#endif // CHATPHOTO_H
