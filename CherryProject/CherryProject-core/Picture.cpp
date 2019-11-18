#include "Picture.h"

Picture::Picture(const QString& filePath):
    Picture(QUrl::fromLocalFile(filePath))
{}
Picture::Picture(const QUrl &fileUrl ):
    id(-1),
    appId(-1),
    fileUrl(fileUrl)
{}

int Picture::getId(){
    return id;
}
void Picture::setId(int id){
    this->id=id;
}

int Picture::getAppId(){
    return appId;
}
void Picture::setId(int appId){
    this->appId=appId;
}

QUrl Picture::getFileUrl() const
{
    return fileUrl;
}

void Picture::setFileUrl(const QUrl& fileUrl)
{
    this->fileUrl = fileUrl;
}
