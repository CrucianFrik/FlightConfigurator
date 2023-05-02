#include "flightplan.h"


PlanPoint::PlanPoint(QgsMapCanvas *canvas, QgsPointXY pos)
    : QgsVertexMarker(canvas)
{
    alt = default_alt;

    setCenter(pos);
    setIconSize(icon_size);
    setPenWidth(outline_width);
    setIconType(icon_type);
    setFillColor(fill_color);
    setColor(outline_color);
}

QgsPointXY PlanPoint::get_pos(){
    return center();
}

void PlanPoint::set_pos(QgsPointXY new_pos){
    setCenter(new_pos);
}

double PlanPoint::get_alt(){
    return alt;
}

void PlanPoint::set_alt(double new_alt){
    alt = new_alt;
}

void PlanPoint::set_visible(bool is_visible){
    if (is_visible){
        setFillColor(fill_color);
        setColor(outline_color);
    } else {
        setFillColor(QColor("transparent"));
        setColor(QColor("transparent"));
    }
    m_visible = is_visible;
}



FlightPlan::FlightPlan(QgsMapCanvas *canvas)
    : QgsRubberBand(canvas),
      possible_line{new QgsRubberBand(canvas)},
      possible_point{new PlanPoint(canvas, {0,0})}
{
    cur_canvas = canvas;

    setColor(color);
    setLineStyle(drawed_style);
    setWidth(drawed_width);

    possible_line->setColor(color);
    possible_line->setLineStyle(possible_style);
    possible_line->setWidth(possible_width);

    possible_point->set_visible(false);
}

int FlightPlan::points_count(){
    return plan_points.size();
}

void FlightPlan::set_point_pos(int point_index, QgsPointXY new_pos){
    plan_points[point_index]->set_pos( new_pos );
    movePoint(point_index, new_pos);
    update();
}

void FlightPlan::set_point_pos_x(int point_index, double x){
    set_point_pos(point_index, QgsPointXY(x, plan_points[point_index]->get_pos().y()));
}

void FlightPlan::set_point_pos_y(int point_index, double y){
    set_point_pos(point_index, QgsPointXY(plan_points[point_index]->get_pos().x(), y));
}

QgsPointXY FlightPlan::get_point_pos(int point_index){
    return plan_points[point_index]->get_pos();
}

void FlightPlan::set_point_alt(int point_index, double alt){
    plan_points[point_index]->set_alt( alt );
}

double FlightPlan::get_point_alt(int point_index){
    return plan_points[point_index]->get_alt();
}

void FlightPlan::add_point(QgsPointXY pos){
    clear_possible_line();

    addPoint(pos);

    PlanPoint* point = new PlanPoint(cur_canvas, pos);
    plan_points.push_back(point);


    int n=points_count();
    table->setRowCount(n);

    QTableWidgetItem* pos_x = new QTableWidgetItem(QString::number(point->get_pos().y(), 'g', pos_precision));
    QTableWidgetItem* pos_y = new QTableWidgetItem(QString::number(point->get_pos().x(), 'g', pos_precision));
    QTableWidgetItem* alt   = new QTableWidgetItem(QString::number(point->get_alt(), 'g', alt_precision));

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

    delete plan_points[point_index];
    plan_points.removeAt(point_index);

    update();
}

void FlightPlan::update_possible_line(QgsPointXY pos){
    possible_point->set_visible(true);
    possible_point->set_pos( pos );

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
    possible_point->set_visible(false);
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

FlightPlan::~FlightPlan(){
    for (auto point : plan_points)
        delete point;

    delete possible_point;
    delete possible_line;
}
