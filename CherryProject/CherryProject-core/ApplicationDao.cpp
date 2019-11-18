#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>

#include "ApplicationDao.h"


ApplicationDAO::ApplicationDAO(QSqlDatabase& database):
    database(database)
{}

void ApplicationDAO::init() const
{
    if(!database.tables().contains("applications")){
        QSqlQuery query(database);
        bool success=query.exec("CREATE TABLE applications "
                                "(id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT)");
    }
}

void ApplicationDAO::addApplication(Application& application) const{
    QSqlQuery query(database);
    query.prepare("INSERT INTO applications (name) VALUES (:name)");
    query.bindValue(":name", application.getName());
    bool success=query.exec();
    application.setId(query.lastInsertId().toInt());
}

unique_ptr<vector<unique_ptr<Application>>> ApplicationDAO::getApplications() const{
    QSqlQuery query("SELECT * FROM applications", database);
    query.exec();
    unique_ptr<vector<unique_ptr<Application>>> list(new vector<unique_ptr<Application>>());
    while (query.next()) {
        Application* app=new Application();
        app->setId(query.value("id").toInt());
        app->setName(query.value("name").toString());
        list->push_back(move(app));
    }
    return list;
}

void ApplicationDAO::updateApplication(const Application &application) const{
    QSqlQuery query(database);
    query.prepare("UPDATE applications SET name = (:name) WHERE id = (:id)");
    query.bindValue(":name", application.getName());
    query.bindValue(":id", application.getId());
    bool success=query.exec();
}

void ApplicationDAO::removeApplication(int id) const{
    QSqlQuery query(database);
    query.prepare("DELETE FROM applications WHERE id = (:id)");
    query.bindValue(":id", id);
    bool success=query.exec();
}
