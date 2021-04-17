#ifndef CONTACT_H
#define CONTACT_H

#include "Types/Type.h"

/*!
    \brief This class represents a phone Contact

    Fields of Contact object
    -----------------------------------

    | Field                 | Type              | Desription  |
    | :---:                 | :----:            | :---- |
    | **phoneNumber**       | `QString`          | Contact's phone number |
    | **firstName**         | `QString`         | Contact's first name |
    | **lastName**          | `QString`         | **Optional**. Contact's last name |
    | **userId**            | `QInt32`          | **Optional**. Contact's user identifier in Telegram |
    | **vcard**             | `QString`         | **Optional**. Additional data about the contact in the form of a [vCard](https://en.wikipedia.org/wiki/VCard) |

    In order to set **optional** fields use "set" methods ([setLastName](@ref setLastName), [setUserId](@ref setUserId), etc.)
*/

class Contact : public Type
{
public:
    Contact();

    Contact(QString phoneNumber,
            QString firstName);

    Contact(QJsonObject jsonObject);

    QString phoneNumber();
    void    setPhoneNumber(QString phoneNumber);

    QString firstName();
    void    setFirstName(QString firstName);

    QString lastName();
    void    setLastName(QString lastName);
    bool    hasLastName();

    qint32  userId();
    void    setUserId(qint32 userId);
    bool    hasUserId();

    QString vcard();
    void    setVcard(QString vcard);
    bool    hasVcard();
};
#endif // CONTACT_H
