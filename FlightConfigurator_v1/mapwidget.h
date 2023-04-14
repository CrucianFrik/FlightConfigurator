#ifndef MAPWIDGET_H
#define MAPWIDGET_H



#include <QAction>
#include <QTextStream>

#include <qgsmaptoolpan.h>
#include <qgsvectorlayer.h>

#include <mapbuttons.h>



class MapWidget : public QgsMapCanvas{
Q_OBJECT

public:
    MapWidget(const QList<QgsMapLayer*>& layers, QWidget* parent=nullptr);

    void move_to(QgsPointXY pos);

    void update_buttons_pos();

    void update_drone_pos(QgsPointXY pos);

    ~MapWidget();

private slots:
    void pan();
    void move_to_search_query();
    void centralize();

private:
    void set_settings();
    QgsPointXY str_to_point(QString str);

    QgsMapToolPan* tool_pan;

    SearchBar* search_bar;

    CentralizeButton* center_button;
    QgsRectangle full_zoom;

    DroneMarker* drone_marker;


    const double zoom_factor_wheel = 1.3;
    const double zoom_factor_move = 1e6;
    const bool antialiasing = true;
    const bool preview_jobs = true;
};



#endif // MAPWIDGET_H
