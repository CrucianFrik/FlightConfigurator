#include "planmapwidget.h"


FlightPlan::FlightPlan(QgsMapCanvas *canvas)
    : QgsRubberBand(canvas),
      possible_line{new QgsRubberBand(canvas)}
{
    setColor(color);
    setLineStyle(drawed_style);
    setWidth(drawed_width);

    possible_line->setColor(color);
    possible_line->setLineStyle(possible_style);
    possible_line->setWidth(possible_width);
}

int FlightPlan::points_count(){
    return points.size();
}

void FlightPlan::set_point_pos(int point_index, QgsPointXY new_pos){
    movePoint(point_index, new_pos);
    points[point_index] = new_pos;
}

QgsPointXY FlightPlan::get_point_pos(int point_index){
    return points[point_index];
}

void FlightPlan::set_point_alt(int point_index, double alt){
    alts[point_index] = alt;
}

double FlightPlan::get_point_alt(int point_index){
    return alts[point_index];
}

void FlightPlan::add_point(QgsPointXY pos){
    clear_possible_line();

    addPoint(pos);
    points.push_back(pos);
    alts.push_back(default_alt);
}

void FlightPlan::delete_point(int point_index){
    removePoint(point_index);
    points.removeAt(point_index);
    alts.removeAt(point_index);
}

void FlightPlan::update_possible_line(QgsPointXY pos){
    if (!points_count()) return;

    if (possible_line->numberOfVertices() == 2){
        possible_line->movePoint(1, pos);
    } else {
        possible_line->addPoint( get_point_pos(points_count()-1) );
        possible_line->addPoint( pos );
    }
}

void FlightPlan::clear_possible_line(){
    possible_line->reset();
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

void PlanMapWidget::mousePressEvent(QMouseEvent *e){
    MapWidget::mousePressEvent(e);

    if (is_plan_drawing && e->button() == Qt::RightButton){
        QgsPointXY mouse_pos = QgsMapMouseEvent(this,e).mapPoint();

        flight_plan->update_possible_line(mouse_pos);
        is_right_button_pressed = true;
    }
}

void PlanMapWidget::mouseMoveEvent(QMouseEvent *e){
    MapWidget::mouseMoveEvent(e);

    if (is_plan_drawing && is_right_button_pressed){
        QgsPointXY mouse_pos = QgsMapMouseEvent(this,e).mapPoint();

        flight_plan->update_possible_line(mouse_pos);
    }
}

void PlanMapWidget::mouseReleaseEvent(QMouseEvent *e){
    MapWidget::mouseReleaseEvent(e);

    if (is_plan_drawing && e->button() == Qt::RightButton){
        QgsPointXY mouse_pos = QgsMapMouseEvent(this,e).mapPoint();

        flight_plan->add_point(mouse_pos);
        is_right_button_pressed = false;
    }
}
