#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->yaw_label->setText("yaw");
    ui->pitch_label->setText("pitch");
    ui->roll_label->setText("roll");
    ui->yaw_label_2->setText("yaw");
    ui->label_5->setText("");
    ui->label_6->setText("");
    ui->label_7->setPixmap(QPixmap(QString::fromUtf8(":images/map.png")));

//    QTimer *timer = new QTimer(this);
//        connect(timer, SIGNAL(timeout()), this, SLOT(update_label()));
//        timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_label(int lcd_num, double number)
{
    switch (lcd_num)
    {
        case 2:
            ui->yaw_number->display(number);
            break;
        case 3:
            ui->pitch_number->display(number);
            break;
        case 4:
            ui->yaw_number_2->display(number);
            break;
        case 5:
            ui->roll_number->display(number);
            break;
        case 6:
            ui->lcdNumber_6->display(number);
            break;
        case 7:
            ui->lcdNumber_7->display(number);
            break;
    }
}

void MainWindow::update_table(std::vector<std::vector<std::string> > param)
{
    ui->table_settings->setRowCount(param.size());
    ui->table_settings->setColumnCount(param[0].size());
    for(int i = 0; i < param.size(); ++i)
    {
        for(int j = 0; j < param[i].size(); ++j)
        {
            ui->table_settings->setItem(i, j, new QTableWidgetItem(QString::fromStdString(param[i][j])));
        }
    }
}

void MainWindow::update_table(std::vector<std::pair<QString, int> > param)
{
    ui->table_settings->setRowCount(param.size());
    ui->table_settings->setColumnCount(1);
    QStringList headers = {};
    for(int i = 0; i < param.size(); ++i)
    {
        ui->table_settings->setItem(i, 0, new QTableWidgetItem(QString::number(param[i].second)));
        headers.append(param[i].first);
    }
    ui->table_settings->setVerticalHeaderLabels(headers);
}
