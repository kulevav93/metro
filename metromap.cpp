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

    MetroPlot *metro_plot = new MetroPlot();
    setCentralWidget(metro_plot); // помещаем созданный виджет в центр виджета QMainWindow

    statusBar()->showMessage("Ready"); // показываем в нижней панели приложения сообщение "Ready"

    auto l = std::make_shared<Line>("first line");
    metro_plot->addLine(l);
    auto l2 = std::make_shared<Line>("second line");
    metro_plot->addLine(l2);
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
        QJsonArray lines = QJsonValue(json_doc.object().value("lines")).toArray();
        for(auto line = 0; line < lines.count(); line++){
            qDebug() << "creating new Line:" << lines.at(line).toObject().value("name").toString();
            QJsonArray stations = lines.at(line).toObject().value("stations").toArray(); // get stations of line
            for(int station = 0; station < stations.count(); station++){
                QString neighbor = "";
                neighbor = stations.at(station).toObject().value("neighbor").toString();
                if(neighbor == ""){//station is first on the line
                    qDebug() << "creating station: " << stations.at(station).toObject().value("name").toString();
                }
                else{
                    qDebug() << "creating station: " << stations.at(station).toObject().value("name").toString()
                             << " after station: " << neighbor;
                }
            }
        }
    }
    else{
        qDebug() << json_read_errors.errorString();
    }
}
