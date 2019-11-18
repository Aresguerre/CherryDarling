#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "ApplicationDao.h"

#include <QString>
#include <memory>

#include "ApplicationDao.h"
#include "PictureDao.h"

class QSqlQuery;
class QSqlDatabase;

const QString DATABASE_FILENAME="cherrydarling.db";

class DatabaseManager
{
public:
    static void debugQuery(const QSqlQuery& query);
    static DatabaseManager& instance();
    ~DatabaseManager();

protected:
    DatabaseManager(const QString& path = DATABASE_FILENAME);
    DatabaseManager& operator =(const DatabaseManager& rhs);

private:
    std::unique_ptr<QSqlDatabase> database;

public:
    const ApplicationDAO applicationDAO;
    const PictureDAO pictureDAO;
};

#endif // DATABASEMANAGER_H
