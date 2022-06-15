#ifndef CATEGORY_H
#define CATEGORY_H

#include <QList>

#include "abstractitem.h"

class Category: public AbstractItem
{
using AbstractItem::AbstractItem;
public:
    bool isCategory();

    void addChild(AbstractItem* child);
public:
    QList<AbstractItem*> children;
};

#endif // CATEGORY_H
