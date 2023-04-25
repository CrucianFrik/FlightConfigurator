#ifndef MAINWINDOW_H
#define MAINWINDOW_H



#include <QMainWindow>
#include <QTime>
#include <QtMath>

#include "mavlink.h"
#include "./ui_mainwindow.h"
#include "mapcontroller.h"

void delay( int millisecondsToWait );

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow{
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    void show();

    void test(){
        double r=10;
        for (double fi=0;; fi+=0.001){
            delay(50);
            map_controller->update_drone_pos({55+r*cos(fi), 37+r*sin(fi)}, fi);
        }
    }

    void resizeEvent(QResizeEvent* event) override;

    void update_label(int lcd_num, double number);

    ~MainWindow();

private slots:
    void update_widgets_geometry_slot();

private:
    Ui::MainWindow *ui;

    MapController* map_controller;


    const QSize window_size = {1100, 600};
    const QString window_title = "FlightConfigurator";
};



#endif // MAINWINDOW_H
