#include "mainwindow.h"
#include "binder.h"
#include <QApplication>
#include <QCoreApplication>
#include <QTime>
#include <QtMath>

void delay( int millisecondsToWait )
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}

void test(Binder& binder){
    mavlink_attitude_t attitude;
    mavlink_heartbeat_t heartbeat;
    for (int i = 0; i < 10; i++){
        delay(500);
        attitude = binder.getAttitude();
        heartbeat = binder.getHeartbeat();
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
    MainWindow w;
    w.show();
    Binder binder("/dev/serial/by-id/usb-3D_Robotics_PX4_FMU_v2.x_0-if00", 115200);
    test(binder);
    return a.exec();
}


