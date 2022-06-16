#ifndef ABSTRACTITEM_H
#define ABSTRACTITEM_H

#include <QString>

/**
 * @brief Abstract class. Can be either security or category of securities
 */
class AbstractItem
{
public:
    AbstractItem();
    AbstractItem(QString name, AbstractItem* parent = nullptr);

    virtual bool isCategory() { return false; };

    int id;
    QString name;

    AbstractItem* parent;
};

#endif // ABSTRACTITEM_H
