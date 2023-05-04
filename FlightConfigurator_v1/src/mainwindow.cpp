#include "mainwindow.h"
#include "hendler_structs.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui{new Ui::MainWindow}
      //map_controller{new MapController(this)}
{
    ui->setupUi(this);
    set_gui_elements();
    set_data_updation();

    connect(ui->connectButton, &QPushButton::released, this, &MainWindow::connect_to_pixhawk);
    connect(ui->tabWidget, SIGNAL(currentChanged(int)), SLOT(update_widgets_geometry_slot()));//FIFME
    connect(ui->param_table, &QTableWidget::cellChanged, this, &MainWindow::process_updated_param);
    connect(ui->upload_params_button, &QPushButton::released, this, &MainWindow::upload_params);
    connect(ui->load_to_file_params_button, &QPushButton::released, this, &MainWindow::load_to_file_params);
    connect(ui->load_from_file_params_button, &QPushButton::released, this, &MainWindow::load_from_file_params);
}

void MainWindow::connect_to_pixhawk(){
    //pixhawk_manager = new PixhawkManager(ui->controllerPath->text(), ui->conrollerSpeed->currentText().toInt());
    if (pixhawk_manager->get_connection_status() != ConnectionStatus::successful){
        pixhawk_manager = new PixhawkManager("/dev/serial/by-id/usb-ArduPilot_Pixhawk1_36003A000551393439373637-if00", 115200);
        pixhawk_manager->request_all_params(); //сделать гифку загрузки
        connect(pixhawk_manager, &PixhawkManager::all_params_received, this, &MainWindow::update_params_table);
    }
};

void MainWindow::set_data_updation(){
    timer = new QTimer();
    int FREQUENCY = 100; //ms
    timer->setInterval(FREQUENCY);
    connect(timer, &QTimer::timeout, this, &MainWindow::data_window_update);
    timer->start();
}

void MainWindow::data_window_update(){

    //todel----------------
    mavlink_attitude_t a = pixhawk_manager->get_attitude();
    ui->label_3->setText("roll");
    ui->label_4->setText("pich");
    ui->data_dist_to_wp->display(qRadiansToDegrees(a.pitch));
    ui->data_speed->display(qRadiansToDegrees((a.roll)));
    //---------------------

    mavlink_global_position_int_t gpi = pixhawk_manager->get_global_position_int();
    ui->data_altitude->display(gpi.relative_alt/1000); //m
    //ui->data_dist_to_wp->display(0);
    //ui->data_speed->display(pow(pow(gpi.vx, 2) + pow(gpi.vy, 2) + pow(gpi.vz, 2), 0.5));
    ui->data_z_speed->display(gpi.vz);
    ui->data_lat->display(gpi.lat);
    ui->data_lon->display(gpi.lon);
}

//все set... выносятся сюда
void MainWindow::set_gui_elements(){
    ui->controllerPath->setPlaceholderText("enter path to PIXHAWK");
}

MainWindow::~MainWindow()
{
    delete ui;
    //delete map_controller;
    for (int i=0; i<ui->param_table->rowCount(); i++){
        for (int j=0; j<ui->param_table->columnCount(); j++){
            delete ui->param_table->item(i, j);
        }
    }
}


void MainWindow::show(){
    QMainWindow::show();
    resize(window_size);
    setWindowTitle(window_title);
}


void MainWindow::update_widgets_geometry_slot(){
    //map_controller->update_maps_geometry();
}


void MainWindow::resizeEvent(QResizeEvent *event){
    QMainWindow::resizeEvent(event);
    update_widgets_geometry_slot();
}

void MainWindow::update_params_table()
{
    const std::map<uint16_t, ParamInfo>& params = pixhawk_manager->get_parametr_list();
    ui->param_table->setRowCount(params.size());
    int i = 0;
    for (const auto &param_pair : params)
    {
        ParamInfo param = param_pair.second;
        //FIXME сделать неизменяемыми колонки name и discr
        QTableWidgetItem* name_item = new QTableWidgetItem(QString{param.param_id});
        name_item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);

        QTableWidgetItem* index_item = new QTableWidgetItem(QString::number(param_pair.first));
        index_item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);

        ui->param_table->setItem(i, param_table_conumns::ind, index_item);
        ui->param_table->setItem(i, param_table_conumns::name, name_item);
        ui->param_table->setItem(i, param_table_conumns::value, new QTableWidgetItem(QString::number(param.param_value))); //FIXME
        i++; //FIXME
    }
    qDebug() << "params_table updated";
    all_parametrs_processed = 1;
}

void MainWindow::process_updated_param(int row, int column){
    if (column == param_table_conumns::value && all_parametrs_processed){
        int index = ui->param_table->item(row, param_table_conumns::ind)->text().toInt();

        QString str = ui->param_table->item(row, param_table_conumns::value)->text(); //FIXME: вынести проверку в PixhawkManager
        bool isdigit;
        str.toInt(&isdigit, 10);

        if (!isdigit) {
            //попытка некорректного изменения параметра
            bool oldState = ui->param_table->blockSignals(true);
            ui->param_table->item(row, param_table_conumns::value)->setText(QString::number(pixhawk_manager->get_param_val(index))); //FIXME
            ui->param_table->item(row, param_table_conumns::value)->setBackground(QColor{235, 167, 162});
            ui->param_table->blockSignals(oldState);
        }
        else{
            bool oldState = ui->param_table->blockSignals(true);
            ui->param_table->item(row, column)->setBackground(QColor{184, 197, 194});
            ui->param_table->blockSignals(oldState);

            float value = ui->param_table->item(row, param_table_conumns::value)->text().toFloat();
            pixhawk_manager->update_param_in_param_list(index, value);
        }
    }

}

void MainWindow::upload_params(){

}

void MainWindow::load_to_file_params(){
    const std::map<uint16_t, ParamInfo>& params = pixhawk_manager->get_parametr_list();
    //загрузка в файл
}

void MainWindow::load_from_file_params(){
    //for (param in loaded_from_file_params)
    //pixhawk_manager->update_param_in_param_list()
}
