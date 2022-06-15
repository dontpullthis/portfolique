#ifndef DB_H
#define DB_H

#include <QMessageBox>


#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include <QVariant>

#include "src/project/project.h"
#include "src/project/securities/category.h"
#include "src/project/securities/security.h"

class Db
{
public:
    Db(QString fileName);

    void saveProject(Project *project);
private:
    QSqlDatabase db;
};

#endif // DB_H
