#ifndef MAINWINDOW_H
#define MAINWINDOW_

#include <QDesktopWidget>
#include <QMainWindow>
#include <QTime>
#include <QtMath>

//#include "mavlink.h"
#include "./ui_mainwindow.h"
#include "param_info.h"
#include "pixhawk_manager.h"
//#include "mapcontroller.h"

void delay( int millisecondsToWait );

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum param_table_conumns{
    ind,
    name,
    none,
    value,
    description
};

class MainWindow : public QMainWindow{
    Q_OBJECT
    void set_gui_elements();

public:
    MainWindow(QWidget *parent = nullptr);
    void show();
    void resizeEvent(QResizeEvent* event) override;
    ~MainWindow();

private slots:
    void update_widgets_geometry_slot();
    void update_params_table();
    void process_updated_param(int row, int column);
    void connect_to_pixhawk();

private:
    Ui::MainWindow *ui;

    //MapController* map_controller;
    PixhawkManager* pixhawk_manager;
    const QSize window_size = QDesktopWidget().size();
    const QString window_title = "FlightConfigurator";
};
#endif // MAINWINDOW_H
