#ifndef TRANSFERSTATION_H
#define TRANSFERSTATION_H

#include "station.h"
#include <QVector>
#include <QPair>

#include<QDebug>

class TransferStation : public Station
{
public:
    TransferStation(QString name);
    TransferStation(QString name, Station *prev, int time);
    void addTransfer(const Station* station, int time);

    QVector<QPair<const Station*, int> > transfers;//keep ptrs to Stations and time to transters

};

#endif // TRANSFERSTATION_H
