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
        stations.insert(name, station);
        return station;
    }
    return nullptr;
}

Station *Line::addStation(QString name, Station *prev, int time)
{
    Station* station = new Station(name, prev, time);
    stations.insert(name, station);
    return station;
}

Station *Line::addTransferStation(QString name)
{
    if(head == nullptr){
        Station* station = new TransferStation(name);
        head = station;
        stations.insert(name, station);
        return station;
    }
    return nullptr;
}

Station *Line::addTransferStation(QString name, Station *prev, int time)
{
    Station* station = new TransferStation(name, prev, time);
    stations.insert(name, station);
    return station;
}

Station *Line::findStation(QString name)
{
    auto it = stations.find(name);
    if(it != stations.end()){
       return *it;
    }
    return nullptr;
}

