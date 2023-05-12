#ifndef MAINWINDOW_H
#define MAINWINDOW_

#include <QDesktopWidget>
#include <QMainWindow>
#include <QTime>
#include <QTimer>
#include <QFileDialog>
#include <QtMath>
#include <QMessageBox>


#include "./ui_mainwindow.h"
#include "hendler_structs.h"
#include "pixhawk_manager.h"
#include "mapcontroller.h"
#include "horizon.h"

#define REDCOLOR 245, 200, 200
#define GREYCOLOR 184, 197, 194
#define GREENCOLOR 200, 235, 200
#define WHITECOLOR 255, 255, 255
#define BLUECOLOR 180, 200, 235
#define LIGHTGREYCOLOR 235, 235, 235


#define PARAM_DESC_PATH "../../config/params_description.csv"
#define FULL_PARAM_PATH "../../config/FullParametrList.txt"
#define MISSION_FILE "../../config/Mission.flyplan"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum param_table_conumns{
    ind,
    name,
    value,
    acc_value,
    description
};

class MainWindow : public QMainWindow{
Q_OBJECT

private:
    Ui::MainWindow *ui;
    MapController* map_controller;
    PixhawkManager* pixhawk_manager;
    const QSize window_size = QDesktopWidget().size();
    const QString window_title = "FlightConfigurator";
    QTimer* info_updation_timer;
    QTimer* params_download_checking_timer;
    Aviagorizont_Viev* horizon_view;

    void set_gui_elements();
    void set_data_updation();
    void reset();
    bool all_parametrs_processed = 0;

    void delay(int millisecondsToWait);
    
    const QList<double> points_table_col_proportions = {0.3, 0.3, 0.15, 0.1};
    void resize_points_table();

public:
    MainWindow(QWidget *parent = nullptr);
    void show();
    void test_flight();
    void resizeEvent(QResizeEvent* event) override;
    ~MainWindow();

private slots:
    void update_widgets_geometry_slot();
    void update_params_table();
    void make_params_table();
    void process_updated_param(int row, int column, bool set_only_red);
    void process_updated_param_slot(int row, int column);
    void connect_to_pixhawk();
    void data_window_update();

    void upload_params();
    void download_params();
    void load_to_file_params();
    void load_from_file_params();
    void load_plan_from_file();
    void load_plan_to_file();
    void upload_plan();
    void reset_params();
};
#endif // MAINWINDOW_H
