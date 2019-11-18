#ifndef APPLICATIONMODAL_H
#define APPLICATIONMODAL_H

#include <QAbstractListModel>
#include <QHash>
#include <vector>
#include <memory>

#include "cherryproject-core_global.h"
#include "Application.h"
#include "Databasemanager.h"

using namespace std;

class CHERRYPROJECTCORESHARED_EXPORT ApplicationModel : public QAbstractListModel
{
public:
    Q_OBJECT
    enum Roles{
        IdRole = Qt::UserRole+1,
        NameRole,
    };

    ApplicationModel(QObject* parent = 0);
    QModelIndex addApplication(const Application& application);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role) override;
    bool removeRows(int row, int count, const QModelIndex& parent) override;
    QHash<int, QByteArray> roleNames() const override;

private:
    bool isIndexValid(const QModelIndex& index) const;

    DatabaseManager& dbm;
    unique_ptr<vector<unique_ptr<Application>>> applications;
};

#endif // APPLICATIONMODAL_H
