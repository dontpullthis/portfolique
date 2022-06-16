#ifndef DB_H
#define DB_H

#include <QMessageBox>


#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include <QList>
#include <QMap>
#include <QMapIterator>
#include <QVariant>

#include "src/project/project.h"
#include "src/project/securities/category.h"
#include "src/project/securities/security.h"

class Db
{
public:
    Db(QString fileName);

    void saveProject(Project *project);
    Project loadProject();
private:
    QSqlDatabase db;
};

#endif // DB_H
