#include "station.h"
#include <QDebug>

Station::Station(QString name)
{
    this->name = name;
    this->prev = nullptr;
    this->next = nullptr;
    time_to_prev = 0;
}

Station::Station(QString name, Station* prev, int time)
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
    prev->next = this;

    time_to_prev = time;
}

