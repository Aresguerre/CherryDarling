#ifndef PICTUREDAO_H
#define PICTUREDAO_H

#include <vector>
#include <memory>

using namespace std;

class QSqlDatabase;
class Picture;

class PictureDAO
{
public:
    explicit PictureDAO(QSqlDatabase& database);
    void init() const;

    void addPictureToApplication(int applicationId, Picture& picture) const;
    void removePicture(int id) const;
    void removePictureFromApplication(int applicationId) const;
    unique_ptr<vector<unique_ptr<Picture>>> getPicturesFromApplication(int applicationId) const;

private:
    QSqlDatabase& database;
};

#endif // PICTUREDAO_H
