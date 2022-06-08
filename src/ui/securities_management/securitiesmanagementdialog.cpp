#include "securitiesmanagementdialog.h"
#include "ui_securitiesmanagementdialog.h"

SecuritiesManagementDialog::SecuritiesManagementDialog(Category *rootCategory, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecuritiesManagementDialog),
    rootSecurityCategory(rootCategory)
{
    ui->setupUi(this);

    allSecuritiesItem = buildSecurityTreeWidget(this->ui->treeWidget, rootCategory);
}

SecuritiesManagementDialog::~SecuritiesManagementDialog()
{
    delete ui;
}


SecurityTreeWidgetItem* SecuritiesManagementDialog::buildSecurityTreeWidget(QTreeWidget *parent, AbstractItem *item)
{
    SecurityTreeWidgetItem *result = new SecurityTreeWidgetItem(parent, item);

    return result;
}


void SecuritiesManagementDialog::on_treeWidget_currentItemChanged(QTreeWidgetItem *current)
{
    bool isEnabled = current != nullptr;
    this->ui->btnAddCategory->setEnabled(isEnabled);
    this->ui->btnAddSecurity->setEnabled(isEnabled);
    this->ui->btnRemoveItem->setEnabled(isEnabled & (current != allSecuritiesItem) & !current->childCount());
}


void SecuritiesManagementDialog::on_btnRemoveItem_clicked()
{
    QTreeWidgetItem* current = this->ui->treeWidget->currentItem();
    if (nullptr == current || allSecuritiesItem == current)
        return;

    current->parent()->removeChild(current);
}

void SecuritiesManagementDialog::on_btnAddCategory_clicked()
{
    SecurityTreeWidgetItem* current = (SecurityTreeWidgetItem*)this->ui->treeWidget->currentItem();
    if (!(current && current->model->isCategory()))
        return;

    Category *currentCategory = (Category*)current->model;
    Category *newCategory = new Category(QString("(New category)"), currentCategory);

    SecurityTreeWidgetItem* newItem = new SecurityTreeWidgetItem(current, newCategory);
    newItem->setFlags(newItem->flags() | Qt::ItemIsEditable);
    this->ui->treeWidget->setCurrentItem(newItem);
    this->ui->treeWidget->editItem(newItem);

}

