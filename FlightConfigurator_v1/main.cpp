
#include "mainwindow.h"
#include "pixhawk_manager.h"
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



void test(PixhawkManager& pixhawkManager, MainWindow& w){
    mavlink_attitude_t attitude;
    mavlink_heartbeat_t heartbeat;
    mavlink_scaled_imu_t scaled_imu;
    pixhawkManager.set_msg_frequency(26, 100000);
    pixhawkManager.request_all_params();
    delay(18000);
    pixhawkManager.set_param(338, 3);
    for (;;){
        delay(100);
        attitude = pixhawkManager.get_attitude();
        heartbeat = pixhawkManager.get_heartbeat();
        scaled_imu = pixhawkManager.get_scaled_imu();

        w.updateLabel(2, qRadiansToDegrees(attitude.roll));
        w.updateLabel(3, qRadiansToDegrees(attitude.pitch));
        w.updateLabel(4, qRadiansToDegrees(attitude.yaw));

        w.updateLabel(5, scaled_imu.xacc/1000.);
        w.updateLabel(6, scaled_imu.yacc/1000.);
        w.updateLabel(7, scaled_imu.zacc/1000.);

        /*qDebug() << "pitch" << qRadiansToDegrees(attitude.pitch)
                        << "roll" << qRadiansToDegrees(attitude.roll)
                        << "yaw" << qRadiansToDegrees(attitude.yaw);
        qDebug() << "Heartbeat received, system type:" << heartbeat.type
                 << "autopilot :" << heartbeat.autopilot;
        qDebug() << "xacc:" << scaled_imu.xacc
                 << "yacc:" << scaled_imu.yacc
                 << "zacc:" << scaled_imu.zacc;
        qDebug() << "xgyro:" << scaled_imu.xgyro
                 << "ygyro:" << scaled_imu.ygyro
                 << "zgyro:" << scaled_imu.zgyro;
        qDebug() << "xmag:" << scaled_imu.xmag
                 << "ymag:" << scaled_imu.ymag
                 << "zmag:" << scaled_imu.zmag;*/
        pixhawkManager.log_received_msgs(1);
    }
}



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    PixhawkManager pixhawkManager("/dev/serial/by-id/usb-ArduPilot_Pixhawk1_36003A000551393439373637-if00", 115200);

    test(pixhawkManager, w);
    return a.exec();
}


