#ifndef REPLYKEYBOARDREMOVE_H
#define REPLYKEYBOARDREMOVE_H

#include "Types/Type.h"

class ReplyKeyboardRemove : public Type
{
public:
    ReplyKeyboardRemove(); // Раздуплить с этой хуйней и вообще со всем бул значениями этой параши

    ReplyKeyboardRemove(bool selective = false);

    ReplyKeyboardRemove(QJsonObject jsonObject);

    bool isSelective();
    void setSelective(bool selective);
    bool hasSelective();
};

#endif // REPLYKEYBOARDREMOVE_H
