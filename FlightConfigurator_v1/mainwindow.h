#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QPair>
#include <qgsrasterlayer.h>

#include "mavlink.h"
#include "mapwidget.h"
#include "./ui_mainwindow.h"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow{
Q_OBJECT

public:
    MainWindow(const QList< QPair<QString, QString> >& layers_paths, QWidget *parent = nullptr);

    void show();

    void resizeEvent(QResizeEvent* event);

    ~MainWindow();

public slots:
    void updateLabel(int lcd_num, double number);

private slots:
    void update_widgets_geometry();

private:


    Ui::MainWindow *ui;

    MapWidget* mapw_data;
    MapWidget* mapw_plan;

    const QSize window_size = {1500, 800};
    const QString window_title = "FlightConfigurator";
};



#endif // MAINWINDOW_H
