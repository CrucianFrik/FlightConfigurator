#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      map_controller{new MapController(this)}
{
    ui->setupUi(this);
    ui->lineEdit->setPlaceholderText("enter path to PIXHAWK");
    ui->data_tab->layout()->addWidget(map_controller->get_data_map());
    ui->plan_tab->layout()->addWidget(map_controller->get_plan_map());
    ui->table->resizeColumnsToContents();
    ui->table->resizeRowsToContents();
    connect(ui->tabWidget, SIGNAL(currentChanged(int)), SLOT(update_widgets_geometry()));

//            tableWidget->addWidget(pushButton_5);
//    QTimer *timer = new QTimer(this);
//    connect(timer, SIGNAL(timeout()), SLOT(updateLabel()));
//    timer->start(1000);
}


MainWindow::~MainWindow()
{
    delete ui;
    delete map_controller;
}


void MainWindow::updateLabel(int lcd_num, double number)
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


void MainWindow::update_widgets_geometry(){
    map_controller->update_maps_geometry();
}


void MainWindow::resizeEvent(QResizeEvent *event){
    QMainWindow::resizeEvent(event);

    update_widgets_geometry();
}
