#include "dronemarker.h"


DroneTrack::DroneTrack(QgsMapCanvas *canvas)
    : QgsRubberBand(canvas)
{
    setColor(color);
    setLineStyle(line_style);
    setWidth(line_width);
}

void DroneTrack::push_point(QgsPointXY point){
    addPoint(point);

    if (numberOfVertices() > max_points_number){
        removePoint(0);
    }
}



DroneMarker::DroneMarker(QgsMapCanvas *canvas)
    : QgsRubberBand(canvas),
      track{new DroneTrack(canvas)}
{
    setColor(color);
    setFillColor(color);

    for (int i=plane_figure.size()-2; i>0; i--){
        plane_figure.push_back( {-plane_figure[i].x(), plane_figure[i].y()} );
    }

    plane_figure.push_back(plane_figure[0]);
}

QgsPointXY DroneMarker::get_pos(){
    return pos;
}

void DroneMarker::set_location(QgsPointXY new_pos, double new_angle){
    pos = new_pos;
    angle = new_angle;

    update_location();

    track->push_point(pos);
}

void DroneMarker::update_location(){
    reset(QgsWkbTypes::PolygonGeometry);
    for (auto i : plane_figure){
        double px = i.x()*cos(angle) - i.y()*sin(angle);
        double py = i.x()*sin(angle) + i.y()*cos(angle);

        addPoint({ pos.x() + px * size,
                   pos.y() + py * size });
    }
}

void DroneMarker::set_size(double new_size){
    size = new_size;
    update_location();
}

DroneMarker::~DroneMarker(){
    delete track;
}

void DroneMarker::update_size(double extent_height, double extent_width){
    set_size( extent_height * win_height_to_size_koef );
}
