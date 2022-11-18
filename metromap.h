#ifndef METROMAP_H
#define METROMAP_H

#include <QMainWindow>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QTextEdit>
#include <memory>

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
    QJsonParseError json_read_errors;
public slots:
    void readJSON();
};

#endif // METROMAP_H
