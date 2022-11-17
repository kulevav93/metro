#ifndef STATION_H
#define STATION_H

#include <QString>
#include <memory>


class Station
{
public:
    Station(QString name);
    Station(QString name, Station *prev);
    QString name;

    Station* next;
    Station* prev;
};

#endif // STATION_H
