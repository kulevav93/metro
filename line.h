#ifndef LINE_H
#define LINE_H

#include <QString>
#include <QMap>
#include <memory>
#include "station.h"

class Line
{
public:
    Line(QString name);
    ~Line();

    QString name;
    Station* head;

    Station* addStation(QString name);
    Station* addStation(QString name, Station* prev);

    Station* findStation(QString name);

protected:
    QMap<QString, Station *> stations;
};

#endif // LINE_H
