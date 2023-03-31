#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "mavlink.h"
#include <QTimer>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setText("yaw");
    ui->label_2->setText("pitch");
    ui->label_3->setText("roll");
    ui->label_4->setText("yaw");
    ui->label_5->setText("");
    ui->label_6->setText("");
    ui->label_7->setPixmap(QPixmap(QString::fromUtf8(":images/map.png")));

    QTimer *timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(updateLabel()));
        timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
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
