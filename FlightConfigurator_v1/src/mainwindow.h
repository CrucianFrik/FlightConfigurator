#ifndef MAINWINDOW_H
#define MAINWINDOW_

#include <QDesktopWidget>
#include <QMainWindow>
#include <QTime>
#include <QTimer>
#include <QFileDialog>
#include <QtMath>
#include <QMessageBox>

//#include "mavlink.h"
#include "./ui_mainwindow.h"
#include "hendler_structs.h"
#include "pixhawk_manager.h"
//#include <mapcontroller.h>

void delay( int millisecondsToWait );

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
private:
    Q_OBJECT
    Ui::MainWindow *ui;

    //MapController* map_controller;
    PixhawkManager* pixhawk_manager; //sheredptr + singltone
    const QSize window_size = QDesktopWidget().size();
    const QString window_title = "FlightConfigurator";
    QTimer* info_updation_timer;
    QTimer* params_download_checking_timer;

    void set_gui_elements();
    void set_data_updation();
    void reset();
    bool all_parametrs_processed = 0;
    
public:
    MainWindow(QWidget *parent = nullptr);
    void show();
    void test_flight();
    void resizeEvent(QResizeEvent* event) override;
    ~MainWindow();

private slots:
    void update_widgets_geometry_slot();
    void update_params_table();
    void process_updated_param(int row, int column, bool set_only_red);
    void process_updated_param_slot(int row, int column);
    void connect_to_pixhawk();
    void data_window_update();

    void upload_params();
    void download_params();
    void load_to_file_params();
    void load_from_file_params();
    void reset_params();
};
#endif // MAINWINDOW_H
