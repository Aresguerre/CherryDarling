#include "ApplicationModel.h"

ApplicationModel::ApplicationModel() :
    QAbstractListModel(parent),
    dbm(DatabaseManager::instance()),
    applications(dbm.applicationDAO.getApplications())
{}

int ApplicationModel::rowCount(const QModelIndex &parent) const{
    return applications->size();
}
