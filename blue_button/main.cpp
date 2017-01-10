#include "mainwindow.h"
#include "formabout.h"
#include "connector.h"
#include "controller.h"
#include "libloader.h"
#include "adds.h"
#include <windows.h>
#include <QApplication>

boolean debug = false; //триггер для отладки программы без контроллера (true - без контроллера)
QString version="2.0.0";
Connector connector;
Controller controller;
LibLoader libLoader;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();

    return a.exec();
}
