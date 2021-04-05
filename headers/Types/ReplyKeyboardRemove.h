#ifndef REPLYKEYBOARDREMOVE_H
#define REPLYKEYBOARDREMOVE_H

#include "Type.h"

class TELEGRAMAPI_EXPORT ReplyKeyboardRemove : public Type
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
