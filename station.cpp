#include "station.h"
#include <QDebug>

Station::Station(QString name)
{
    this->name = name;
    this->prev = nullptr;
    this->next = nullptr;
}

Station::Station(QString name, Station* prev)
{
    this->name = name;
    if(prev->next != nullptr){
        this->next = prev->next;
        this->next->prev = this;
    }
    else{
        this->next = nullptr;
    }
    this->prev = prev;
    prev->next = this; qDebug() << "end";
}

