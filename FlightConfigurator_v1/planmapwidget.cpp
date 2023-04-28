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
    points[point_index] = new_pos;
    movePoint(point_index, points[point_index]);
    update();
}

void FlightPlan::set_point_pos_x(int point_index, double x){
    set_point_pos(point_index, QgsPointXY(x, points[point_index].y()));
}

void FlightPlan::set_point_pos_y(int point_index, double y){
    set_point_pos(point_index, QgsPointXY(points[point_index].x(), y));
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


    int n=points_count();
    table->setRowCount(n);

    QTableWidgetItem* pos_x = new QTableWidgetItem(QString::number(pos.y(), 'g', pos_precision));
    QTableWidgetItem* pos_y = new QTableWidgetItem(QString::number(pos.x(), 'g', pos_precision));
    QTableWidgetItem* alt   = new QTableWidgetItem(QString::number(default_alt, 'g', alt_precision));

    table->setItem(n-1, COLUMN_LAT, pos_x);
    table->setItem(n-1, COLUMN_LON, pos_y);
    table->setItem(n-1, COLUMN_ALT, alt);

    QPushButton* btn = new QPushButton;
    btn->setIcon(delete_button_icon);
    connect(btn, SIGNAL(clicked(bool)), SLOT(del_button_pressed()));
    table->setCellWidget(n-1, COLUMN_DEL, btn);

    table->update();
}

void FlightPlan::delete_point(int point_index){
    removePoint(point_index);
    points.removeAt(point_index);
    alts.removeAt(point_index);

    update();
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

void FlightPlan::set_table(QTableWidget *t){
    table = t;

    connect(table, SIGNAL(cellChanged(int,int)), SLOT(update_point(int,int)));
}

void FlightPlan::update_point(int row, int column){
    bool is_ok = false;
    double changed = table->item(row, column)->text().toDouble(&is_ok);

    if (!is_ok){
        table->item(row, column)->setBackground(error_cell_color);
        return;
    }
    table->item(row, column)->setBackground(default_cell_color);

    switch(column){
    case COLUMN_LAT:
        set_point_pos_y(row, changed);
        break;
    case COLUMN_LON:
        set_point_pos_x(row, changed);
        break;
    case COLUMN_ALT:
        set_point_alt(row, changed);
        break;
    }

    QString rounded_text = QString::number(changed, 'g',
            ( column == COLUMN_ALT ? alt_precision : pos_precision ));
    table->item(row, column)->setText(rounded_text);
}

void FlightPlan::del_button_pressed(){
    for (int row=0; row < table->rowCount(); row++){
        if (sender() == table->cellWidget(row, COLUMN_DEL)){
            delete_point(row);

            table->removeRow(row);
            table->update();
        }
    }
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
