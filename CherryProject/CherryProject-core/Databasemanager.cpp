#include "Databasemanager.h"
#include<QSqlDatabase>

DatabaseManager& DatabaseManager::instance()
{
    static DatabaseManager singleton;
    return singleton;
}

DatabaseManager::DatabaseManager(const QString &path):
    database(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"))),
    applicationDAO(*database)
{
    database->setDatabaseName(path);
    database->open();
    applicationDAO.init();
}

DatabaseManager::~DatabaseManager()
{
    database->close();
    delete database;
}
