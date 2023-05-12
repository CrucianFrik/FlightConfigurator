#include "flightplan.h"


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
    move_polygon_point(point_index, new_pos);
    move_adj_arrows(point_index);
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

    add_arrow();


    int n=points_count();
    table->setRowCount(n);

    QTableWidgetItem* pos_x = new QTableWidgetItem(QString::number(point->get_pos().y(), 'g', pos_precision + count_digits(point->get_pos().y())));
    QTableWidgetItem* pos_y = new QTableWidgetItem(QString::number(point->get_pos().x(), 'g', pos_precision + count_digits(point->get_pos().x())));
    QTableWidgetItem* alt   = new QTableWidgetItem(QString::number(point->get_alt(), 'g', alt_precision + count_digits(point->get_alt())));

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
    delete_arrow(point_index);
    delete_point_from_polygon(point_index);

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
            ( column == COLUMN_ALT ? alt_precision : pos_precision ) + count_digits(changed));
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

    for (auto arrow : plan_arrows)
        delete arrow;

    delete possible_point;
    delete possible_line;
}


void FlightPlan::delete_point_from_polygon(int point_index){
    removePoint(point_index);

    if (points_count() != 1 && point_index == points_count()-1){
        addPoint(plan_points[points_count()-2]->get_pos());
        removePoint(point_index);
    }
}


void FlightPlan::move_polygon_point(int point_index, QgsPointXY new_pos){
    movePoint(point_index, new_pos);

    if (points_count() != 1 && point_index == points_count()-1){
        addPoint(new_pos);
        removePoint(point_index+1);
    }
}


void FlightPlan::update_arrows_size(double extent_height, double extent_width){
    for (auto arrow : plan_arrows)
        arrow->update_size(extent_height, extent_width);

    last_extent_height = extent_height;
    last_extent_width  = extent_width;
}


void FlightPlan::add_arrow(){
    if (points_count() < 2) return;

    auto new_arrow = new PlanArrow(cur_canvas, plan_points[points_count() - 2]->get_pos(),
                                               plan_points[points_count() - 1]->get_pos(),
                                               last_extent_height, last_extent_width);
    plan_arrows.push_back( new_arrow );
}


void FlightPlan::move_adj_arrows(int point_index){
    if (point_index < points_count()-1){
        plan_arrows[point_index]->update_pos(plan_points[point_index]  ->get_pos(),
                                             plan_points[point_index+1]->get_pos());
    }
    if (point_index > 0){
        plan_arrows[point_index-1]->update_pos(plan_points[point_index-1]->get_pos(),
                                             plan_points[point_index]  ->get_pos());
    }
}


void FlightPlan::delete_arrow(int point_index){
    if (points_count() == 1) return;

    if (point_index == 0){
        delete plan_arrows[point_index];
        plan_arrows.removeAt(point_index);
    } else if (point_index == points_count()-1){
        delete plan_arrows[point_index-1];
        plan_arrows.removeAt(point_index-1);
    } else {
        plan_arrows[point_index]->update_pos( plan_points[point_index-1]->get_pos(),
                                              plan_points[point_index+1]->get_pos() );

        delete plan_arrows[point_index-1];
        plan_arrows.removeAt(point_index-1);
    }
}


void FlightPlan::get_points(QList<std::array<double, 3> >& arr){
    arr.reserve( points_count() );
    for (auto& point : plan_points){
        arr.push_back({point->get_pos().y(), point->get_pos().x(), point->get_alt()});
    }
}


bool FlightPlan::load_to_file(const QString &path){
    if (QFileInfo(path).suffix() != plan_format)
        return false;

    QString filepath = QFileInfo(path).absolutePath();
    QDir dir;
    if (!dir.exists(filepath))
        dir.mkpath(filepath);


    QFile file(path);

    if (file.open(QIODevice::WriteOnly)){
        QTextStream file_stream(&file);

        file_stream << comment_symbol << ' ' << file_prompt << '\n';

        for (auto& point : plan_points){
            file_stream << QString::number(point->get_pos().y(), 'g', 9) << ' ';
            file_stream << QString::number(point->get_pos().x(), 'g', 9) << ' ';
            file_stream << QString::number(point->get_alt(), 'g', 9) << '\n';
        }

        file.close();
    } else return false;

    return true;
}


bool FlightPlan::load_from_file(const QString &path){
    if (QFileInfo(path).suffix() != plan_format){

        return false;
    }

    QFile file(path);

    if (file.open(QIODevice::ReadOnly)){
        QTextStream file_stream(&file);

        clear();

        while (!file_stream.atEnd()){
            QString line = file_stream.readLine();

            if (line.startsWith(comment_symbol))
                continue;

            QTextStream line_stream(&line);

            double px=0, py=0, alt=0;
            line_stream >> py >> px >> alt;

            add_point(QgsPointXY(px,py));
            plan_points.back()->set_alt(alt);
        }

        file.close();
    } else return false;

    return true;
}


int FlightPlan::count_digits(int number){
    int res=0;
    number = abs(number);
    while (number > 0){
        number /= 10;
        ++res;
    }
    return res;
}


void FlightPlan::clear(){
    reset();

    for (auto point : plan_points)
        delete point;

    for (auto arrow : plan_arrows)
        delete arrow;

    plan_arrows.clear();
    plan_points.clear();

    table->setRowCount(0);
}


QString FlightPlan::get_plan_file_format(){
    return plan_format;
}
