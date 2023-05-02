#include "planmapwidget.h"


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


void PlanMapWidget::set_table(QTableWidget *t){
    flight_plan->set_table(t);
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
