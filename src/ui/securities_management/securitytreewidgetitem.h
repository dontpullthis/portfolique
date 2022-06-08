#ifndef SECURITYTREEWIDGETITEM_H
#define SECURITYTREEWIDGETITEM_H

#include <QWidget>
#include <QTreeWidget>

#include "src/project/securities/abstractitem.h"

class Q_WIDGETS_EXPORT SecurityTreeWidgetItem : public QTreeWidgetItem
{
public:
    explicit SecurityTreeWidgetItem(QTreeWidget *parent, AbstractItem *model);
    explicit SecurityTreeWidgetItem(SecurityTreeWidgetItem *parent, AbstractItem *model);

    AbstractItem *model;

signals:

};

#endif // SECURITYTREEWIDGETITEM_H
