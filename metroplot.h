#ifndef METROPLOT_H
#define METROPLOT_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QVector>
#include <memory>
#include <typeinfo.h>
#include "line.h"

#include<QDebug>

class MetroPlot : public QWidget
{
    Q_OBJECT
public:
    explicit MetroPlot(QWidget *parent = 0);

    void addLines(QVector<std::shared_ptr<Line> > lines);
    void printLines();

protected:
    void paintEvent(QPaintEvent *);

private:
    /*general applointment*/
    QVector<std::shared_ptr<Line> > lines;

    /*for drawing
    int col_number; //equals number of stations
    int row_number; //equals max number of stations on a line
    */

    /*for choosing shortest way*/
    QVector<QString> station_names;
    QVector<QVector<int> > matrix;

    void formMatrix();

signals:

public slots:
};

#endif // METROPLOT_H
