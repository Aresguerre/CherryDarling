#include "PictureDao.h"
#include <QSqlQuery>
#include <QVariant>


PictureDAO::PictureDAO(QSqlDatabase& database):
    database(database)
{}

void PictureDAO::init() const{
    if(!database.tables().contains("pictures")){
        QSqlQuery query(database);
        query.exec(QString("CREATE TABLE pictures")
                           + "(id INTEGER PRIMARY KEY AUTOINCREMENT,"
                           + "applicationId INTEGER,"
                           + "url TEXT)");
    }
}

void PictureDAO::addPictureToApplication(int applicationId, Picture &picture) const{
    QSqlQuery query(database);
    query.prepare(QString("INSERT INTO pictures")
                  + " (applicationId, url)"
                  + " VALUES (:applicationId, :url)");
    query.bindValue(":applicationId", applicationId);
    query.bindValue(":url", picture.getFileUrl());
    bool success=query.exec();
    picture.setId(query.lastInsertId().toInt());
    picture.setApplicationId(applicationId);
}

void PictureDAO::removePicture(int id) const{
    QSqlQuery query(database);
    query.prepare("DELETE FROM pictures WHERE id = (:id)");
    query.bindValue(":id", id);
    bool success = query.exec();
}

void PictureDAO::removePictureFromApplication(int applicationId) const{
    QSqlQuery query(database);
    query.prepare("DELETE FROM pictures WHERE applicationId = (:applicationId)");
    query.bindValue(":applicationId", applicationId);
    bool success=query.exec();
}

unique_ptr<vector<unique_ptr<<Picture> PictureDAO::getPicturesFromApplication(int applicationId) const{
    QSqlQuery query(database);
    query.prepare("SELECT * FROM pictures WHERE applicationId = (:applicationId)");
    query.bindValue(":applicationId", applicationId);
    query.exec();
    unique_ptr<vector<unique_ptr<Picture>>> list(new vector<unique_ptr<Picture>>());
    while(query.next()){
        unique_ptr<Picture> pic(new Picture());
        pic->setId(query.value("id").toInt());
        pic->setApplicationId(query.value("applicationId").toInt());
        pic->setFileUrl(query.value("url").toString());
        list->push_back(move(pic));
    }
    return list;
}
