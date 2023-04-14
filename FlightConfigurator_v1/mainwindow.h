#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <cmath>
#include <QMainWindow>
#include <QPair>
#include <QTime>
#include <QtMath>

#include <qgsrasterlayer.h>

#include "mavlink.h"
#include "mapwidget.h"
#include "./ui_mainwindow.h"

//void delay( int millisecondsToWait );

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow{
Q_OBJECT

public:
    MainWindow(const QList< QPair<QString, QString> >& layers_paths, QWidget *parent = nullptr);

    void show();

//    void test(){
//        double r=10;
//        for (double fi=0;; fi+=0.001){
//            delay(50);
//            mapw_data->update_drone_pos({55+r*cos(fi), 37+r*sin(fi)});
//        }
//    }

    void resizeEvent(QResizeEvent* event);

    ~MainWindow();

public slots:
    void updateLabel(int lcd_num, double number);

private slots:
    void update_widgets_geometry();

private:
    Ui::MainWindow *ui;

    MapWidget* mapw_data;
    MapWidget* mapw_plan;

    const QSize window_size = {1100, 600};
    const QString window_title = "FlightConfigurator";
};



#endif // MAINWINDOW_H
