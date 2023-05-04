#include "plan_attrs.h"

PlanPoint::PlanPoint(QgsMapCanvas *canvas, QgsPointXY pos)
    : QgsVertexMarker(canvas)
{
    alt = default_alt;
    cur_fill_color = low_color;

    setCenter(pos);
    setIconSize(icon_size);
    setPenWidth(outline_width);
    setIconType(icon_type);
    setColor(outline_color);

    update_color();
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

    update_color();
}

void PlanPoint::set_visible(bool is_visible){
    if (is_visible){
        setColor(outline_color);
        update_color();
    } else {
        setFillColor(QColor("transparent"));
        setColor(QColor("transparent"));
    }
    m_visible = is_visible;
}

void PlanPoint::update_color(){
    double delta_hue = double(high_color.hue() - low_color.hue()) / (max_alt - min_alt);
    double new_hue = double(low_color.hue()) + delta_hue * (alt - min_alt);

    new_hue = std::min(new_hue, 255.);
    new_hue = std::max(0., new_hue);

    cur_fill_color.setHsv(std::round(new_hue), low_color.saturation(), low_color.value());
    setFillColor(cur_fill_color);
}



PlanArrow::PlanArrow(QgsMapCanvas* canvas, QgsPointXY start_point, QgsPointXY end_point,
                     double extent_height, double extent_width)
    : QgsRubberBand(canvas)
{
    setColor(color);
    setFillColor(color);

    update_pos(start_point, end_point);
    update_size(extent_height, extent_width);
}

QgsPointXY PlanArrow::get_pos(){
    return pos;
}

void PlanArrow::update_pos(QgsPointXY start_point, QgsPointXY end_point){
    pos.setX( (start_point.x() + end_point.x()) * 0.5 );
    pos.setY( (start_point.y() + end_point.y()) * 0.5 );

    angle = atan2( end_point.y() - start_point.y(),
                   end_point.x() - start_point.x());
    angle -= M_PI_2;

    update_location();
}

void PlanArrow::update_location(){
    reset(QgsWkbTypes::PolygonGeometry);

    for (auto p : arrow_figure){
        double px = p.x()*cos(angle) - p.y()*sin(angle);
        double py = p.x()*sin(angle) + p.y()*cos(angle);

        addPoint({ pos.x() + px * size,
                   pos.y() + py * size });
    }
}

void PlanArrow::update_size(double extent_height, double extent_width){
    size = extent_height * win_height_to_size_koef;

    update_location();
}
