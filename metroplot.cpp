#include "metroplot.h"

MetroPlot::MetroPlot(QWidget *parent) : QWidget(parent)
{

}

void MetroPlot::addLine(std::shared_ptr<Line> line)
{
    lines.append(line);
    for(auto l: lines){
        qDebug() << l.get()->name;
    }
}

void MetroPlot::paintEvent(QPaintEvent *)
{
    QPainter painter(this); // Создаём объект отрисовщика
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::white, 2, Qt::SolidLine, Qt::FlatCap));
    painter.fillRect(0, 0, width(), height(), Qt::white);
}

