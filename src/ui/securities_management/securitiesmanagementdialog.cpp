#include "securitiesmanagementdialog.h"
#include "ui_securitiesmanagementdialog.h"

SecuritiesManagementDialog::SecuritiesManagementDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecuritiesManagementDialog)
{
    ui->setupUi(this);

    allSecuritiesItem = new QTreeWidgetItem(this->ui->treeWidget, QStringList("All securities"));
}

SecuritiesManagementDialog::~SecuritiesManagementDialog()
{
    delete ui;
}

void SecuritiesManagementDialog::on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    bool isEnabled = current != nullptr;
    this->ui->btnAddItem->setEnabled(isEnabled);
    this->ui->btnRemoveItem->setEnabled(isEnabled & (current != allSecuritiesItem) & !current->childCount());
}


void SecuritiesManagementDialog::on_btnAddItem_clicked()
{
    QTreeWidgetItem* current = this->ui->treeWidget->currentItem();
    if (nullptr == current)
        return;

    QTreeWidgetItem* newItem = new QTreeWidgetItem(current, QStringList("(New item)"));
    newItem->setFlags(newItem->flags() | Qt::ItemIsEditable);
    this->ui->treeWidget->setCurrentItem(newItem);
    this->ui->treeWidget->editItem(newItem);

}


void SecuritiesManagementDialog::on_btnRemoveItem_clicked()
{
    QTreeWidgetItem* current = this->ui->treeWidget->currentItem();
    if (nullptr == current || allSecuritiesItem == current)
        return;

    current->parent()->removeChild(current);
}

