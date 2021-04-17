#ifndef BOTCOMMAND_H
#define BOTCOMMAND_H

#include "Types/Type.h"

/*!
    \brief This class represents a Bot Command

    Fields of BotCommand object
    -----------------------------------

    | Field             | Type          | Desription  |
    | :---:             | :----:        | :---- |
    | **command**       | `QString`     | Text of the command. <U><B>Must be 1-32 characters. Can contain only lowercase English letters, digits and underscores</B></U> |
    | **description**   | `QString`     | Description of the command. <U><B>Must be 3-256 characters</B></U> |
*/

class BotCommand : public Type
{
public:
    BotCommand();

    BotCommand(QString command,
               QString description);

    BotCommand(QJsonObject jsonObject);

    QString command();
    void    setCommand(QString command);

    QString description();
    void    setDescription(QString description);
};

#endif // BOTCOMMAND_H
