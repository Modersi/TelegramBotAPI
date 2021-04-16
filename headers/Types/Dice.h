#ifndef DICE_H
#define DICE_H

#include "Types/Type.h"

/*!
    \brief This class represents an animated emoji that displays a random value

    Fields of Dice object
    -----------------------------------

    | Field     | Type      | Desription  |
    | :---:     | :----:    | :---- |
    | **emoji** | `QString` | Emoji on which the dice throw animation is based |
    | **value** | `QInt32`  | Value of the dice, 1-6 for “🎲” (dice) and “🎯”(darts throw) base emoji, 1-5 for “🏀”(ball throw) base emoji |
*/

class Dice : public Type
{
public:
    Dice();

    Dice(QString emoji,
         qint32  value);

    Dice(QJsonObject jsonObject);

    QString emoji();
    void    setEmoji(QString text);

    qint32  value();
    void    setValue(qint32 voterCount);
};

#endif // DICE_H
