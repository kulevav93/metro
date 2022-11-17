#ifndef TRANSFERSTATION_H
#define TRANSFERSTATION_H

#include "station.h"
#include <QVector>

class TransferStation : public Station
{
public:
    TransferStation();
    QVector<Station*> transfers;
};

#endif // TRANSFERSTATION_H
