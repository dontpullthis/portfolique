#ifndef SECURITY_H
#define SECURITY_H

#include "abstractitem.h"

class Security: public AbstractItem
{
using AbstractItem::AbstractItem;
public:
    bool isCategory();
};

#endif // SECURITY_H
