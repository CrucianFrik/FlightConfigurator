#include "mainwindow.h"


MainWindow::MainWindow(const QList< QPair<QString, QString> >& layers_paths, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->label->setText("yaw");
    ui->label_2->setText("pitch");
    ui->label_3->setText("roll");
    ui->label_4->setText("yaw");
    ui->label_5->setText("");
    ui->label_6->setText("");

    QList<QgsMapLayer*> layers;
    for (auto& path : layers_paths){
        layers.push_back(new QgsVectorLayer( QDir(QDir::currentPath()).filePath(path.first), path.second, "ogr" ));
    }
//    layers.push_back(new QgsRasterLayer("/home/k7ps/QtProjects/FlightConfigurator/maps/raster/worldmap.tif","tif"));

    mapw_data = new MapWidget(layers);
    mapw_plan = new MapWidget(layers);

    ui->data_tab->layout()->addWidget(mapw_data);
    ui->plan_tab->layout()->addWidget(mapw_plan);

    connect(ui->tabWidget, SIGNAL(currentChanged(int)), SLOT(update_widgets_geometry()));

//    QTimer *timer = new QTimer(this);
//    connect(timer, SIGNAL(timeout()), SLOT(updateLabel()));
//    timer->start(1000);
}


MainWindow::~MainWindow()
{
    delete ui;
    delete mapw_data;
    delete mapw_plan;
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
    mapw_data->update_buttons_pos();
    mapw_plan->update_buttons_pos();
}


void MainWindow::resizeEvent(QResizeEvent *event){
    QMainWindow::resizeEvent(event);

    update_widgets_geometry();
}
