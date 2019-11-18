#include "ApplicationModel.h"

ApplicationModel::ApplicationModel(QObject* parent) :
    QAbstractListModel(parent),
    dbm(DatabaseManager::instance()),
    applications(dbm.applicationDAO.getApplications())
{}

bool ApplicationModel::isIndexValid(const QModelIndex &index) const{
    if (index.row() < 0 || index.row() >= rowCount() || !index.isValid()) {
        return false;
    }
    return true;
}

int ApplicationModel::rowCount(const QModelIndex &parent) const{
    return applications->size();
}

QVariant ApplicationModel::data(const QModelIndex &index, int role) const{
    if(!isIndexValid(index)){
        return QVariant();
    }
    const Application& app = *applications->at(index.row());
    switch(role){
        case Roles::IdRole:
            return app.getId();
        case Roles::NameRole:
        case Qt::DisplayRole:
            return app.getName();
        default:
            return QVariant();
    }
}

QHash<int, QByteArray> ApplicationModel::roleNames() const{
    QHash<int, QByteArray> roles;
    roles[Roles::IdRole] = "id";
    roles[Roles::NameRole] = "name";
    return roles;
}

QModelIndex ApplicationModel::addApplication(const Application &application){
    int rowIndex = rowCount();
    beginInsertRows(QModelIndex(), rowIndex, rowIndex);
    unique_ptr<Application> newApp(new Application(application));
    dbm.applicationDAO.addApplication(*newApp);
    applications->push_back(move(newApp));
    endInsertRows();
    return index(rowIndex, 0);
}

bool ApplicationModel::setData(const QModelIndex &index, const QVariant &value, int role){
    if(!isIndexValid(index) || role!=Roles::NameRole){
        return false;
    }
    Application& app = *applications->at(index.row());
    app.setName(value.toString());
    dbm.applicationDAO.updateApplication(app);
    emit dataChanged(index, index);
    return true;

}

bool ApplicationModel::removeRows(int row, int count, const QModelIndex &parent){
    if( row<0 || row>=rowCount() || count<0 || (row+count) > rowCount() ){
        return false;
    }
    beginRemoveRows(parent, row, row+count-1);
    int countLeft = count;
    while(countLeft--){
        const Application& app = *applications->at(row+countLeft);
        dbm.applicationDAO.removeApplication(app.getId());
    }
    applications->erase(applications->begin()+row,applications->begin()+row+count);
    endRemoveRows();
    return true;
}
