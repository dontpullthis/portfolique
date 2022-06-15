#include "db.h"

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
        if (-1 == current->id)
        {
            query.prepare("INSERT INTO securities(name, category_id) VALUES(:name, :category_id)");
            isInsertOperation = true;

        }
        else
        {
            query.prepare("UPDATE securites SET name = :name, category_id = :category_id WHERE id = :id");
            query.bindValue(":id", QVariant(current->id));
        }
        query.bindValue(":category_id", QVariant(parent->id));

    }
    query.bindValue(":name", QVariant(current->name));
    query.exec();

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
        messageBox.critical(0,"Error", QString("Can't open a database \"" + fileName + "\". Error: " + db.lastError().text()));

    }

    QSqlQuery query("CREATE TABLE IF NOT EXISTS securities(id INTEGER PRIMARY KEY, name TEXT NOT NULL, category_id INTEGER NOT NULL)");
    query = QSqlQuery("CREATE TABLE IF NOT EXISTS security_categories(id INTEGER PRIMARY KEY, name TEXT NOT NULL, parent_id INTEGER)");
}


void Db::saveProject(Project *project)
{
    saveProjectCategory(nullptr, &project->rootSecurityCategory);
}

