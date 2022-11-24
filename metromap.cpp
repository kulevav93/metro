#include "metromap.h"

MetroMap::MetroMap(QWidget *parent)
    : QMainWindow(parent)
{
    QAction *quit = new QAction("&Quit", this);
    QAction *loadFile = new QAction("&Load JSON", this);

    QMenu *file;
    file = menuBar()->addMenu("&File");

    // Помещаем действие "Quit" (Выход) в меню с помощью метода addAction()
    file->addAction(loadFile);
    file->addAction(quit);
    // Когда мы выбираем в меню опцию "Quit", то приложение сразу же завершает свое выполнение
    connect(quit, &QAction::triggered, qApp, QApplication::quit);
    connect(loadFile, &QAction::triggered, this, &MetroMap::readJSON);

    metro_plot = new MetroPlot();
    setCentralWidget(metro_plot); // помещаем созданный виджет в центр виджета QMainWindow

    statusBar()->showMessage("Ready"); // показываем в нижней панели приложения сообщение "Ready"

    /*auto l = std::make_shared<Line>("first line");
    l.get()->addStation("first_1");
    qDebug() << l.get()->findStation("first_1")->name;
    metro_plot->addLine(l);
    auto l2 = std::make_shared<Line>("second line");
    metro_plot->addLine(l2);*/
}

MetroMap::~MetroMap()
{

}

void MetroMap::readJSON()
{
    QFile json_file(QFileDialog::getOpenFileName(nullptr, "JSON File", "..\\Metro", ""));

    QJsonDocument json_doc;
    if(json_file.open(QIODevice::ReadWrite|QFile::Text)){
        json_doc = QJsonDocument::fromJson(QByteArray(json_file.readAll()), &json_read_errors);
    }
    else{
        qDebug() << "Can not open json file";
    }
    json_file.close();

    if(json_read_errors.errorString().toInt() == QJsonParseError::NoError){
        createStationsFromJson(json_doc);
        settingTransferStations(json_doc);
    }
    else{
        qDebug() << json_read_errors.errorString();
    }
}


void MetroMap::formMatrixOfVertexes()
{

}

void MetroMap::createStationsFromJson(const QJsonDocument &json_doc)
{
    ///createStationsFromJson(...) creates Stations and sets relations between them,
    /// sets time to prev station, also craetes TransferStations, if Station has parameter "transfer",
    /// but does not set link to other TransferStation, it does settingTransferStations(...)
    //get all Lines in the JSON file
    QJsonArray lines = QJsonValue(json_doc.object().value("lines")).toArray();
    for(auto line = 0; line < lines.count(); line++){
        QString line_name = lines.at(line).toObject().value("name").toString();
        auto line_ptr = std::make_shared<Line>(line_name);
        array_of_lines.append(line_ptr);
        metro_plot->addLine(line_ptr);

        //get all stations in the Line from JSON
        QJsonArray stations = lines.at(line).toObject().value("stations").toArray(); // get stations of line
        for(int station = 0; station < stations.count(); station++){
            QString neighbor = "";
            neighbor = stations.at(station).toObject().value("neighbor").toString();
            QString station_name = stations.at(station).toObject().value("name").toString();

            //checks if the station_name is the a TranserStation
            bool is_transfer = stations.at(station).toObject().value("transfers").toArray().count();

            if(neighbor == ""){//station is first on the line
                if(is_transfer){
                   array_of_stations.insert(station_name, line_ptr.get()->addTransferStation(station_name));
                }
                else{
                    array_of_stations.insert(station_name, line_ptr.get()->addStation(station_name));
                }
            }
            else{//insertion staition after neighbor
                Station* neighbor_ptr = line_ptr.get()->findStation(neighbor);
                if(neighbor_ptr != nullptr){
                    int time_to_neigbor = stations.at(station).toObject().value("time_to_neighbor").toInt();

                    if(is_transfer){
                        array_of_stations.insert(station_name, line_ptr.get()->addTransferStation(station_name, neighbor_ptr, time_to_neigbor));
                    }
                    else{
                        array_of_stations.insert(station_name, line_ptr.get()->addStation(station_name, neighbor_ptr, time_to_neigbor));
                    }
                }
            }
        }
    }
}

void MetroMap::settingTransferStations(const QJsonDocument &json_doc)
{
    ///settingTransferStations(...) sets relations between TranserStations after createStationsFromJson(...)
    //get all Lines in the JSON file
    QJsonArray lines = QJsonValue(json_doc.object().value("lines")).toArray();
    for(auto line = 0; line < lines.count(); line++){
        //get all stations in the Line from JSON
        QJsonArray stations = lines.at(line).toObject().value("stations").toArray(); // get stations of line
        for(int station = 0; station < stations.count(); station++){
            //get TranserStations
            QJsonArray transfers = stations.at(station).toObject().value("transfers").toArray();
            for(int transfer = 0; transfer < transfers.count(); transfer++){
                QString transfer_to_name = transfers.at(transfer).toObject().value("transfer_to").toString();
                int time_to_transfer = transfers.at(transfer).toObject().value("time_to_transfer").toInt();
                Station* transfer_to_ptr = array_of_stations[transfer_to_name];

                QString current_station = stations.at(station).toObject().value("name").toString();
                Station* current_station_ptr = array_of_stations[current_station];
                if(transfer_to_ptr != nullptr){
                    if(typeid(*transfer_to_ptr) == typeid(TransferStation)){
                       dynamic_cast<TransferStation*>(current_station_ptr)->addTransfer(transfer_to_ptr, time_to_transfer);
                    }
                }
                else{
                    qDebug() << "Transfer to " << transfer_to_name << " can not create, because "
                             << transfer_to_name << " does not exist";
                }
            }
        }
    }metro_plot->printLines();
}
