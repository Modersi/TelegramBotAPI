#include "ChatMember.h"

/*!
    \brief A default constructor. Constructs an empty object
*/
ChatMember::ChatMember() {}


/*!
    \brief Class contructor
    \param user     Information about the user
    \param status   The member's status in the chat. Can be “creator”, “administrator”, “member”, “restricted”, “left” or “kicked”
*/
ChatMember::ChatMember(User     user,
                       QString  status)
{
    _jsonObject.insert("user", user.toObject());
    _jsonObject.insert("status", status);
}

/*!
    \brief Constructor from QJsonObject
    \param QJsonObject QJsonObject which contains fields suitable for the class
*/
ChatMember::ChatMember(QJsonObject jsonObject)
{
    if(jsonObject.contains("user"))
        _jsonObject.insert("user", jsonObject.value("user"));

    if(jsonObject.contains("status"))
        _jsonObject.insert("status", jsonObject.value("status"));

    if(jsonObject.contains("custom_title"))
        _jsonObject.insert("custom_title", jsonObject.value("custom_title"));

    if(jsonObject.contains("until_date"))
        _jsonObject.insert("until_date", jsonObject.value("until_date"));

    if(jsonObject.contains("can_be_edited"))
        _jsonObject.insert("can_be_edited", jsonObject.value("can_be_edited"));

    if(jsonObject.contains("can_post_messages"))
        _jsonObject.insert("can_post_messages", jsonObject.value("can_post_messages"));

    if(jsonObject.contains("can_edit_messages"))
        _jsonObject.insert("can_edit_messages", jsonObject.value("can_edit_messages"));

    if(jsonObject.contains("can_delete_messages"))
        _jsonObject.insert("can_delete_messages", jsonObject.value("can_delete_messages"));

    if(jsonObject.contains("can_restrict_members"))
        _jsonObject.insert("can_restrict_members", jsonObject.value("can_restrict_members"));

    if(jsonObject.contains("can_promote_members"))
        _jsonObject.insert("can_promote_members", jsonObject.value("can_promote_members"));

    if(jsonObject.contains("can_change_info"))
        _jsonObject.insert("can_change_info", jsonObject.value("can_change_info"));

    if(jsonObject.contains("can_invite_users"))
        _jsonObject.insert("can_invite_users", jsonObject.value("can_invite_users"));

    if(jsonObject.contains("can_pin_messages"))
        _jsonObject.insert("can_pin_messages", jsonObject.value("can_pin_messages"));

    if(jsonObject.contains("is_member"))
        _jsonObject.insert("is_member", jsonObject.value("is_member"));

    if(jsonObject.contains("can_send_messages"))
        _jsonObject.insert("can_send_messages", jsonObject.value("can_send_messages"));

    if(jsonObject.contains("can_send_media_messages"))
        _jsonObject.insert("can_send_media_messages", jsonObject.value("can_send_media_messages"));

    if(jsonObject.contains("can_send_polls"))
        _jsonObject.insert("can_send_polls", jsonObject.value("can_send_polls"));

    if(jsonObject.contains("can_send_other_messages"))
        _jsonObject.insert("can_send_other_messages", jsonObject.value("can_send_other_messages"));

    if(jsonObject.contains("can_add_web_page_previews"))
        _jsonObject.insert("can_add_web_page_previews", jsonObject.value("can_add_web_page_previews"));
}


/***//*!
    \brief Get **user** value
    \return Value of **user** in form of `User` object
*/
User ChatMember::user()
{
    return User(_jsonObject.value("user").toObject());
}

/*!
    \brief Set new value for **user**
    \param User New value of **user**
*/
void ChatMember::setUser(User user)
{
    _jsonObject.insert("user", user.toObject());
}


/***//*!
    \brief Get **status** value
    \return Value of **status**
*/
QString ChatMember::status()
{
    return _jsonObject.value("status").toString();
}

/*!
    \brief Set new value for **status**
    \param QString New value of **status**
*/
void ChatMember::setStatus(QString status)
{
    _jsonObject.insert("status", status);
}


/***//*!
    \brief Get **customTitle** value
    \return Value of **customTitle**
*/
QString ChatMember::customTitle()
{
    return _jsonObject.value("custom_title").toString();
}

/*!
    \brief Set new value for **customTitle**
    \param QString New value of **customTitle**
*/
void ChatMember::setCustomTitle(QString customTitle)
{
    _jsonObject.insert("custom_title", customTitle);
}

/*!
    \brief Check if object has **customTitle**
    \return `True` if has **customTitle**, `false` if doesn't
*/
bool ChatMember::hasCustomTitle()
{
    return _jsonObject.contains("custom_title");
}


/***//*!
    \brief Get **untilDate** value
    \return Value of **untilDate**
*/
qint32 ChatMember::untilDate()
{
    return _jsonObject.value("until_date").toInt();
}

/*!
    \brief Set new value for **untilDate**
    \param qint32 New value of **untilDate**
*/
void ChatMember::setUntilDate(qint32 untilDate)
{
    _jsonObject.insert("until_date", untilDate);
}

/*!
    \brief Check if object has **untilDate**
    \return `True` if has **untilDate**, `false` if doesn't
*/
bool ChatMember::hasUntilDate()
{
    return _jsonObject.contains("until_date");
}


/***//*!
    \brief Get **canBeEdited** value
    \return Value of **canBeEdited**
*/
bool ChatMember::canBeEdited()
{
    return _jsonObject.value("can_be_edited").toBool();
}

/*!
    \brief Set new value for **canBeEdited**
    \param bool New value of **canBeEdited**
*/
void ChatMember::setCanBeEdited(bool canBeEdited)
{
    _jsonObject.insert("can_be_edited", canBeEdited);
}

/*!
    \brief Check if object has **canBeEdited** field
    \return `True` if has **canBeEdited** field, `false` if doesn't
*/
bool ChatMember::hasCanBeEdited()
{
    return _jsonObject.contains("can_be_edited");
}


/***//*!
    \brief Get **canPostMessages** value
    \return Value of **canPostMessages**
*/
bool ChatMember::canPostMessages()
{
    return _jsonObject.value("can_post_messages").toBool();
}

/*!
    \brief Set new value for **canPostMessages**
    \param bool New value of **canPostMessages**
*/
void ChatMember::setCanPostMessages(bool canPostMessages)
{
    _jsonObject.insert("can_post_messages", canPostMessages);
}

/*!
    \brief Check if object has **canPostMessages** field
    \return `True` if has **canPostMessages** field, `false` if doesn't
*/
bool ChatMember::hasCanPostMessages()
{
    return _jsonObject.contains("can_post_messages");
}


/***//*!
    \brief Get **canEditMessages** value
    \return Value of **canEditMessages**
*/
bool ChatMember::canEditMessages()
{
    return _jsonObject.value("can_edit_messages").toBool();
}

/*!
    \brief Set new value for **canEditMessages**
    \param bool New value of **canEditMessages**
*/
void ChatMember::setCanEditMessages(bool canEditMessages)
{
    _jsonObject.insert("can_edit_messages", canEditMessages);
}

/*!
    \brief Check if object has **canEditMessages** field
    \return `True` if has **canEditMessages** field, `false` if doesn't
*/
bool ChatMember::hasCanEditMessages()
{
    return _jsonObject.contains("can_edit_messages");
}


/***//*!
    \brief Get **canDeleteMessages** value
    \return Value of **canDeleteMessages**
*/
bool ChatMember::canDeleteMessages()
{
    return _jsonObject.value("can_delete_messages").toBool();
}

/*!
    \brief Set new value for **canDeleteMessages**
    \param bool New value of **canDeleteMessages**
*/
void ChatMember::setCanDeleteMessages(bool canDeleteMessages)
{
    _jsonObject.insert("can_delete_messages", canDeleteMessages);
}

/*!
    \brief Check if object has **canDeleteMessages** field
    \return `True` if has **canDeleteMessages** field, `false` if doesn't
*/
bool ChatMember::hasCanDeleteMessages()
{
    return _jsonObject.contains("can_delete_messages");
}


/***//*!
    \brief Get **canRestrictMembers** value
    \return Value of **canRestrictMembers**
*/
bool ChatMember::canRestrictMembers()
{
    return _jsonObject.value("can_restrict_members").toBool();
}

/*!
    \brief Set new value for **canRestrictMembers**
    \param bool New value of **canRestrictMembers**
*/
void ChatMember::setCanRestrictMembers(bool canRestrictMembers)
{
    _jsonObject.insert("can_restrict_members", canRestrictMembers);
}

/*!
    \brief Check if object has **canRestrictMembers** field
    \return `True` if has **canRestrictMembers** field, `false` if doesn't
*/
bool ChatMember::hasCanRestrictMembers()
{
    return _jsonObject.contains("can_restrict_members");
}


/***//*!
    \brief Get **canPromoteMembers** value
    \return Value of **canPromoteMembers**
*/
bool ChatMember::canPromoteMembers()
{
    return _jsonObject.value("can_promote_members").toBool();
}

/*!
    \brief Set new value for **canPromoteMembers**
    \param bool New value of **canPromoteMembers**
*/
void ChatMember::setCanPromoteMembers(bool canPromoteMembers)
{
    _jsonObject.insert("can_promote_members", canPromoteMembers);
}

/*!
    \brief Check if object has **canPromoteMembers** field
    \return `True` if has **canPromoteMembers** field, `false` if doesn't
*/
bool ChatMember::hasCanPromoteMembers()
{
    return _jsonObject.contains("can_promote_members");
}


/***//*!
    \brief Get **canChangeInfo** value
    \return Value of **canChangeInfo**
*/
bool ChatMember::canChangeInfo()
{
    return _jsonObject.value("can_change_info").toBool();
}

/*!
    \brief Set new value for **canChangeInfo**
    \param bool New value of **canChangeInfo**
*/
void ChatMember::setCanChangeInfo(bool canChangeInfo)
{
    _jsonObject.insert("can_change_info", canChangeInfo);
}

/*!
    \brief Check if object has **canChangeInfo** field
    \return `True` if has **canChangeInfo** field, `false` if doesn't
*/
bool ChatMember::hasCanChangeInfo()
{
    return _jsonObject.contains("can_change_info");
}


/***//*!
    \brief Get **canInviteUsers** value
    \return Value of **canInviteUsers**
*/
bool ChatMember::canInviteUsers()
{
    return _jsonObject.value("can_invite_users").toBool();
}

/*!
    \brief Set new value for **canInviteUsers**
    \param bool New value of **canInviteUsers**
*/
void ChatMember::setCanInviteUsers(bool canInviteUsers)
{
    _jsonObject.insert("can_invite_users", canInviteUsers);
}

/*!
    \brief Check if object has **canInviteUsers** field
    \return `True` if has **canInviteUsers** field, `false` if doesn't
*/
bool ChatMember::hasCanInviteUsers()
{
    return _jsonObject.contains("can_invite_users");
}


/***//*!
    \brief Get **canPinMessages** value
    \return Value of **canPinMessages**
*/
bool ChatMember::canPinMessages()
{
    return _jsonObject.value("can_pin_messages").toBool();
}

/*!
    \brief Set new value for **canPinMessages**
    \param bool New value of **canPinMessages**
*/
void ChatMember::setCanPinMessages(bool canPinMessages)
{
    _jsonObject.insert("can_pin_messages", canPinMessages);
}

/*!
    \brief Check if object has **canPinMessages** field
    \return `True` if has **canPinMessages** field, `false` if doesn't
*/
bool ChatMember::hasCanPinMessages()
{
    return _jsonObject.contains("can_pin_messages");
}


/***//*!
    \brief Get **isMember** value
    \return Value of **isMember**
*/
bool ChatMember::isMember()
{
    return _jsonObject.value("is_member").toBool();
}

/*!
    \brief Set new value for **isMember**
    \param bool New value of **isMember**
*/
void ChatMember::setIsMember(bool isMember)
{
    _jsonObject.insert("is_member", isMember);
}

/*!
    \brief Check if object has **isMember** field
    \return `True` if has **isMember** field, `false` if doesn't
*/
bool ChatMember::hasIsMember()
{
    return _jsonObject.contains("is_member");
}


/***//*!
    \brief Get **canSendMessages** value
    \return Value of **canSendMessages**
*/
bool ChatMember::canSendMessages()
{
    return _jsonObject.value("can_send_messages").toBool();
}

/*!
    \brief Set new value for **canSendMessages**
    \param bool New value of **canSendMessages**
*/
void ChatMember::setCanSendMessages(bool canSendMessages)
{
    _jsonObject.insert("can_send_messages", canSendMessages);
}

/*!
    \brief Check if object has **canSendMessages** field
    \return `True` if has **canSendMessages** field, `false` if doesn't
*/
bool ChatMember::hasCanSendMessages()
{
    return _jsonObject.contains("can_send_messages");
}


/***//*!
    \brief Get **canSendMediaMessages** value
    \return Value of **canSendMediaMessages**
*/
bool ChatMember::canSendMediaMessages()
{
    return _jsonObject.value("can_send_media_messages").toBool();
}

/*!
    \brief Set new value for **canSendMediaMessages**
    \param bool New value of **canSendMediaMessages**
*/
void ChatMember::setCanSendMediaMessages(bool canSendMediaMessages)
{
    _jsonObject.insert("can_send_media_messages", canSendMediaMessages);
}

/*!
    \brief Check if object has **canSendMediaMessages** field
    \return `True` if has **canSendMediaMessages** field, `false` if doesn't
*/
bool ChatMember::hasCanSendMediaMessages()
{
    return _jsonObject.contains("can_send_media_messages");
}


/***//*!
    \brief Get **canSendPolls** value
    \return Value of **canSendPolls**
*/
bool ChatMember::canSendPolls()
{
    return _jsonObject.value("can_send_polls").toBool();
}

/*!
    \brief Set new value for **canSendPolls**
    \param bool New value of **canSendPolls**
*/
void ChatMember::setCanSendPolls(bool canSendPolls)
{
    _jsonObject.insert("can_send_polls", canSendPolls);
}

/*!
    \brief Check if object has **canSendPolls** field
    \return `True` if has **canSendPolls** field, `false` if doesn't
*/
bool ChatMember::hasCanSendPolls()
{
    return _jsonObject.contains("can_send_polls");
}


/***//*!
    \brief Get **canSendOtherMessages** value
    \return Value of **canSendOtherMessages**
*/
bool ChatMember::canSendOtherMessages()
{
    return _jsonObject.value("can_send_other_messages").toBool();
}

/*!
    \brief Set new value for **canSendOtherMessages**
    \param bool New value of **canSendOtherMessages**
*/
void ChatMember::setCanSendOtherMessagess(bool canSendOtherMessages)
{
    _jsonObject.insert("can_send_other_messages", canSendOtherMessages);
}

/*!
    \brief Check if object has **canSendOtherMessages** field
    \return `True` if has **canSendOtherMessages** field, `false` if doesn't
*/
bool ChatMember::hasCanSendOtherMessagess()
{
    return _jsonObject.contains("can_send_other_messages");
}


/***//*!
    \brief Get **canAddWebPagePreviews** value
    \return Value of **canAddWebPagePreviews**
*/
bool ChatMember::canAddWebPagePreviews()
{
    return _jsonObject.value("can_add_web_page_previews").toBool();
}

/*!
    \brief Set new value for **canAddWebPagePreviews**
    \param bool New value of **canAddWebPagePreviews**
*/
void ChatMember::setCanAddWebPagePreviews(bool canAddWebPagePreviews)
{
    _jsonObject.insert("can_add_web_page_previews", canAddWebPagePreviews);
}

/*!
    \brief Check if object has **canAddWebPagePreviews** field
    \return `True` if has **canAddWebPagePreviews** field, `false` if doesn't
*/
bool ChatMember::hasCanAddWebPagePreviews()
{
    return _jsonObject.contains("can_add_web_page_previews");
}
