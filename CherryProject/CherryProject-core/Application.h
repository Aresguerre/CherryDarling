#ifndef APPLICATION_H
#define APPLICATION_H

#include "cherryproject-core_global.h"
#include <QString>

class CHERRYPROJECTCORESHARED_EXPORT Application
{

public:
    explicit Application(const QString& name = "");

    int getId() const;
    void setId(int id);
    QString getName() const;
    void setName(const QString& name);

private:
    int id;
    QString name;

};

#endif // APPLICATION_H
