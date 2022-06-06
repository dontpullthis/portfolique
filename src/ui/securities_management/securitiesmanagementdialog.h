#ifndef SECURITIESMANAGEMENTDIALOG_H
#define SECURITIESMANAGEMENTDIALOG_H

#include <QDialog>
#include <QTreeWidget>

namespace Ui {
class SecuritiesManagementDialog;
}

class SecuritiesManagementDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SecuritiesManagementDialog(QWidget *parent = nullptr);
    ~SecuritiesManagementDialog();

private slots:
    void on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    void on_btnAddItem_clicked();

    void on_btnRemoveItem_clicked();

private:
    Ui::SecuritiesManagementDialog *ui;

    QTreeWidgetItem *allSecuritiesItem;
};

#endif // SECURITIESMANAGEMENTDIALOG_H
