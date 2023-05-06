#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui{new Ui::MainWindow},
      map_controller{new MapController(this)}
{
    ui->setupUi(this);
    set_gui_elements();
    set_data_updation();
    
    ui->data_tab->layout()->addWidget(map_controller->get_data_map());
    ui->plan_tab->layout()->addWidget(map_controller->get_plan_map());
    map_controller->get_plan_map()->set_table(ui->points_table);
    ui->label_8->setPixmap(QPixmap(QString::fromUtf8(":/icons/logo.jpg")));
    connect(ui->tabWidget, SIGNAL(currentChanged(int)), SLOT(update_widgets_geometry_slot()));

    connect(ui->connectButton, &QPushButton::released, this, &MainWindow::connect_to_pixhawk);
    connect(ui->param_table, &QTableWidget::cellChanged, this, &MainWindow::process_updated_param);
    connect(ui->upload_params_button, &QPushButton::released, this, &MainWindow::upload_params);
    connect(ui->load_to_file_params_button, &QPushButton::released, this, &MainWindow::load_to_file_params);
    connect(ui->load_from_file_params_button, &QPushButton::released, this, &MainWindow::load_from_file_params);
    connect(ui->reset_params_button, &QPushButton::released, this, &MainWindow::reset_params);
}



void MainWindow::download_params(){
    if (!pixhawk_manager->get_parametr_list().size() || pixhawk_manager->get_parametr_list().find(0)==pixhawk_manager->get_parametr_list().end() ) {
        pixhawk_manager->request_all_params();
        qDebug() << "reuploading";
        params_download_checking_timer->start(2000);
    }
}

void MainWindow::connect_to_pixhawk(){
    pixhawk_manager = new PixhawkManager(ui->controllerPath->text(), ui->conrollerSpeed->currentText().toInt());
    if (pixhawk_manager->get_connection_status() != ConnectionStatus::successful){
        ui->connectButton->setPalette(QPalette(Qt::red));
        //pixhawk_manager = new PixhawkManager("/dev/serial/by-id/usb-ArduPilot_RoyalPenguin1_40003F000650484843373120-if00", 115200);
        //pixhawk_manager = new PixhawkManager("/dev/serial/by-id/usb-ArduPilot_Pixhawk1_36003A000551393439373637-if00", 115200);
        //pixhawk_manager = new PixhawkManager("/dev/serial/by-id/usb-3D_Robotics_PX4_FMU_v2.x_0-if00", 115200);
        if (pixhawk_manager->get_connection_status() == ConnectionStatus::successful){
            pixhawk_manager->request_all_params();
            connect(pixhawk_manager, &PixhawkManager::all_params_received, this, &MainWindow::update_params_table);
            ui->connectButton->setPalette(QPalette(Qt::blue));
            params_download_checking_timer->start(2000);
        }
    }
};

void MainWindow::reset_params(){
    update_params_table();
}

void MainWindow::set_data_updation(){
    info_updation_timer = new QTimer();
    int FREQUENCY = 100; //ms
    info_updation_timer->setInterval(FREQUENCY);
    connect(info_updation_timer, &QTimer::timeout, this, &MainWindow::data_window_update);
    info_updation_timer->start();

    params_download_checking_timer = new QTimer();
    params_download_checking_timer->setSingleShot(true);
    connect(params_download_checking_timer, &QTimer::timeout, this, &MainWindow::download_params);
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
    ui->param_table->verticalHeader()->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete map_controller;
    delete pixhawk_manager;

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
    map_controller->update_maps_geometry();
}


void MainWindow::resizeEvent(QResizeEvent *event){
    QMainWindow::resizeEvent(event);
    update_widgets_geometry_slot();
}


void MainWindow::update_params_table(){
    ui->connectButton->setPalette(QPalette(Qt::green));
    bool oldState = ui->param_table->blockSignals(true);
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
        ui->param_table->item(i, param_table_conumns::value)->setBackground(QColor{WHITECOLOR});
        i++; //FIXME
    }
    qDebug() << "params_table updated";
    all_parametrs_processed = 1;
    ui->param_table->blockSignals(oldState);
}

void MainWindow::process_updated_param(int row, int column){
    if (column == param_table_conumns::value && all_parametrs_processed){
        int index = ui->param_table->item(row, param_table_conumns::ind)->text().toInt(); // при замене на uint8_t значение лоамется
        QString str = ui->param_table->item(row, param_table_conumns::value)->text(); //FIXME: вынести проверку в PixhawkManager
        bool isdigit;
        str.toInt(&isdigit, 10);

        if (!isdigit) {
            //попытка ввода некорректного значения параметра
            bool oldState = ui->param_table->blockSignals(true);
            ui->param_table->item(row, param_table_conumns::value)->setText(QString::number(pixhawk_manager->get_param_val(index))); //FIXME
            ui->param_table->item(row, param_table_conumns::value)->setBackground(QColor{REDCOLOR});
            ui->param_table->blockSignals(oldState);
        }
        else{
            bool oldState = ui->param_table->blockSignals(true);
            ui->param_table->item(row, column)->setBackground(QColor{GREYCOLOR});
            ui->param_table->blockSignals(oldState);

            float value = ui->param_table->item(row, param_table_conumns::value)->text().toFloat();
            qDebug() << "changed index" << index;
            pixhawk_manager->remember__new_param_value(index, value);
        }
    }

}

void MainWindow::upload_params(){
    bool oldState = ui->param_table->blockSignals(true);
    for (const auto &param_pair : pixhawk_manager->get_updated_items_in_params_list())
    {
        qDebug() << "to green" << param_pair.first;
        ui->param_table->item(param_pair.first, param_table_conumns::value)->setBackground(QColor{GREENCOLOR});
    }
    ui->param_table->blockSignals(oldState);
    pixhawk_manager->upload_new_params();
}

void MainWindow::load_to_file_params(){
    const std::map<uint16_t, ParamInfo>& params = pixhawk_manager->get_parametr_list();
    //загрузка в файл
}

void MainWindow::load_from_file_params(){
    //for (param in loaded_from_file_params)
    //pixhawk_manager->update_param_in_params_list()

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

void MainWindow::delay(int millisecondsToWait){
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime ) {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}
