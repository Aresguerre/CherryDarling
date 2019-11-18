#include "Picture.h"

Picture::Picture(const QString& filePath):
    Picture(QUrl::fromLocalFile(filePath))
{}
Picture::Picture(const QUrl &fileUrl ):
    id(-1),
    applicationId(-1),
    fileUrl(fileUrl)
{}

int Picture::getId() const {
    return id;
}
void Picture::setId(int id){
    this->id=id;
}

int Picture::getApplicationId() const{
    return applicationId;
}
void Picture::setApplicationId(int applicationId){
    this->applicationId=applicationId;
}

QUrl Picture::getFileUrl() const
{
    return fileUrl;
}

void Picture::setFileUrl(const QUrl& fileUrl)
{
    this->fileUrl = fileUrl;
}
