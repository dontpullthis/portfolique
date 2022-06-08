#include "securitytreewidgetitem.h"

SecurityTreeWidgetItem::SecurityTreeWidgetItem(QTreeWidget *parent, AbstractItem *model)
    : QTreeWidgetItem(parent, QStringList(model->name)),
    model(model)
{

}

SecurityTreeWidgetItem::SecurityTreeWidgetItem(SecurityTreeWidgetItem *parent, AbstractItem *model)
    : QTreeWidgetItem(parent, QStringList(model->name)),
    model(model)
{

}
