#include "security.h"

Security::Security() :
    AbstractItem(),
    decimalNumbers(0)
{
}

Security::Security(QString name, AbstractItem* parent) :
    AbstractItem(name, parent),
    decimalNumbers(0)
{

}

bool Security::isCategory()
{
    return false;
}
