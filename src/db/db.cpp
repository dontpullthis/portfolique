#include "db.h"
#include <QDebug>
void saveProjectCategory(AbstractItem *parent, AbstractItem *current)
{
    // Process ittem
    QSqlQuery query;
    bool isInsertOperation = false;
    if (current->isCategory())
    {
        if (-1 == current->id)
        {
            query.prepare("INSERT INTO security_categories(name, parent_id) VALUES(:name, :parent_id)");
            isInsertOperation = true;
        }
        else
        {
            query.prepare("UPDATE security_categories SET name = :name, parent_id = :parent_id WHERE id = :id");
            query.bindValue(":id", QVariant(current->id));

        }
        query.bindValue(":parent_id", parent ? QVariant(parent->id) : QVariant::fromValue(nullptr));
    }
    else
    {
        Security *security = (Security*)current;
        if (-1 == current->id)
        {
            query.prepare("INSERT INTO securities(name, category_id, code, decimal_numbers) VALUES(:name, :category_id, :code, :decimal_numbers)");
            isInsertOperation = true;

        }
        else
        {
            query.prepare("UPDATE securities SET name = :name, category_id = :category_id, code = :code, decimal_numbers = :decimal_numbers WHERE id = :id");
            query.bindValue(":id", QVariant(security->id));
        }
        query.bindValue(":category_id", QVariant(parent->id));
        query.bindValue(":code", QVariant(security->code));
        query.bindValue(":decimal_numbers", QVariant(security->decimalNumbers));

    }
    query.bindValue(":name", QVariant(current->name));
    bool test = query.exec();
    qDebug() << "STATUS: " << test;


    // Process children
    if (isInsertOperation)
        current->id = query.lastInsertId().toInt();
    if (current->isCategory())
    {
        Category *cat = (Category*)current;
        for (AbstractItem *child: cat->children) {
            saveProjectCategory(cat, (Category*)child);
        }
    }

}


Db::Db(QString fileName)
{
    const QString DRIVER("QSQLITE");
    if(!QSqlDatabase::isDriverAvailable(DRIVER)) // TODO: check on app startup in order to let user know about the problem ASAP
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error", "SQLite driver is not available.");
        exit(-1);
    }
    db = QSqlDatabase::addDatabase(DRIVER);
    db.setDatabaseName(fileName);

    if(!db.open())
    {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", QString("Can't open a database \"" + fileName + "\". Error: " + db.lastError().text()));
    }

    QSqlQuery query("CREATE TABLE IF NOT EXISTS securities(id INTEGER PRIMARY KEY, name TEXT NOT NULL, category_id INTEGER NOT NULL, code TEXT NOT NULL, decimal_numbers INTEGER NOT NULL)");
    query = QSqlQuery("CREATE TABLE IF NOT EXISTS security_categories(id INTEGER PRIMARY KEY, name TEXT NOT NULL, parent_id INTEGER)");
}


void Db::saveProject(Project *project)
{
    saveProjectCategory(nullptr, &project->rootSecurityCategory);
}

Project Db::loadProject()
{
    Project project;
    QSqlQuery query;
    query.prepare("SELECT id, name, parent_id FROM security_categories;");
    if(!query.exec())
    {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", QString("Cannot get secuirity categories from the project. Error: " + query.lastError().text()));
        return project;
    }
    QMap<int, Category*> categoriesMap;
    QMap<int, QList<int>> childrenMap;
    Category *rootCategory = nullptr;
    while (query.next())
    {
        Category *category = new Category();
        category->id = query.value(0).toInt();
        category->name = query.value(1).toString();
        int parentId = query.value(2).toInt();

        categoriesMap[category->id] = category;
        if (0 == parentId)
        {
            rootCategory = category;
        }
        if (!childrenMap.contains(parentId))
        {
            childrenMap[parentId] = QList<int>();
        }
        childrenMap[parentId].append(category->id);

    }

    QMapIterator<int, QList<int>> it(childrenMap);
    while (it.hasNext())
    {
        it.next();
        int parentId = it.key();
        if (0 == parentId)
            continue;
        Category *parent = categoriesMap[parentId];
        for (int childId: it.value())
        {
            Category *child = categoriesMap[childId];
            parent->addChild(child);
        }
    }

    query.prepare("SELECT id, name, category_id, code, decimal_numbers FROM securities");
    if(!query.exec())
    {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", QString("Cannot get secuirities from the project. Error: " + query.lastError().text()));
        return project;
    }
    while (query.next())
    {
        Security *security = new Security();
        security->id = query.value(0).toInt();
        security->name = query.value(1).toString();
        int categoryId = query.value(2).toInt();
        security->code = query.value(3).toString();
        security->decimalNumbers = query.value(4).toInt();

        Category *category = categoriesMap[categoryId];
        category->addChild(security);
    }

    project.rootSecurityCategory = *rootCategory;

    return project;
}
