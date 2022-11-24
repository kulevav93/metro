#ifndef METROMAP_H
#define METROMAP_H

#include <QMainWindow>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QTextEdit>
#include <memory>
#include <typeinfo.h>

#include <metroplot.h>
#include <line.h>

#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QByteArray>


class MetroMap : public QMainWindow
{
    Q_OBJECT

public:
    MetroMap(QWidget *parent = 0);
    ~MetroMap();
    MetroPlot *metro_plot;
    QJsonParseError json_read_errors;
public slots:
    void readJSON();

private:

    QVector<QVector<int> > matrix;
    QVector<std::shared_ptr<Line> > array_of_lines;
    QMap<QString, Station*> array_of_stations;

    void formMatrixOfVertexes();
    void createStationsFromJson(const QJsonDocument& json_doc);
    void settingTransferStations(const QJsonDocument& json_doc);
};

#endif // METROMAP_H
