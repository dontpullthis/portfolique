#ifndef PROJECT_H
#define PROJECT_H

#include <QList>

#include "securities/category.h"

class Project
{
public:
    Project();

    Category rootSecurityCategory;
};

#endif // PROJECT_H
