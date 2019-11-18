#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "ApplicationDao.h"
#include <QString>

class QSqlDatabase;

const QString DATABASE_FILENAME="cherrydarling.db";

class DatabaseManager
{
public:
    static DatabaseManager& instance();
    ~DatabaseManager();

protected:
    DatabaseManager(const QString& path = DATABASE_FILENAME);
    DatabaseManager& operator =(const DatabaseManager& rhs);

private:
    QSqlDatabase* database;

public:
    const ApplicationDAO applicationDAO;
};

#endif // DATABASEMANAGER_H
