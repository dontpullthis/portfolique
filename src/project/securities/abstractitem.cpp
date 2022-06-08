#include "abstractitem.h"

AbstractItem::AbstractItem(QString name, AbstractItem* parent)
{
    this->name = name;
    this->parent = parent;
}
