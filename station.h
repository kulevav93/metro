#ifndef STATION_H
#define STATION_H

#include <QString>
#include <QPoint>
#include <QColor>
#include <memory>


class Station
{
public:
    Station(QString name);
    Station(QString name, Station *prev, int time);
    void setCoordinates(const QPoint& coord){coordinates = coord;}
    QPoint getCoordinates(){return coordinates;}
    QString getName() const {return name;}

    Station* next;
    Station* prev;
    int time_to_prev;

    virtual void f(){}
private:
    QString name;
    QPoint coordinates;
};

#endif // STATION_H
