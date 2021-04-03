#ifndef CHATPERMISSIONS_H
#define CHATPERMISSIONS_H

#include "Type.h"

/*!
    \brief This class describes actions that a non-administrator user is allowed to take in a chat

    Fields of ChatPermissions object
    -----------------------------------

    | Field                     | Type      | Desription  |
    | :---:                     | :----:    | :---- |
    | **canSendMessages**       | `Bool`    | **Optional**. True, if the user is allowed to send text messages, contacts, locations and venues |
    | **canSendMediaMessages**  | `Bool`    | **Optional**. True, if the user is allowed to send audios, documents, photos, videos, video notes and voice notes, implies canSendMessages |
    | **canSendPolls**          | `Bool`    | **Optional**. True, if the user is allowed to send polls, implies canSendMessages |
    | **canSendOtherMessages**  | `Bool`    | **Optional**. Restricted only. True, if the user is allowed to send animations, games, stickers and use inline bots, implies canSendMediaMessages |
    | **canAddWebPagePreviews** | `Bool`    | **Optional**. Restricted only. True, if the user is allowed to add web page previews to their messages, implies canSendMediaMessages |
    | **canChangeInfo**         | `Bool`    | **Optional**. True, if the user is allowed to change the chat title, photo and other settings. Ignored in public supergroups |
    | **canInviteUsers**        | `Bool`    | **Optional**. True, if the user is allowed to invite new users to the chat |
    | **canPinMessages**        | `Bool`    | **Optional**. True, if the user is allowed to pin messages. Ignored in public supergroups |

    In order to set **optional** fields use "set" methods ([setCustomTitle](@ref setCustomTitle), [setUntilDate](@ref setUntilDate), etc.)
*/

class TELEGRAMAPI_EXPORT ChatPermissions : public Type
{
public:
    ChatPermissions();

    ChatPermissions(QJsonObject jsonObject);

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

    bool    canChangeInfo();
    void    setCanChangeInfo(bool canChangeInfo);
    bool    hasCanChangeInfo();

    bool    canInviteUsers();
    void    setCanInviteUsers(bool canInviteUsers);
    bool    hasCanInviteUsers();

    bool    canPinMessages();
    void    setCanPinMessages(bool canPinMessages);
    bool    hasCanPinMessages();
};

#endif // CHATPERMISSIONS_H
