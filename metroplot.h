#ifndef METROPLOT_H
#define METROPLOT_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QVector>
#include <memory>
#include "line.h"

#include<QDebug>

class MetroPlot : public QWidget
{
    Q_OBJECT
public:
    explicit MetroPlot(QWidget *parent = 0);

    void addLine(std::shared_ptr<Line> line);

protected:
    void paintEvent(QPaintEvent *);
private:
    QVector<std::shared_ptr<Line> > lines;

signals:

public slots:
};

#endif // METROPLOT_H