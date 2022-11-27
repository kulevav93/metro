#include "metroplot.h"

MetroPlot::MetroPlot(QWidget *parent) : QWidget(parent)
{

}

void MetroPlot::addLines(QVector<std::shared_ptr<Line> > lines)
{
    this->lines = lines;
    for(std::shared_ptr<Line> line: lines){
        station_names.append(line.get()->getStationNames());
    }
    formMatrix();
}

void MetroPlot::printLines()
{
    for(auto line: lines){
      qDebug() << "Printing all stations of line " << line.get()->name << " :";
      Station *head = line.get()->head;
      while(head != nullptr){
          qDebug() << " " << head->getName() << "time to back: " << head->time_to_prev;
          if(typeid(*head) == typeid(TransferStation)){
              for(auto tr: dynamic_cast<TransferStation*>(head)->transfers){
                  qDebug() << "transfer to: " << tr.first->getName() << " for " << tr.second;
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

    //counting rows number and columns number for placing stations on the field
    int col_number = lines.size();
    int row_number = 0;

    for(auto i = 0; i < lines.size(); i++){
        auto line = lines.at(i);
        if(line.get()->stationsNumber() > row_number){
            row_number = line.get()->stationsNumber();
        }
    }

    int cell_width = 0;
    int cell_height = 0;
    if(col_number != 0 and row_number != 0){
        cell_width = width()/col_number;
        cell_height = height()/row_number;
    }

    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::FlatCap));
    for(auto i = 0; i < lines.size(); i++){
        QVector<Station*> stations = lines[i].get()->getStations();
        painter.setPen(QPen(lines[i].get()->getColor(), 2, Qt::SolidLine, Qt::FlatCap));
        for(auto j = 0; j < stations.size(); j++){
            stations[j]->setCoordinates(QPoint(i * cell_width + cell_width/2,
                                               j * cell_height + cell_height/2));
            painter.drawEllipse(stations[j]->getCoordinates(), 10, 10);
        }
    }
}

void MetroPlot::formMatrix()
{
    ///formMatrix(...)creates matrix of vertexes from Line Stations
    /// and time to neigbors and transfers

    matrix.resize(station_names.size());
    for(auto i = 0; i < matrix.size(); i++){
        matrix[i] = QVector<int>(station_names.size(), -1);
        matrix[i][i] = 0;
    }

    for(auto line: lines){
      Station *station = line.get()->head;
      while(station->next != nullptr){
          QString station_from_name = station->getName();
          int station_from_index = station_names.indexOf(station_from_name);

          QString station_to_name = station->next->getName();
          int station_to_index = station_names.indexOf(station_to_name);

          int time = station->next->time_to_prev;

          matrix[station_from_index][station_to_index] = time;
          matrix[station_to_index][station_from_index] = time;

          if(typeid(*station) == typeid(TransferStation)){
              for(auto transfer: dynamic_cast<TransferStation*>(station)->transfers){
                  station_to_name = transfer.first->getName();
                  station_to_index = station_names.indexOf(station_to_name);
                  time = transfer.second;

                  matrix[station_from_index][station_to_index] = time;
              }
          }
          station = station->next;
      }
    }
    for(int i=0; i < matrix.size(); i++){
        qDebug() << matrix[i];
    }
}

