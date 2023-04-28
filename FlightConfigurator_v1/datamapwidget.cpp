#include "datamapwidget.h"

DataMapWidget::DataMapWidget(const QList<QgsMapLayer *> &layers, QWidget *parent)
    : MapWidget(layers, parent),
      follow_checkbox{new FollowCheckbox(this)},
      drone_marker{new DroneMarker(this)}
{
    follow_checkbox->set_pos_number(follow_checkbox_pos);
    center_button  ->set_pos_number(center_button_pos);
    zoomin_button  ->set_pos_number(zoomin_button_pos);
    zoomout_button ->set_pos_number(zoomout_button_pos);

    connect(follow_checkbox, SIGNAL(clicked()), SLOT(change_focus_slot()));
    connect(this, SIGNAL(scaleChanged(double)), SLOT(update_drone_size()));
}


void DataMapWidget::update_drone_size(){
    drone_marker->update_size( extent().height(), extent().width() );
}


DataMapWidget::~DataMapWidget(){
    delete follow_checkbox;
    delete drone_marker;
}


void DataMapWidget::change_focus_slot(){
    follow_checkbox->switch_icon();
    if (!is_focused){
        move_to_drone_with_zoom_slot();
    }
    enable_pan(is_focused);
    is_focused = !is_focused;
}


void DataMapWidget::set_unfocused(){
    if (is_focused){
        change_focus_slot();
        waitWhileRendering();
    }
}


void DataMapWidget::move_to_drone_slot(){
    move_to(drone_marker->get_pos());
}


void DataMapWidget::move_to_drone_with_zoom_slot(){
    move_to_with_zoom(drone_marker->get_pos());
}


void DataMapWidget::wheelEvent(QWheelEvent *e){
    QgsMapCanvas::wheelEvent(e);

    if (is_focused){
        stopRendering();
        move_to_drone_slot();
    }
}


void DataMapWidget::update_drone_pos(QgsPointXY pos, double angle){
    drone_marker->set_location(pos, angle);

    if (is_focused){
        waitWhileRendering();
        move_to_drone_slot();
    }
}


void DataMapWidget::update_buttons_pos(){
    MapWidget::update_buttons_pos();

    follow_checkbox->update_pos(size());
}


void DataMapWidget::move_to_search_query_slot(){
    set_unfocused();

    MapWidget::move_to_search_query_slot();
}


void DataMapWidget::centralize_slot(){
    set_unfocused();

    MapWidget::centralize_slot();
}
