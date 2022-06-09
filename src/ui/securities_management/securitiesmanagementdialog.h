#ifndef SECURITIESMANAGEMENTDIALOG_H
#define SECURITIESMANAGEMENTDIALOG_H

#include <QDialog>
#include <QTreeWidget>

#include "src/project/securities/category.h"
#include "src/project/securities/security.h"
#include "securitytreewidgetitem.h"

namespace Ui {
class SecuritiesManagementDialog;
}

class SecuritiesManagementDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SecuritiesManagementDialog(Category *rootCategory, QWidget *parent = nullptr);
    ~SecuritiesManagementDialog();

private slots:
    void on_treeWidget_currentItemChanged(QTreeWidgetItem *current);

    void on_btnRemoveItem_clicked();

    void on_btnAddCategory_clicked();

    void on_btnAddSecurity_clicked();

private:
    Ui::SecuritiesManagementDialog *ui;

    QTreeWidgetItem *allSecuritiesItem;

    Category *rootSecurityCategory;

    SecurityTreeWidgetItem* buildSecurityTreeWidget(QTreeWidget *parent, AbstractItem *item = nullptr);
};

#endif // SECURITIESMANAGEMENTDIALOG_H
