#ifndef PICTURE_H
#define PICTURE_H

#include "cherryproject-core_global.h"
#include <QString>
#include <QUrl>

class CHERRYPROJECTCORESHARED_EXPORT Picture
{
public:
    Picture(const QString& filePath = "");
    Picture(const QUrl& fileUrl);

    int getId() const;
    void setId(int id);

    int getApplicationId() const;
    void setApplicationId(int applicationId);

    QUrl getFileUrl() const;
    void setFileUrl(const QUrl& fileUrl);

private:
    int id;
    int applicationId;
    QUrl fileUrl;

};

#endif // PICTURE_H
