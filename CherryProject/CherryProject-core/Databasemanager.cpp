#include "Databasemanager.h"

#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

void DatabaseManager::debugQuery(const QSqlQuery& query)
{
    if (query.lastError().type() == QSqlError::ErrorType::NoError) {
        qDebug() << "Query OK:"  << query.lastQuery();
    } else {
       qWarning() << "Query KO:" << query.lastError().text();
       qWarning() << "Query text:" << query.lastQuery();
    }
}


DatabaseManager& DatabaseManager::instance()
{
    static DatabaseManager singleton;
    return singleton;
}

DatabaseManager::DatabaseManager(const QString &path):
    database(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"))),
    applicationDAO(*database),
    pictureDAO(*database)
{
    database->setDatabaseName(path);
    database->open();
    applicationDAO.init();
    pictureDAO.init();
}

DatabaseManager::~DatabaseManager()
{
    database->close();
}
