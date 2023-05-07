#ifndef MAINWINDOW_H
#define MAINWINDOW_

#include <QDesktopWidget>
#include <QMainWindow>
#include <QTime>
#include <QTimer>
#include <QtMath>

//#include "mavlink.h"
#include "./ui_mainwindow.h"
#include "hendler_structs.h"
#include "pixhawk_manager.h"
#include "mapcontroller.h"
#include "horizon.h"


#define REDCOLOR 235, 200, 200
#define GREYCOLOR 184, 197, 194
#define GREENCOLOR 200, 235, 200
#define WHITECOLOR 255, 255, 255


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum param_table_conumns{
    ind,
    name,
    value,
    description
};

class MainWindow : public QMainWindow{
Q_OBJECT

private:
    Ui::MainWindow *ui;

    MapController* map_controller;
    PixhawkManager* pixhawk_manager; //sheredptr + singltone
    const QSize window_size = QDesktopWidget().size();
    const QString window_title = "FlightConfigurator";
    QTimer* info_updation_timer;
    QTimer* params_download_checking_timer;
    Aviagorizont_Viev* horizon_view;


    void set_gui_elements();
    void set_data_updation();
    bool all_parametrs_processed = 0;

    void delay(int millisecondsToWait);
    
public:
    MainWindow(QWidget *parent = nullptr);
    void show();
    void test_flight();
    void resizeEvent(QResizeEvent* event) override;
    ~MainWindow();

private slots:
    void update_widgets_geometry_slot();
    void update_params_table();
    void process_updated_param(int row, int column);
    void connect_to_pixhawk();
    void data_window_update();

    void upload_params();
    void download_params();
    void load_to_file_params();
    void load_from_file_params();
    void reset_params();
};
#endif // MAINWINDOW_H
