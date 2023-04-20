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
    void move_to_with_zoom(QgsPointXY pos);

    void update_buttons_pos();

    void update_drone_pos(QgsPointXY pos);

    ~MapWidget();

protected:
    void wheelEvent(QWheelEvent* e) override;

private slots:
    void move_to_search_query_slot();
    void move_to_drone_slot();
    void move_to_drone_with_zoom_slot();

    void centralize_slot();
    void change_focus_slot();

private:
    void enable_pan(bool is_enabled);
    void set_settings();
    void set_unfocused();

    QgsPointXY str_to_point(QString str);


    QgsRectangle full_zoom;

    QgsMapToolPan* tool_pan;

    SearchBar* search_bar;

    CentralizeButton* center_button;
    ZoomInButton*     zoomin_button;
    ZoomOutButton*    zoomout_button;
    FollowCheckbox*   follow_checkbox;

    const int center_button_pos   = 2;
    const int zoomin_button_pos   = 4;
    const int zoomout_button_pos  = 3;
    const int follow_checkbox_pos = 1;

    DroneMarker* drone_marker;

    bool is_focused = false;

    const double ZOOM_FACTOR_WHEEL = 1.3;
    const double ZOOM_FACTOR_MOVE = 1e6;
    const bool ANTIALIASING  = true;
    const bool PREVIEW_JOBS  = true;
    const bool IS_PAN_ENABLE = true;

};



#endif // MAPWIDGET_H
