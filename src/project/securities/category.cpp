#include "category.h"

bool Category::isCategory()
{
    return true;
}

void Category::addChild(AbstractItem* child)
{
    this->children.append(child);
}
