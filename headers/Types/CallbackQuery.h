#ifndef CALLBACKQUERY_H
#define CALLBACKQUERY_H

#include "Type.h"
#include "User.h"
#include "Message.h"

/*!
    \brief This object represents an incoming Callback Query from a callback button in an inline keyboard

    Fields of CallbackQuery object
    -----------------------------------

    | Field                 | Type          | Desription  |
    | :---:                 | :----:        | :---- |
    | **id**                | `QString`     | Unique identifier for this query |
    | **from**              | `User`        | Sender |
    | **chatInstance**      | `QString`     | Global identifier, uniquely corresponding to the chat to which the message with the callback button was sent. Useful for high scores in games |
    | **message**           | `Message`     | **Optional**. Message with the callback button that originated the query. Note that message content and message date will not be available if the message is too old |
    | **inlineMessageId**   | `QString`     | **Optional**. Identifier of the message sent via the bot in inline mode, that originated the query |
    | **data**              | `QString`     | **Optional**. Data associated with the callback button. Be aware that a bad client can send arbitrary data in this field |
    | **gameShortName**     | `QString`     | **Optional**. Short name of a Game to be returned, serves as the unique identifier for the game |

    If the button that originated the query was attached to a message sent by the bot, the field message will be present.
    If the button was attached to a message sent via the bot (in inline mode), the field inlineMessageId will be present.
    Exactly one of the fields data or gameShortName will be present.

    > **NOTE:** After the user presses a callback button, Telegram clients will display a progress bar until you call answerCallbackQuery.
    > It is, therefore, necessary to react by calling answerCallbackQuery even if no notification to the user is needed
    > (e.g., without specifying any of the optional parameters).
*/

class TELEGRAMAPI_EXPORT CallbackQuery : public Type
{
public:
    CallbackQuery();

    CallbackQuery(QString id,
                  User    from,
                  QString chatInstance);

    CallbackQuery(QJsonObject jsonObject);

    QString id();
    void    setId(QString id);

    User    user();
    void    setUser(User user);

    Message message();
    void    setMessage(Message message);
    bool    hasMessage();

    QString inlineMessageId();
    void    setInlineMessageId(QString inlineMessageId);
    bool    hasInlineMessageId();

    QString chatInstance();
    void    setChatInstance(QString chatInstance);

    QString data();
    void    setData(QString data);
    bool    hasData();

    QString gameShortName();
    void    setGameShortName(QString gameShortName);
    bool    hasGameShortName();
};

#endif // CALLBACKQUERY_H
