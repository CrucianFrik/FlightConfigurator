#ifndef DATAMAPWIDGET_H
#define DATAMAPWIDGET_H



#include "mapwidget.h"
#include "dronemarker.h"



class DataMapWidget : public MapWidget {
Q_OBJECT

public:
    DataMapWidget(const QList<QgsMapLayer*>& layers, QWidget* parent=nullptr);

    void update_drone_pos(QgsPointXY pos, double angle);
    void update_buttons_pos() override;

    ~DataMapWidget();

private slots:
    void move_to_search_query_slot() override;
    void centralize_slot() override;

    void change_focus_slot();

    void move_to_drone_slot();
    void move_to_drone_with_zoom_slot();

    void update_drone_size();

private:
    void wheelEvent(QWheelEvent* e) override;

    void set_unfocused();


    FollowCheckbox* follow_checkbox;

    DroneMarker* drone_marker;

    bool is_focused = false;

    const int   center_button_pos = 2;
    const int   zoomin_button_pos = 4;
    const int  zoomout_button_pos = 3;
    const int follow_checkbox_pos = 1;

};



#endif // DATAMAPWIDGET_H
