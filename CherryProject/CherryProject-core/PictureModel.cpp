#include "PictureModel.h"

PictureModel::PictureModel(const ApplicationModel &applicationModel, QObject *parent):
    QAbstractListModel(parent),
    dbm(DatabaseManager::instance()),
    applicationId(-1),
    pictures(new vector<unique_ptr<Picture>>())
{
    connect(&applicationModel, &ApplicationModel::rowsRemoved,this,&PictureModel::deletePictureFromApplication);
}

QModelIndex PictureModel::addPicture(const Picture& picture){
    int rows =rowCount();
    beginInsertRows(QModelIndex(), rows,rows);
    unique_ptr<Picture> newPic(new Picture(picture));
    dbm.pictureDAO.addPictureToApplication(applicationId, *newPic);
    endInsertRows();
    return index(rows,0);
}

int PictureModel::rowCount(const QModelIndex& parent ) const {
    return pictures->size();
}

QVariant PictureModel::data(const QModelIndex& index, int role) const {
    if(!isIndexValid(index)){
        return QVariant();
    }

    const Picture& picture = *pictures->at(index.row());
    switch (role) {
    case Qt::DisplayPropertyRole:
        return picture.getFileUrl().fileName();
        break;
    case Roles::UrlRole:
        return picture.getFileUrl();
        break;
    case Roles::FilePathRole:
        return picture.getFileUrl().toLocalFile();
        break;
    default:
        return QVariant();
    }
}
bool PictureModel::removeRows(int row, int count, const QModelIndex& parent) {
    if( row<0 || row>rowCount() || count<0 || row+count>rowCount() ){
        return false;
    }

    beginRemoveRows(parent, row, row+count-1);
    int countLeft = count;
    while(countLeft--){
        const Picture& picture = *pictures->at(row+countLeft);
        dbm.pictureDAO.removePicture(picture.getId());
    }
    pictures->erase(pictures->begin()+row, pictures->begin()+row+count);
    endRemoveRows();
    return true;
}

QHash<int, QByteArray> PictureModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[Roles::FilePathRole] = "filepath";
    return roles;
}

void PictureModel::setApplicationId(int applicationId){
    beginResetModel();
    this->applicationId=applicationId;
    loadPictures(applicationId);
    endResetModel();
}
void PictureModel::clearApplication(){
    setApplicationId(-1);
}

void PictureModel::deletePictureFromApplication(){
    dbm.pictureDAO.removePictureFromApplication(applicationId);
    clearApplication();
}

void PictureModel::loadPictures(int applicationId){
    if(applicationId<=0){
        pictures.reset(new vector<unique_ptr<Picture>>());
        return;
    }
    pictures = dbm.pictureDAO.getPicturesFromApplication(applicationId);
}
bool PictureModel::isIndexValid(const QModelIndex& index) const{
    if(index.row()<0 || index.row()>=rowCount() || !index.isValid()){
        return false;
    }
    return true;
}
