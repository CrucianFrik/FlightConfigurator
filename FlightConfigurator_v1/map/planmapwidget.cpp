#include "planmapwidget.h"


PlanMapWidget::PlanMapWidget(const QList<QgsMapLayer *> &layers, QWidget *parent)
    : MapWidget(layers, parent),
      flight_plan{new FlightPlan(this)}
{
    center_button  ->set_pos_number(center_button_pos);
    zoomin_button  ->set_pos_number(zoomin_button_pos);
    zoomout_button ->set_pos_number(zoomout_button_pos);

    connect(this, SIGNAL(scaleChanged(double)), SLOT(update_arrows_size()));
}


PlanMapWidget::~PlanMapWidget(){
    delete flight_plan;
}


void PlanMapWidget::update_arrows_size(){
    flight_plan->update_arrows_size( extent().height(), extent().width() );
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


void PlanMapWidget::get_plan_points(QList<std::array<double, 3> > &arr){
    flight_plan->get_points(arr);
}


bool PlanMapWidget::load_plan_to_file(const QString &path){
    return flight_plan->load_to_file(path);
}


bool PlanMapWidget::load_plan_from_file(const QString &path){
    return flight_plan->load_from_file(path);
}


QString PlanMapWidget::get_plan_file_format(){
    return flight_plan->get_plan_file_format();
}
