#include "metroplot.h"

MetroPlot::MetroPlot(QWidget *parent) : QWidget(parent)
{

}

void MetroPlot::addLine(std::shared_ptr<Line> line)
{
    lines.append(line);
}

void MetroPlot::printLines()
{
    for(auto line: lines){
      qDebug() << "Printing all stations of line " << line.get()->name << " :";
      Station *head = line.get()->head;
      while(head != nullptr){
          qDebug() << " " << head->name << "time to back: " << head->time_to_prev;
          if(typeid(*head) == typeid(TransferStation)){
              for(auto tr: dynamic_cast<TransferStation*>(head)->transfers){
                  qDebug() << "transfer to: " << tr.first->name << " for " << tr.second;
              }
          }

          head = head->next;
      }
    }

}

void MetroPlot::paintEvent(QPaintEvent *)
{
    QPainter painter(this); // Создаём объект отрисовщика
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::white, 2, Qt::SolidLine, Qt::FlatCap));
    painter.fillRect(0, 0, width(), height(), Qt::white);
}

