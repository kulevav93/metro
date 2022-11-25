#ifndef LINE_H
#define LINE_H

#include <QString>
#include <QMap>
#include <memory>
#include "station.h"
#include "transferstation.h"

class Line
{
public:
    Line(QString name);
    ~Line();

    QString name;
    Station* head;

    Station* addStation(QString name);
    Station* addStation(QString name, Station* prev, int time);
    Station* addTransferStation(QString name);
    Station* addTransferStation(QString name, Station* prev, int time);

    Station* findStation(QString name);
    int stationsNumber() {return stations.size();}
    QVector<Station*> getStations(){return stations.values().toVector();}

protected:
    QMap<QString, Station *> stations;
};

#endif // LINE_H
