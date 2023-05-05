#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui{new Ui::MainWindow},
      map_controller{new MapController(this)}
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

    ui->data_tab->layout()->addWidget(map_controller->get_data_map());
    ui->plan_tab->layout()->addWidget(map_controller->get_plan_map());
    map_controller->get_plan_map()->set_table(ui->tableWidget);
    ui->label_8->setPixmap(QPixmap(QString::fromUtf8(":/icons/logo.jpg")));
    connect(ui->tabWidget, SIGNAL(currentChanged(int)), SLOT(update_widgets_geometry_slot()));
}


MainWindow::~MainWindow()
{
    delete ui;
    delete map_controller;

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
    map_controller->update_maps_geometry();
}


void MainWindow::resizeEvent(QResizeEvent *event){
    QMainWindow::resizeEvent(event);

    update_widgets_geometry_slot();
}


void MainWindow::test_flight(){
    double r=15;
    QgsPointXY p1(-10,-15), p2(-10,15), p3(40,0);
    double dfi=0.05, dx=dfi*r;
    int delay_time = 50;

    while (true){
        for (double fi=M_PI_2; fi<2*M_PI; fi+=dfi){
            delay(delay_time);
            map_controller->update_drone_pos({p1.x()+r*cos(fi), p1.y()+r*sin(fi)}, fi);
        }
        for (double x=0; x<p3.x()-p1.x()-r; x+=dx){
            delay(delay_time);
            map_controller->update_drone_pos({p1.x()+r+x, p1.y()}, -M_PI_2);
        }
        for (double fi=-M_PI_2; fi<M_PI_2; fi+=dfi){
            delay(delay_time);
            map_controller->update_drone_pos({p3.x()+r*cos(fi), p3.y()+r*sin(fi)}, fi);
        }
        for (double x=0; x<p3.x()-p1.x()-r; x+=dx){
            delay(delay_time);
            map_controller->update_drone_pos({p3.x()-x, p2.y()}, M_PI_2);
        }
        for (double fi=0; fi<3*M_PI_2; fi+=dfi){
            delay(delay_time);
            map_controller->update_drone_pos({p2.x()+r*cos(fi), p2.y()+r*sin(fi)}, fi);
        }
    }
}
