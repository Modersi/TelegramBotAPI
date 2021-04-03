#include "BotCommand.h"

/*!
    \brief A default constructor. Constructs an empty object
*/
BotCommand::BotCommand() {}

/*!
    \brief Class contructor
    \param command       Text of the command, 1-32 characters. Can contain only lowercase English letters, digits and underscores
    \param description   Description of the command, 3-256 characters
*/
BotCommand::BotCommand(QString command,
                       QString description)
{
    this->setCommand(command);
    this->setDescription(description);
}

/*!
    \brief Constructor from QJsonObject
    \param QJsonObject QJsonObject which contains fields suitable for the class
*/
BotCommand::BotCommand(QJsonObject jsonObject)
{
    if(jsonObject.contains("command"))
        _jsonObject.insert("command", jsonObject.value("command"));

    if(jsonObject.contains("description"))
        _jsonObject.insert("description", jsonObject.value("description"));
}


/***//*!
    \brief Get **command** value
    \return Value of **command**
*/
QString BotCommand::command()
{
    return _jsonObject.value("command").toString();
}

/*!
    \brief Set new value for **command**
    \param QString New value of **command**
*/
void BotCommand::setCommand(QString command)
{
    for(int i = 0; i < command.size(); i++)
    {
        if((command[i].unicode() < 48 || command[i].unicode() > 57) &&          // Check if command contain something other than only digits (48 - 57 in Unicode),
           (command[i].unicode() < 97 || command[i].unicode() > 122) &&         // lowercase English letters (97 - 122 in Unicode)
            command[i].unicode() != 95)                                         // and underscores (95 in Unicode),
        {                                                                       //
            command.remove(i, 1);                                               // if yes - remove unallowed symbol
            i--;
        }
    }

    if(command.size() < 1 || command.size() > 32)                               // Check if command lenght is less than 1 or greater than 32 characters,
        command = "wrong_command";                                              // if yes - put error message instead of command

    _jsonObject.insert("command", command);
}


/***//*!
    \brief Get **description** value
    \return Value of **description**
*/
QString BotCommand::description()
{
    return _jsonObject.value("description").toString();
}

/*!
    \brief Set new value for **description**
    \param QString New value of **description**
*/
void BotCommand::setDescription(QString description)
{
    if(description.size() < 3 && description.size() > 256)                      // Check if description lenght is less than 3 or greater than 256 characters,
        description = "Description lenght must be 3-256 symbols";               // if yes - put error message instead of description
    _jsonObject.insert("description", description);
}
