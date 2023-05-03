#include <QApplication>
#include <QCoreApplication>
#include <QTime>
#include <QtMath>

#include <vector>
#include  <utility>

#include "mainwindow.h"
#include "pixhawk_manager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow window;
    window.show();
    return a.exec();
}


