#ifndef CHAT_H
#define CHAT_H

#include "Types/Type.h"
#include "Types/ChatPhoto.h"
#include "Types/ChatPermissions.h"

class Message;

/*!
    \brief This class represents a Chat

    Fields of Chat object
    -----------------------------------

    | Field                 | Type              | Desription  |
    | :---:                 | :----:            | :---- |
    | **id**                | `QInt64`          | Unique identifier for this chat |
    | **type**              | `QString`         | Type of chat, can be either “private”, “group”, “supergroup” or “channel” |
    | **title**             | `QString`         | **Optional**. Title, for supergroups, channels and group chats |
    | **firstName**         | `QString`         | **Optional**. First name of the other party in a private chat |
    | **lastName**          | `QString`         | **Optional**. Last name of the other party in a private chat |
    | **photo**             | `ChatPhoto`       | **Optional**. Chat photo. Returned only in [getChat](@ref getChat) |
    | **description**       | `QString`         | **Optional**. Description, for groups, supergroups and channel chats. Returned only in [getChat](@ref getChat) |
    | **inviteLink**        | `QString`         | **Optional**. Chat invite link, for groups, supergroups and channel chats. Each administrator in a chat generates their own invite links, so the bot must first generate the link using [exportChatInviteLink](@ref exportChatInviteLink). Returned only in [getChat](@ref getChat) |
    | **pinnedMessage**     | `Message`         | **Optional**. Pinned message, for groups, supergroups and channels. Returned only in [getChat](@ref getChat) |
    | **permissions**       | `ChatPermissions` | **Optional**. Default chat member permissions, for groups and supergroups. Returned only in [getChat](@ref getChat) |
    | **slowModeDelay**     | `QInt32`          | **Optional**. For supergroups, the minimum allowed delay between consecutive messages sent by each unpriviledged user. Returned only in [getChat](@ref getChat) |
    | **stickerSetName**    | `QString`         | **Optional**. For supergroups, name of group sticker set. Returned only in [getChat](@ref getChat) |
    | **canSetStickerSet**  | `Bool`            | **Optional**. True, if the bot can change the group sticker set. Returned only in [getChat](@ref getChat) |

    In order to set **optional** fields use "set" methods ([setTitle](@ref setTitle), [setUsername](@ref setUsername), etc.)
*/

class Chat : public Type
{
public:
    Chat();

    Chat(qint64   id,
         QString  type);

    Chat(QJsonObject jsonObject);

    qint64  id();
    void    setId(qint64 id);

    QString type();
    void    setType(QString type);

    QString title();
    void    setTitle(QString title);
    bool    hasTitle();

    QString username();
    void    setUsername(QString username);
    bool    hasUsername();

    QString firstName();
    void    setFirstName(QString firstName);
    bool    hasFirstName();

    QString lastName();
    void    setLastName(QString lastName);
    bool    hasLastName();

    ChatPhoto   photo();
    void        setPhoto(ChatPhoto photo);
    bool        hasPhoto();

    QString description();
    void    setDescription(QString description);
    bool    hasDescription();

    QString inviteLink();
    void    setInviteLink(QString inviteLink);
    bool    hasInviteLink();

    QSharedPointer<Message> pinnedMessage();
    void                    setPinnedMessage(Message pinnedMessage);
    bool                    hasPinnedMessage();

    ChatPermissions permissions();
    void            setPermissions(ChatPermissions permissions);
    bool            hasPermissions();

    qint32  slowModeDelay();
    void    setSlowModeDelay(qint32 slowModeDelay);
    bool    hasSlowModeDelay();

    QString stickerSetName();
    void    setStickerSetName(QString stickerSetName);
    bool    hasStickerSetName();

    bool    canSetStickerSet();
    void    setCanSetStickerSet(bool canSetStickerSet);
    bool    hasCanSetStickerSet();
};

#endif // CHAT_H
