#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui{new Ui::MainWindow}
      //map_controller{new MapController(this)}
{
    ui->setupUi(this);
    ui->setupUi(this);
    ui->label->setText("roll");
    ui->label_2->setText("pitch");
    ui->label_4->setText("yaw");

    ui->label_3->setText("xacc (G)");
    ui->label_5->setText("yacc (G)");
    ui->label_6->setText("zacc (G)");
    ui->lineEdit->setPlaceholderText("enter path to PIXHAWK");

    //ui->data_tab->layout()->addWidget(map_controller->get_data_map());
    //ui->plan_tab->layout()->addWidget(map_controller->get_plan_map());
    //map_controller->get_plan_map()->set_table(ui->tableWidget);

    connect(ui->tabWidget, SIGNAL(currentChanged(int)), SLOT(update_widgets_geometry_slot()));
}


MainWindow::~MainWindow()
{
    delete ui;
    //delete map_controller;

    for (int i=0; i<ui->table->rowCount(); i++){
        for (int j=0; j<ui->table->columnCount(); j++){
            delete ui->table->item(i, j);
        }
    }
}


void MainWindow::update_label(int lcd_num, double number)
{
    switch (lcd_num)
    {
        case 2:
            ui->lcdNumber_2->display(number);
            break;
        case 3:
            ui->lcdNumber_3->display(number);
            break;
        case 4:
            ui->lcdNumber_4->display(number);
            break;
        case 5:
            ui->lcdNumber_5->display(number);
            break;
        case 6:
            ui->lcdNumber_6->display(number);
            break;
        case 7:
            ui->lcdNumber_7->display(number);
            break;
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


void MainWindow::update_param_table(){

}
