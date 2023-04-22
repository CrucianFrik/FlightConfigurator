#include "planmapwidget.h"


FlightPlan::FlightPlan(QgsMapCanvas *canvas)
    : QgsRubberBand(canvas)
{
    setColor(color);
    setLineStyle(line_style);
    setWidth(line_width);
}

int FlightPlan::points_count(){
    return numberOfVertices();
}

void FlightPlan::set_point_pos(int point_index, QgsPointXY new_pos){
    movePoint(point_index, new_pos);
}

QgsPointXY FlightPlan::get_point_pos(int point_index){
    return *getPoint(point_index);
}

void FlightPlan::set_point_alt(int point_index, double alt){
    alts[point_index] = alt;
}

double FlightPlan::get_point_alt(int point_index){
    return alts[point_index];
}

void FlightPlan::add_point(QgsPointXY pos){
    addPoint(pos);
    alts.push_back(default_alt);
}

void FlightPlan::delete_point(int point_index){
    removePoint(point_index);
    alts.removeAt(point_index);
}



PlanMapWidget::PlanMapWidget(const QList<QgsMapLayer *> &layers, QWidget *parent)
    : MapWidget(layers, parent),
      flight_plan{new FlightPlan(this)}
{
    center_button  ->set_pos_number(center_button_pos);
    zoomin_button  ->set_pos_number(zoomin_button_pos);
    zoomout_button ->set_pos_number(zoomout_button_pos);
}

PlanMapWidget::~PlanMapWidget(){
    delete flight_plan;
}
