#ifndef ABSTRACTITEM_H
#define ABSTRACTITEM_H

#include <QString>

/**
 * @brief Abstract class. Can be either security or category of securities
 */
class AbstractItem
{
public:
    AbstractItem(QString name, AbstractItem* parent = nullptr);

    virtual bool isCategory() { return false; };

    QString name;
private:

    AbstractItem* parent;
};

#endif // ABSTRACTITEM_H
