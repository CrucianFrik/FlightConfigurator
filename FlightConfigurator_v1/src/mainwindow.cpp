#include "mainwindow.h"
#include "param_info.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui{new Ui::MainWindow}
      //map_controller{new MapController(this)}
   // pixhawk_manager{ new PixhawkManager("/dev/serial/by-id/usb-ArduPilot_Pixhawk1_36003A000551393439373637-if00", 115200)}
{
    ui->setupUi(this);
    set_gui_elements();

    connect(ui->connectButton, &QPushButton::released, this, &MainWindow::connect_to_pixhawk);
    connect(ui->tabWidget, SIGNAL(currentChanged(int)), SLOT(update_widgets_geometry_slot()));//FIFME
    connect(ui->param_table, &QTableWidget::cellChanged, this, &MainWindow::process_updated_param);
}

void MainWindow::connect_to_pixhawk(){
    qDebug() << ui->controllerPath->text() << ui->conrollerSpeed->currentData().toInt();
    pixhawk_manager = new PixhawkManager(ui->controllerPath->text() , ui->conrollerSpeed->currentText().toInt());
    //pixhawk_manager = new PixhawkManager("/dev/serial/by-id/usb-ArduPilot_Pixhawk1_36003A000551393439373637-if00", 115200);
    pixhawk_manager->request_all_params();
    connect(pixhawk_manager, &PixhawkManager::all_params_received, this, &MainWindow::update_params_table);
};

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
    QStringList headers = {};
    ui->param_table->setRowCount(params.size());
    int i = 0;
    for (const auto &param_pair : params)
    {
        ParamInfo param = param_pair.second;
        //FIXME сделать неизменяемыми колонки name и discr
        ui->param_table->setItem(i, param_table_conumns::ind,  new QTableWidgetItem(QString::number(param_pair.first)));
        ui->param_table->setItem(i, param_table_conumns::name, new QTableWidgetItem(QString {param.param_id}));
    //    ui->param_table->setItem(i, param_table_conumns::value,  new QTableWidgetItem(QString::number(param.param_value)));//FIXME
        headers.append(QString::number(i));
        i++; //FIXME
    }
    ui->param_table->setVerticalHeaderLabels(headers);
    qDebug() << "update_table";
}

void MainWindow::process_updated_param(int row, int column){
    if (column == param_table_conumns::value && pixhawk_manager->is_all_params_received()){
        int index = ui->param_table->item(row, param_table_conumns::description)->text().toInt();
        float value = ui->param_table->item(row, param_table_conumns::value)->text().toFloat();
        pixhawk_manager->update_param_in_param_list(index, value);
        qDebug() << index << row << column << value;
    }

}
