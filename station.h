#ifndef STATION_H
#define STATION_H

#include <QString>
#include <memory>


class Station
{
public:
    Station(QString name);
    Station(QString name, Station *prev, int time);
    QString name;

    Station* next;
    Station* prev;
    int time_to_prev;

    virtual void f(){}
};

#endif // STATION_H
