#include "line.h"
#include <QDebug>

Line::Line(QString name)
{
    head = nullptr;
    this->name = name;
}

Line::~Line()
{
    Station* station = head;
    if(station != nullptr){
        while(station->next != nullptr){
            station = station->next;
            delete station->prev;
        }
        delete station;
    }
}

Station *Line::addStation(QString name)
{
    if(head == nullptr){
        Station* station = new Station(name);
        head = station;
        return station;
    }
    return nullptr;

}

Station *Line::addStation(QString name, Station *prev)
{
    return new Station(name, prev);
}

