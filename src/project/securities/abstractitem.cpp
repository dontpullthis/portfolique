#include "abstractitem.h"

AbstractItem::AbstractItem(QString name, AbstractItem* parent)
{
    this->id = -1;
    this->name = name;
    this->parent = parent;
}
