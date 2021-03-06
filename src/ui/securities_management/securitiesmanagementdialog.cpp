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

SecurityTreeWidgetItem* SecuritiesManagementDialog::buildSecurityTreeWidget(SecurityTreeWidgetItem *parent, AbstractItem *item)
{
    SecurityTreeWidgetItem *result = new SecurityTreeWidgetItem(parent, item);
    if (item->isCategory())
    {
        Category *category = (Category*)item;
        for (AbstractItem *child: category->children)
        {
            result->addChild(this->buildSecurityTreeWidget(result, child));
        }
    }

    return result;
}

SecurityTreeWidgetItem* SecuritiesManagementDialog::buildSecurityTreeWidget(QTreeWidget *parent, AbstractItem *item)
{
    SecurityTreeWidgetItem *result = new SecurityTreeWidgetItem(parent, item);
    if (item->isCategory())
    {
        Category *category = (Category*)item;
        for (AbstractItem *child: category->children)
        {
            result->addChild(this->buildSecurityTreeWidget(result, child));
        }
    }

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
\
    Category *currentCategory = (Category*)current->model;
    Category *newCategory = new Category(QString("(New category)"), currentCategory);
    currentCategory->addChild(newCategory);

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
    currentCategory->addChild(newSecurity);

    SecurityTreeWidgetItem* newItem = new SecurityTreeWidgetItem(current, newSecurity);
    this->ui->treeWidget->setCurrentItem(newItem);
}


void SecuritiesManagementDialog::on_btnResetItem_clicked()
{
    this->setFormProperties();
}


void SecuritiesManagementDialog::setFormProperties()
{
    SecurityTreeWidgetItem* current = (SecurityTreeWidgetItem*)this->ui->treeWidget->currentItem();
    if (nullptr == current) {
        this->ui->editName->setText("");
        this->ui->editCode->setText("");
        this->ui->editDecimalNumbers->setText("");
        return;
    }

    // Common fields for securities and categories
    this->ui->editName->setText(current->model->name);

    // Fields specific for securities
    if (current->model->isCategory()) {
        return;
    }
    Security *model = (Security*)current->model;
    this->ui->editCode->setText(model->code);
    this->ui->editDecimalNumbers->setText(QString::number(model->decimalNumbers));
}

void SecuritiesManagementDialog::on_btnSaveItem_clicked()
{
    QTreeWidgetItem* current = this->ui->treeWidget->currentItem();
    SecurityTreeWidgetItem* currentItem = (SecurityTreeWidgetItem*)current;

    if (!currentItem)
        return;
    Security *model = (Security*)currentItem->model;

    model->name = this->ui->editName->text();
    model->code = this->ui->editCode->text();
    model->decimalNumbers = this->ui->editDecimalNumbers->text().toInt();

    currentItem->setData(0, 0, model->name);
}

