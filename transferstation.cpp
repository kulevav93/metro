#include "transferstation.h"

TransferStation::TransferStation(QString name):Station(name)
{

}

TransferStation::TransferStation(QString name, Station *prev, int time): Station(name, prev, time)
{

}

void TransferStation::addTransfer(const Station *station, int time)
{
    transfers.append(qMakePair(station, time));
}

