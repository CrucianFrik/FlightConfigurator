#include <QApplication>
#include <QCoreApplication>
#include <QTime>
#include <QtMath>

#include "mainwindow.h"
#include "binder.h"



void delay( int millisecondsToWait )
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}


void test(Binder& binder, MainWindow& w){
    mavlink_attitude_t attitude;
    mavlink_heartbeat_t heartbeat;
    for (;;){
        delay(500);
        attitude = binder.getAttitude();
        heartbeat = binder.getHeartbeat();
        w.updateLabel(2, qRadiansToDegrees(attitude.pitch));
        w.updateLabel(3, qRadiansToDegrees(attitude.roll));
        w.updateLabel(4, qRadiansToDegrees(attitude.yaw));
        qDebug() << "pitch" << qRadiansToDegrees(attitude.pitch)
                        << "roll" << qRadiansToDegrees(attitude.roll)
                        << "yaw" << qRadiansToDegrees(attitude.yaw);
        qDebug() << "Heartbeat received, system type:" << heartbeat.type
                 << "autopilot :" << heartbeat.autopilot;
    }
}



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QList< QPair<QString, QString> > map_layers_paths = {{"../../maps/kx-world-land-areas-110-million-SHP/world-land-areas-110-million.shp", "land"},
                                                         {"../../maps/kx-world-bathymetry-110-million-SHP/world-bathymetry-110-million.shp", "bath"}};


    MainWindow main_window(map_layers_paths);
    main_window.show();

    Binder binder("/dev/serial/by-id/usb-3D_Robotics_PX4_FMU_v2.x_0-if00", 115200);

//    test(binder, main_window);
    return a.exec();
}


