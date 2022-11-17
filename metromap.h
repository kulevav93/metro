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


class MetroMap : public QMainWindow
{
    Q_OBJECT

public:
    MetroMap(QWidget *parent = 0);
    ~MetroMap();
};

#endif // METROMAP_H
