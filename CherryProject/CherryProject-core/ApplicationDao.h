#ifndef APPLICATIONDAO_H
#define APPLICATIONDAO_H

#include <vector>
#include <memory>

using namespace std;

class QSqlDatabase;
class Application;

class ApplicationDAO
{
public:
    ApplicationDAO(QSqlDatabase& database);
    void init() const;
    void addApplication(Application& application) const; //C
    unique_ptr<vector<unique_ptr<Application>>> getApplications() const; //R
    void updateApplication(const Application& application) const; //U
    void removeApplication(int id) const; //D


private:
    QSqlDatabase& database;
};

#endif // APPLICATIONDAO_H
