#ifndef MAINWINDOW_H
#define MAINWINDOW_


#include <QDesktopWidget>
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

    void test_flight();

    void resizeEvent(QResizeEvent* event) override;

    void update_label(int lcd_num, double number);

    ~MainWindow();

private slots:
    void update_widgets_geometry_slot();

private:
    Ui::MainWindow *ui;

    MapController* map_controller;


    const QSize window_size = QDesktopWidget().size();
    const QString window_title = "FlightConfigurator";
};
#endif // MAINWINDOW_H
