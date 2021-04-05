#include "ChatPermissions.h"

/*!
    \brief A default constructor. Constructs an empty object
*/
ChatPermissions::ChatPermissions() {}

/*!
    \brief Constructor from QJsonObject
    \param QJsonObject QJsonObject which contains fields suitable for the class
*/
ChatPermissions::ChatPermissions(QJsonObject jsonObject)
{
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

    if(jsonObject.contains("can_change_info"))
        _jsonObject.insert("can_change_info", jsonObject.value("can_change_info"));

    if(jsonObject.contains("can_invite_users"))
        _jsonObject.insert("can_invite_users", jsonObject.value("can_invite_users"));

    if(jsonObject.contains("can_pin_messages"))
        _jsonObject.insert("can_pin_messages", jsonObject.value("can_pin_messages"));
}


/***//*!
    \brief Get **canSendMessages** value
    \return Value of **canSendMessages**
*/
bool ChatPermissions::canSendMessages()
{
    return _jsonObject.value("can_send_messages").toBool();
}

/*!
    \brief Set new value for **canSendMessages**
    \param bool New value of **canSendMessages**
*/
void ChatPermissions::setCanSendMessages(bool canSendMessages)
{
    _jsonObject.insert("can_send_messages", canSendMessages);
}

/*!
    \brief Check if object has **canSendMessages** field
    \return `True` if has **canSendMessages** field, `false` if doesn't
*/
bool ChatPermissions::hasCanSendMessages()
{
    return _jsonObject.contains("can_send_messages");
}


/***//*!
    \brief Get **canSendMediaMessages** value
    \return Value of **canSendMediaMessages**
*/
bool ChatPermissions::canSendMediaMessages()
{
    return _jsonObject.value("can_send_media_messages").toBool();
}

/*!
    \brief Set new value for **canSendMediaMessages**
    \param bool New value of **canSendMediaMessages**
*/
void ChatPermissions::setCanSendMediaMessages(bool canSendMediaMessages)
{
    _jsonObject.insert("can_send_media_messages", canSendMediaMessages);
}

/*!
    \brief Check if object has **canSendMediaMessages** field
    \return `True` if has **canSendMediaMessages** field, `false` if doesn't
*/
bool ChatPermissions::hasCanSendMediaMessages()
{
    return _jsonObject.contains("can_send_media_messages");
}


/***//*!
    \brief Get **canSendPolls** value
    \return Value of **canSendPolls**
*/
bool ChatPermissions::canSendPolls()
{
    return _jsonObject.value("can_send_polls").toBool();
}

/*!
    \brief Set new value for **canSendPolls**
    \param bool New value of **canSendPolls**
*/
void ChatPermissions::setCanSendPolls(bool canSendPolls)
{
    _jsonObject.insert("can_send_polls", canSendPolls);
}

/*!
    \brief Check if object has **canSendPolls** field
    \return `True` if has **canSendPolls** field, `false` if doesn't
*/
bool ChatPermissions::hasCanSendPolls()
{
    return _jsonObject.contains("can_send_polls");
}


/***//*!
    \brief Get **canSendOtherMessages** value
    \return Value of **canSendOtherMessages**
*/
bool ChatPermissions::canSendOtherMessages()
{
    return _jsonObject.value("can_send_other_messages").toBool();
}

/*!
    \brief Set new value for **canSendOtherMessages**
    \param bool New value of **canSendOtherMessages**
*/
void ChatPermissions::setCanSendOtherMessagess(bool canSendOtherMessages)
{
    _jsonObject.insert("can_send_other_messages", canSendOtherMessages);
}

/*!
    \brief Check if object has **canSendOtherMessages** field
    \return `True` if has **canSendOtherMessages** field, `false` if doesn't
*/
bool ChatPermissions::hasCanSendOtherMessagess()
{
    return _jsonObject.contains("can_send_other_messages");
}


/***//*!
    \brief Get **canAddWebPagePreviews** value
    \return Value of **canAddWebPagePreviews**
*/
bool ChatPermissions::canAddWebPagePreviews()
{
    return _jsonObject.value("can_add_web_page_previews").toBool();
}

/*!
    \brief Set new value for **canAddWebPagePreviews**
    \param bool New value of **canAddWebPagePreviews**
*/
void ChatPermissions::setCanAddWebPagePreviews(bool canAddWebPagePreviews)
{
    _jsonObject.insert("can_add_web_page_previews", canAddWebPagePreviews);
}

/*!
    \brief Check if object has **canAddWebPagePreviews** field
    \return `True` if has **canAddWebPagePreviews** field, `false` if doesn't
*/
bool ChatPermissions::hasCanAddWebPagePreviews()
{
    return _jsonObject.contains("can_add_web_page_previews");
}


/***//*!
    \brief Get **canChangeInfo** value
    \return Value of **canChangeInfo**
*/
bool ChatPermissions::canChangeInfo()
{
    return _jsonObject.value("can_change_info").toBool();
}

/*!
    \brief Set new value for **setCanChangeInfo**
    \param bool New value of **setCanChangeInfo**
*/
void ChatPermissions::setCanChangeInfo(bool canChangeInfo)
{
    _jsonObject.insert("can_change_info", canChangeInfo);
}

/*!
    \brief Check if object has **setCanChangeInfo** field
    \return `True` if has **setCanChangeInfo** field, `false` if doesn't
*/
bool ChatPermissions::hasCanChangeInfo()
{
    return _jsonObject.contains("can_change_info");
}


/***//*!
    \brief Get **canInviteUsers** value
    \return Value of **canInviteUsers**
*/
bool ChatPermissions::canInviteUsers()
{
    return _jsonObject.value("can_invite_users").toBool();
}

/*!
    \brief Set new value for **canInviteUsers**
    \param bool New value of **canInviteUsers**
*/
void ChatPermissions::setCanInviteUsers(bool canInviteUsers)
{
    _jsonObject.insert("can_invite_users", canInviteUsers);
}

/*!
    \brief Check if object has **canInviteUsers** field
    \return `True` if has **canInviteUsers** field, `false` if doesn't
*/
bool ChatPermissions::hasCanInviteUsers()
{
    return _jsonObject.contains("can_invite_users");
}


/***//*!
    \brief Get **canPinMessages** value
    \return Value of **canPinMessages**
*/
bool ChatPermissions::canPinMessages()
{
    return _jsonObject.value("can_pin_messages").toBool();
}

/*!
    \brief Set new value for **canPinMessages**
    \param bool New value of **canPinMessages**
*/
void ChatPermissions::setCanPinMessages(bool canPinMessages)
{
    _jsonObject.insert("can_pin_messages", canPinMessages);
}

/*!
    \brief Check if object has **canPinMessages** field
    \return `True` if has **canPinMessages** field, `false` if doesn't
*/
bool ChatPermissions::hasCanPinMessages()
{
    return _jsonObject.contains("can_pin_messages");
}
