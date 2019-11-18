#include "Application.h"


Application::Application(const QString& name):id(id), name(name){

}

int Application::getId()const{
    return id;
}
void Application::setId(int id){
    this->id=id;
}

QString Application::getName()const{
    return name;
}
void Application::setName(const QString &name){
    this->name=name;
}
