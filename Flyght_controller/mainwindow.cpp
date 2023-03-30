#include "mainwindow.h"
#include "./ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_5->setText("qwertyu");
    ui->label_7->setPixmap(QPixmap(QString::fromUtf8("map.png")));
}

MainWindow::~MainWindow()
{
    delete ui;
}

