#include "metromap.h"

MetroMap::MetroMap(QWidget *parent)
    : QMainWindow(parent)
{
    QAction *quit = new QAction("&Quit", this);
    // Создаем объект класса QMenu (меню)
    QMenu *file;
    file = menuBar()->addMenu("&File");

    // Помещаем действие "Quit" (Выход) в меню с помощью метода addAction()
    file->addAction(quit);
    // Когда мы выбираем в меню опцию "Quit", то приложение сразу же завершает свое выполнение
    connect(quit, &QAction::triggered, qApp, QApplication::quit);

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
