#include "mainwindow.h"
#include "hendler_structs.h"
#include <QDebug>
#include <QFile>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui{new Ui::MainWindow},
      map_controller{new MapController(this)},
      horizon_view{new Aviagorizont_Viev(this)}
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
    connect(ui->param_table, &QTableWidget::cellChanged, this, &MainWindow::process_updated_param_slot);
    connect(ui->upload_params_button, &QPushButton::released, this, &MainWindow::upload_params);
    connect(ui->load_to_file_params_button, &QPushButton::released, this, &MainWindow::load_to_file_params);
    connect(ui->load_from_file_params_button, &QPushButton::released, this, &MainWindow::load_from_file_params);
    connect(ui->reset_params_button, &QPushButton::released, this, &MainWindow::reset_params);
    connect(ui->load_plan_to_file_button, &QPushButton::released, this, &MainWindow::load_plan_to_file);
    connect(ui->load_plan_from_file_button, &QPushButton::released, this, &MainWindow::load_plan_from_file);
    connect(ui->upload_plan_button, &QPushButton::released, this, &MainWindow::upload_plan);
}

void::MainWindow::reset(){
    ui->param_table->setRowCount(0);
    map_controller->plan_reset();
}

void MainWindow::download_params(){
    if (!pixhawk_manager->get_parametr_list().size() || pixhawk_manager->get_parametr_list().find(0)==pixhawk_manager->get_parametr_list().end() ) {
        pixhawk_manager->request_all_params();
        qDebug() << "reuploading";
        params_download_checking_timer->start(2000);
    }
}

void MainWindow::connect_to_pixhawk(){
    //pixhawk_manager = new PixhawkManager(ui->controllerPath->text(), ui->conrollerSpeed->currentText().toInt());
    if (pixhawk_manager->get_connection_status() != ConnectionStatus::successful){
        ui->connectButton->setPalette(QPalette(Qt::red));
        //pixhawk_manager = new PixhawkManager("/dev/serial/by-id/usb-ArduPilot_RoyalPenguin1_40003F000650484843373120-if00", 115200);
         //pixhawk_manager = new PixhawkManager("/dev/serial/by-id/usb-ArduPilot_Pixhawk1_36003A000551393439373637-if00", 115200);
        // pixhawk_manager = new PixhawkManager("/dev/serial/by-id/usb-3D_Robotics_PX4_FMU_v2.x_0-if00", 115200);
        pixhawk_manager = new PixhawkManager("/dev/ttyACM0", 115200);
        if (pixhawk_manager->get_connection_status() == ConnectionStatus::successful){
            pixhawk_manager->request_all_params();
            connect(pixhawk_manager, &PixhawkManager::all_params_received, this, &MainWindow::make_params_table);
            ui->connectButton->setPalette(QPalette(Qt::blue));
            params_download_checking_timer->start(2000);
            QMessageBox::information(this, "Уведомление", "Загрузка данных займёт несколько секунд");
        }
    }

    else if (pixhawk_manager->is_all_params_received()){
        qDebug() << pixhawk_manager->is_all_params_received();
        ui->connectButton->setPalette(QPalette(Qt::white));
        ui->connectButton->setText("CONNECT");
        pixhawk_manager->disconnect();
        delete pixhawk_manager;
        reset();
    }
};

void MainWindow::reset_params(){
    update_params_table();
    pixhawk_manager->reset_new_param_values();
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
    if (pixhawk_manager->get_connection_status()){
        //todel----------------
        mavlink_attitude_t a = pixhawk_manager->get_attitude();
        ui->label_3->setText("roll");
        ui->label_4->setText("pich");
        ui->data_dist_to_wp->display(qRadiansToDegrees(a.pitch));
        ui->data_speed->display(qRadiansToDegrees((a.roll)));
        //---------------------

        horizon_view->update(qRadiansToDegrees(a.pitch), qRadiansToDegrees(a.roll));
      
        mavlink_global_position_int_t gpi = pixhawk_manager->get_global_position_int();
        ui->data_altitude->display(gpi.relative_alt/1000); //m
        //ui->data_dist_to_wp->display(0);
        //ui->data_speed->display(pow(pow(gpi.vx, 2) + pow(gpi.vy, 2) + pow(gpi.vz, 2), 0.5));
        ui->data_z_speed->display(gpi.vz);
        ui->data_lat->display(gpi.lat);
        ui->data_lon->display(gpi.lon);
    }
}

//все set... выносятся сюда
void MainWindow::set_gui_elements(){
    ui->controllerPath->setPlaceholderText("enter path to PIXHAWK");
    ui->param_table->verticalHeader()->setVisible(false);

    QHeaderView* header_h = ui->param_table->horizontalHeader();
    QHeaderView* header_v = ui->param_table->verticalHeader();
//    header_h->setSectionResizeMode(1, QHeaderView::ResizeToContents);
//    header_v->setSectionResizeMode(QHeaderView::ResizeToContents);
    header_h->setSectionResizeMode(3, QHeaderView::Stretch);
    header_h->setSectionResizeMode(4, QHeaderView::Stretch);
    horizon_view->set_label_name(ui->horizon_lable);
//    test_flight();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete map_controller;
    delete pixhawk_manager;
    delete horizon_view;

    for (int i=0; i<ui->param_table->rowCount(); i++){
        for (int j=0; j<ui->param_table->columnCount(); j++){
            delete ui->param_table->item(i, j);
        }
    }
}


void MainWindow::show(){
    QMainWindow::show();
    resize(window_size);
    resize_points_table();
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
    bool oldState = ui->param_table->blockSignals(true);
    const std::map<uint16_t, ParamInfo>& params = pixhawk_manager->get_parametr_list();
    int i = 0;
    for (const auto &param_pair : params)
    {
        ui->param_table->item(i, param_table_conumns::value)->setText(QString::number(param_pair.second.param_value)); //FIXME
        ui->param_table->item(i, param_table_conumns::value)->setBackgroundColor(QColor{WHITECOLOR});
        i++; //FIXME
    }
    ui->param_table->blockSignals(oldState);
}

void MainWindow::make_params_table(){
    ui->connectButton->setPalette(QPalette(Qt::green));
    ui->connectButton->setText("DISCONNECT");

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
        i++; //FIXME
    }

    QString filename = PARAM_DESC_PATH; 
    QFile file(filename);
    if ( file.open(QIODevice::ReadWrite) ){
        qDebug() << "ReadWrite";
        QStringList wordList;
        int i = 0;
        char splitter = ';';
        while (!file.atEnd()) {
            QByteArray line = file.readLine();
            wordList.append(line.split(splitter).first());
            int row = pixhawk_manager->get_param_id_from_index(line.split(splitter)[0]);
            if (row > -1){
                QTableWidgetItem* acc_value_item = new QTableWidgetItem(QString{line.split(splitter)[2]});
                acc_value_item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);

                QTableWidgetItem* desc_item = new QTableWidgetItem(QString{line.split(splitter)[1]});
                desc_item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);

                ui->param_table->setItem(row, param_table_conumns::acc_value, acc_value_item);
                ui->param_table->setItem(row, param_table_conumns::description, desc_item);
            }
            i++;
        }
    }
    file.close();

    qDebug() << "params_table updated";
    all_parametrs_processed = 1;
    ui->param_table->blockSignals(oldState);
}

void MainWindow::process_updated_param_slot(int row, int column){ process_updated_param(row, column, 0); }

void MainWindow::process_updated_param(int row, int column, bool set_only_red){
    if (column == param_table_conumns::value && all_parametrs_processed){
        int index = ui->param_table->item(row, param_table_conumns::ind)->text().toInt(); // при замене на uint8_t значение лоамется
        QString str = ui->param_table->item(row, param_table_conumns::value)->text(); //FIXME: вынести проверку в PixhawkManager
        bool isdigit;
        str.toFloat(&isdigit);

        if (!isdigit) {
            //попытка ввода некорректного значения параметра
            bool oldState = ui->param_table->blockSignals(true);
            ui->param_table->item(row, param_table_conumns::value)->setText(QString::number(pixhawk_manager->get_param_val(index))); //FIXME
            ui->param_table->item(row, param_table_conumns::value)->setBackground(QColor{REDCOLOR});
            pixhawk_manager->remember_new_param_value(index, pixhawk_manager->get_param_val(index));
            ui->param_table->blockSignals(oldState);
        }
        else if (!set_only_red){
            bool oldState = ui->param_table->blockSignals(true);
            ui->param_table->item(row, column)->setBackground(QColor{GREYCOLOR});
            ui->param_table->blockSignals(oldState);

            float value = ui->param_table->item(row, param_table_conumns::value)->text().toFloat();
            qDebug() << "changed index" << index;
            pixhawk_manager->remember_new_param_value(index, value);
        }
    }

}

void MainWindow::upload_params(){
    if (! pixhawk_manager->is_all_params_received()) {
        QMessageBox::warning(this, "Ошибка", "Дождитесь загрузки параметров");
        return;
    }
    bool oldState = ui->param_table->blockSignals(true);
    for (const auto &param_pair : pixhawk_manager->get_updated_items_in_params_list())
    {
        qDebug() << "to green" << param_pair.first;
        ui->param_table->item(param_pair.first, param_table_conumns::value)->setBackground(QColor{GREENCOLOR});
    }
    ui->param_table->blockSignals(oldState);
    pixhawk_manager->upload_new_params();
    QMessageBox::information(this, "Уведомление", "Загрузка параметров началась. На отключайте контролле в течении 15 секунд."); //это неправда, проверки успеха загрузки нет
}

void MainWindow::load_to_file_params(){
    if (! pixhawk_manager->is_all_params_received()) {
        QMessageBox::warning(this, "Ошибка", "Дождитесь загрузки параметров");
        return;
    }
    const std::map<uint16_t, ParamInfo>& params = pixhawk_manager->get_parametr_list();
    QString filename = FULL_PARAM_PATH;
    QFile file(filename);
    if ( file.open(QIODevice::ReadWrite) ){
        QTextStream stream( &file );

        for (const auto &i : params) {
            QString s{i.second.param_id};
            stream << s << "," << i.second.param_value << "\n";
        }
    }
    file.close();
    QMessageBox::information(this, "Уведомление", "Актуальные параметры из контроллера загружены в файл " + filename); //это неправда, проверки успеха загрузки нет
}

void MainWindow::load_from_file_params(){
    if (! pixhawk_manager->is_all_params_received()) {
        QMessageBox::warning(this, "Ошибка", "Дождитесь загрузки параметров");
        return;
    }

    QString filename = QFileDialog::getOpenFileName(this, "Открыть");
    if(filename.isEmpty()){ return; }
    QFile file(filename);
    QString target_expansion = ".param";
    int n = target_expansion.length();
//    qDebug() << "FILENAME" << filename << filename.mid(filename.length() - n, n);

    if(filename.mid(filename.length() - n, n) != target_expansion){
        QMessageBox::warning(this, "Предупреждение", "Загрузите файл с расширением "+target_expansion);
        return;
    }
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Предупреждение", "Не удалось открыть файл: " +
                             file.errorString());
        return;
    }

    try {
    QTextStream in(&file);
    bool oldState = ui->param_table->blockSignals(true);
    pixhawk_manager->reset_new_param_values();
    std::map<uint16_t, ParamInfo> params = pixhawk_manager->get_parametr_list();
    while (!in.atEnd())
    {
        QString line = in.readLine();
       // qDebug() << line;
        int ind = pixhawk_manager->get_param_id_from_index(line.split(",")[0]);
        if (ind != -1){
            uint16_t index{ind};
            ParamInfo param = params[index];
            if (line.split(",")[1].toFloat() == param.param_value)
                ui->param_table->item(index, param_table_conumns::value)->setBackground(QColor{LIGHTGREYCOLOR});
            else{
                ui->param_table->item(index, param_table_conumns::value)->setBackground(QColor{BLUECOLOR});
                pixhawk_manager->remember_new_param_value(index, line.split(",")[1].toFloat());
            }
            ui->param_table->item(index, param_table_conumns::value)->setText(line.split(",")[1]);
            process_updated_param(index, param_table_conumns::value, 1);
         // qDebug() << param_pair.second.param_value << param_pair.first << line.split(",")[1].toFloat() << param_pair.second.param_value;
        }
    }
    ui->param_table->blockSignals(oldState);
    file.close();
    QMessageBox::information(this, "Уведомление", "Параметры загружены.\n"
                "Ячейка серая - новое значение равно старому (не обновлён),\n голубая - новое значение отлично от старого (обновлён)\n"
                "красная - новое значение некорректно (не обновлён)\n"
                "белая или тёмно серая - параметра не было в файле (не обновлён)\n");
    }
    catch (const char* error_message)
    {
        pixhawk_manager->reset_new_param_values();
        QMessageBox::warning(this, "Ошибка чтения файла", error_message);
    }
}

void MainWindow::test_flight(){
    double r = 0.0007, d = 0.0025;

    QgsPointXY p1(38.104376, 55.604367);
    QgsPointXY p2(p1.x(),   p1.y()+2*r);
    QgsPointXY p3(p1.x()+d, p1.y()+r);

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

/////////////////////////////////////////////////////////////////MISSION/////////////////////////////////////////////////////////////
void MainWindow::load_plan_to_file(){
    if (map_controller->load_plan_to_file(MISSION_FILE)){
        QMessageBox::information(this, "Уведомление", "план успешно загружен в config/Mission.flyplan");
    } //FIXME
    else{
        QMessageBox::warning(this, "Ошибка", "Не удалось загрузить план в файл");
    }
}

void MainWindow::load_plan_from_file(){
    QString filename = QFileDialog::getOpenFileName(this, "Открыть");
    if(filename.isEmpty()){ return; }
    QString target_expansion = ".flyplan";
    int n = target_expansion.length();
    if(filename.mid(filename.length() - n, n) != target_expansion){
        QMessageBox::warning(this, "Предупреждение", "Загрузите файл с расширением "+target_expansion);
        return;
    }
    map_controller->load_plan_from_file(filename);
}

void MainWindow::upload_plan(){
    QList<std::array<double, 3>> arr;
    map_controller->get_plan_points(arr);
    pixhawk_manager->upload_flight_mission(arr);
    QMessageBox::information(this, "Уведомление", "План успешно загружен"); //проверки нет
}

void MainWindow::resize_points_table(){
    for (int i=0; i<ui->points_table->columnCount(); i++){
        ui->points_table->setColumnWidth(i, (double) ui->points_table->width() * points_table_col_proportions[i]);
    }
}
