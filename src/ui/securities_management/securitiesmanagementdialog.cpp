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
    SecurityTreeWidgetItem* currentItem = (SecurityTreeWidgetItem*)current;
    bool isCategorySelected = currentItem && currentItem->model->isCategory();
    bool isSecuritySelected = currentItem && !currentItem->model->isCategory();
    this->ui->btnAddCategory->setEnabled(isCategorySelected);
    this->ui->btnAddSecurity->setEnabled(isCategorySelected);
    this->ui->btnRemoveItem->setEnabled((current != nullptr) && (current != allSecuritiesItem) && !current->childCount());

    this->ui->editName->setEnabled(currentItem);
    this->ui->editCode->setEnabled(isSecuritySelected);
    this->ui->editDecimalNumbers->setEnabled(isSecuritySelected);

    this->setFormProperties();
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
    this->ui->treeWidget->setCurrentItem(newItem);
}


void SecuritiesManagementDialog::on_btnAddSecurity_clicked()
{
    SecurityTreeWidgetItem* current = (SecurityTreeWidgetItem*)this->ui->treeWidget->currentItem();
    if (!(current && current->model->isCategory()))
        return;

    Category *currentCategory = (Category*)current->model;
    Security *newSecurity = new Security(QString("(New security)"), currentCategory);

    SecurityTreeWidgetItem* newItem = new SecurityTreeWidgetItem(current, newSecurity);
    newItem->setFlags(newItem->flags() | Qt::ItemIsEditable);
    this->ui->treeWidget->setCurrentItem(newItem);
    this->ui->treeWidget->editItem(newItem);
}


void SecuritiesManagementDialog::on_btnResetItem_clicked()
{
    this->setFormProperties();
}


void SecuritiesManagementDialog::setFormProperties()
{
    QTreeWidgetItem* current = this->ui->treeWidget->currentItem();
    SecurityTreeWidgetItem* currentItem = (SecurityTreeWidgetItem*)current;

    if (!currentItem) return;

    this->ui->editName->setText(currentItem ? currentItem->model->name : "");
}

void SecuritiesManagementDialog::on_btnSaveItem_clicked()
{
    QTreeWidgetItem* current = this->ui->treeWidget->currentItem();
    SecurityTreeWidgetItem* currentItem = (SecurityTreeWidgetItem*)current;

    if (!currentItem) return;

    AbstractItem *model = currentItem->model;
    model->name = this->ui->editName->text();
    currentItem->setData(0, 0, model->name);
}

