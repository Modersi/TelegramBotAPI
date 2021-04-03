#ifndef CHATMEMBER_H
#define CHATMEMBER_H

#include "Type.h"
#include "User.h"

/*!
    \brief This class represents a Chat Member

    Fields of ChatMember object
    -----------------------------------

    | Field                     | Type      | Desription  |
    | :---:                     | :----:    | :---- |
    | **user**                  | `User`    | Information about the user |
    | **status**                | `QString` | The member's status in the chat. <U><B>Can be only “creator”, “administrator”, “member”, “restricted”, “left” or “kicked” </B></U> |
    | **customTitle**           | `QString` | **Optional**. Owner and administrators only. Custom title for this user |
    | **untilDate**             | `QInt32`  | **Optional**. Restricted and kicked only. Date when restrictions will be lifted for this user; unix time |
    | **canBeEdited**           | `Bool`    | **Optional**. Administrators only. True, if the bot is allowed to edit administrator privileges of that user |
    | **canPostMessages**       | `Bool`    | **Optional**. Administrators only. True, if the administrator can post in the channel; channels only |
    | **canEditMessages**       | `Bool`    | **Optional**. Administrators only. True, if the administrator can edit messages of other users and can pin messages; channels only |
    | **canDeleteMessages**     | `Bool`    | **Optional**. Administrators only. True, if the administrator can delete messages of other users |
    | **canRestrictMembers**    | `Bool`    | **Optional**. Administrators only. True, if the administrator can restrict, ban or unban chat members |
    | **canPromoteMembers**     | `Bool`    | **Optional**. Administrators only. True, if the administrator can add new administrators with a subset of their own privileges or demote administrators that he has promoted, directly or indirectly (promoted by administrators that were appointed by the user) |
    | **canChangeInfo**         | `Bool`    | **Optional**. Administrators and restricted only. True, if the user is allowed to change the chat title, photo and other settings |
    | **canInviteUsers**        | `Bool`    | **Optional**. Administrators and restricted only. True, if the user is allowed to invite new users to the chat |
    | **canPinMessages**        | `Bool`    | **Optional**. Administrators and restricted only. True, if the user is allowed to pin messages; groups and supergroups only |
    | **isMember**              | `Bool`    | **Optional**. Restricted only. True, if the user is a member of the chat at the moment of the request |
    | **canSendMessages**       | `Bool`    | **Optional**. Restricted only. True, if the user is allowed to send text messages, contacts, locations and venues |
    | **canSendMediaMessages**  | `Bool`    | **Optional**. Restricted only. True, if the user is allowed to send audios, documents, photos, videos, video notes and voice notes |
    | **canSendPolls**          | `Bool`    | **Optional**. Restricted only. True, if the user is allowed to send polls |
    | **canSendOtherMessages**  | `Bool`    | **Optional**. Restricted only. True, if the user is allowed to send animations, games, stickers and use inline bots |
    | **canAddWebPagePreviews** | `Bool`    | **Optional**. Restricted only. True, if the user is allowed to add web page previews to their messages |

    In order to set **optional** fields use "set" methods ([setCustomTitle](@ref setCustomTitle), [setUntilDate](@ref setUntilDate), etc.)
*/

class TELEGRAMAPI_EXPORT ChatMember : public Type
{
public:
    ChatMember();

    ChatMember(User    user,
               QString status);

    ChatMember(QJsonObject jsonObject);

    User    user();
    void    setUser(User user);

    QString status();
    void    setStatus(QString status);

    QString customTitle();
    void    setCustomTitle(QString customTitle);
    bool    hasCustomTitle();

    qint32  untilDate();
    void    setUntilDate(qint32 untilDate);
    bool    hasUntilDate();

    bool    canBeEdited();
    void    setCanBeEdited(bool canBeEdited);
    bool    hasCanBeEdited();

    bool    canPostMessages();
    void    setCanPostMessages(bool canPostMessages);
    bool    hasCanPostMessages();

    bool    canEditMessages();
    void    setCanEditMessages(bool canEditMessages);
    bool    hasCanEditMessages();

    bool    canDeleteMessages();
    void    setCanDeleteMessages(bool canDeleteMessages);
    bool    hasCanDeleteMessages();

    bool    canRestrictMembers();
    void    setCanRestrictMembers(bool canRestrictMembers);
    bool    hasCanRestrictMembers();

    bool    canPromoteMembers();
    void    setCanPromoteMembers(bool canPromoteMembers);
    bool    hasCanPromoteMembers();

    bool    canChangeInfo();
    void    setCanChangeInfo(bool canChangeInfo);
    bool    hasCanChangeInfo();

    bool    canInviteUsers();
    void    setCanInviteUsers(bool canInviteUsers);
    bool    hasCanInviteUsers();

    bool    canPinMessages();
    void    setCanPinMessages(bool canPinMessages);
    bool    hasCanPinMessages();

    bool    isMember();
    void    setIsMember(bool isMember);
    bool    hasIsMember();

    bool    canSendMessages();
    void    setCanSendMessages(bool canSendMessages);
    bool    hasCanSendMessages();

    bool    canSendMediaMessages();
    void    setCanSendMediaMessages(bool canSendMediaMessages);
    bool    hasCanSendMediaMessages();

    bool    canSendPolls();
    void    setCanSendPolls(bool canSendPolls);
    bool    hasCanSendPolls();

    bool    canSendOtherMessages();
    void    setCanSendOtherMessagess(bool canSendOtherMessages);
    bool    hasCanSendOtherMessagess();

    bool    canAddWebPagePreviews();
    void    setCanAddWebPagePreviews(bool canAddWebPagePreviews);
    bool    hasCanAddWebPagePreviews();
};

#endif // CHATMEMBER_H
