#ifndef SECURITY_H
#define SECURITY_H

#include "abstractitem.h"
#include "category.h"

class Security: public AbstractItem
{
public:
    Security();
    Security(QString name, AbstractItem* parent = nullptr);
    bool isCategory();

    QString code;
    int decimalNumbers;
};

#endif // SECURITY_H
