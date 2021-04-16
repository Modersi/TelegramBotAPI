#ifndef INLINEKEYBOARDMARKUP_H
#define INLINEKEYBOARDMARKUP_H

#include "Types/Type.h"
#include "Types/InlineKeyboardButton.h"

/*!
    \brief This class represents an inline keyboard that appears right next to the message it belongs to

    Fields of InlineKeyboardMarkup object
    -----------------------------------

    | Field              | Type                                    | Desription  |
    | :---:              | :----:                                  | :---- |
    | **inlineKeyboard** | `QVector<QVector<InlineKeyboardButton>> | QVector of button rows, each represented by an QVector of [InlineKeyboardButton](@ref InlineKeyboardButton) objects |

    > **Note:** This will only work in Telegram versions released after 9 April, 2016. Older clients will display unsupported message
*/

class InlineKeyboardMarkup : public Type
{
public:
    InlineKeyboardMarkup();

    InlineKeyboardMarkup(QVector<QVector<InlineKeyboardButton>> inlineKeyboard);

    InlineKeyboardMarkup(QJsonObject jsonObject);

    QVector<QVector<InlineKeyboardButton>>  inlineKeyboard();
    void                                    setInlineKeyboard(QVector<QVector<InlineKeyboardButton>> keyboard);
};

#endif // INLINEKEYBOARDMARKUP_H
