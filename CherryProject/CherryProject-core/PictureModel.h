#ifndef PICTUREMODEL_H
#define PICTUREMODEL_H

#include <memory>
#include <vector>
#include <QAbstractListModel>

#include "cherryproject-core_global.h"
#include "Picture.h"

#include "Application.h"
#include "Databasemanager.h"
#include "ApplicationModel.h"

using namespace std;
class CHERRYPROJECTCORESHARED_EXPORT PictureModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles{
        UrlRole = Qt::UserRole+1,
        FilePathRole
    };
    PictureModel(const ApplicationModel& applicationModel, QObject* parent=0);

    QModelIndex addPicture(const Picture& picture);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    bool removeRows(int row, int count, const QModelIndex& parent) override;
    QHash<int, QByteArray> roleNames() const override;

    void setApplicationId(int applicationId);
    void clearApplication();

public slots:
    void deletePictureFromApplication();

private:
    void loadPictures(int applicationId);
    bool isIndexValid(const QModelIndex& index) const;

    DatabaseManager& dbm;
    int applicationId;
    unique_ptr<vector<unique_ptr<Picture>>> pictures;
};

#endif // PICTUREMODEL_H
