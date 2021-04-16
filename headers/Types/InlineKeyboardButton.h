#ifndef INLINEKEYBOARDBUTTON_H
#define INLINEKEYBOARDBUTTON_H

#include "Types/Type.h"
#include "Types/LoginUrl.h"

/*!
    \brief This object represents one button of an inline keyboard

    Fields of InlineKeyboardButton object
    -----------------------------------

    | Field                             | Type           | Desription  |
    | :---:                             | :----:         | :---- |
    | **text**                          | `QString`      | Label text on the button |
    | **url**                           | `QString`      | **Optional**. HTTP or tg:// url to be opened when button is pressed |
    | **loginUrl**                      | `LoginUrl`     | **Optional**. An HTTP URL used to automatically authorize the user. Can be used as a replacement for the [Telegram Login Widget](https://core.telegram.org/widgets/login) |
    | **callbackData**                  | `QString`      | **Optional**. Data to be sent in a [сallback query](@ref CallbackQuery) to the bot when button is pressed, <U><B>1-64</B></U> bytes |
    | **switchInlineQuery**             | `QString`      | **Optional**. If set, pressing the button will prompt the user to select one of their chats, open that chat and insert the bot's username and the specified inline query in the input field. Can be empty, in which case just the bot's username will be inserted |
    | **switchInlineQueryCurrentChat**  | `QString`      | **Optional**. If set, pressing the button will insert the bot's username and the specified inline query in the current chat's input field. Can be empty, in which case only the bot's username will be inserted |
    | **callbackGame**                  | `CallbackGame` | **Optional**. Description of the game that will be launched when the user presses the button. **NOTE:** This type of button must always be the first button in the first row |
    | **isPay**                         | `Bool`         | **Optional**. Specify True, to send a Pay button. |

    > You **must** use exactly one of the optional fields

    In order to set **optional** fields use "set" methods ([setTitle](@ref setTitle), [setUsername](@ref setUsername), etc.)
*/

class InlineKeyboardButton : public Type
{
public:
    InlineKeyboardButton();

    InlineKeyboardButton(QString text);

    InlineKeyboardButton(QJsonObject jsonObject);

    QString         text();
    void            setText(QString text);

    QString         url();
    void            setUrl(QString url);
    bool            hasUrl();

    LoginUrl        loginUrl();
    void            setLoginUrl(LoginUrl loginUrl);
    bool            hasLoginUrl();

    QString         callbackData();
    void            setCallbackData(QString callbackData);
    bool            hasCallbackData();

    QString         switchInlineQuery();
    void            setSwitchInlineQuery(QString switchInlineQuery);
    bool            hasSwitchInlineQuery();

    QString         switchInlineQueryCurrentChat();
    void            setSwitchInlineQueryCurrentChat(QString switchInlineQueryCurrentChat);
    bool            hasSwitchInlineQueryCurrentChat();

    //CallbackGame    callbackGame();
    //void            setCallbackGame(CallbackGame callbackGame);
    //bool            hasCallbackGame();

    bool            isPay();
    void            setPay(bool pay);
    bool            hasPay();
};

#endif // INLINEKEYBOARDBUTTON_H
