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
    : QgsVertexMarker(canvas),
      track{new DroneTrack(canvas)}
{
    setFillColor(color);
    setIconSize(size);
    setIconType(icon_type);
}

void DroneMarker::update_pos(QgsPointXY pos){
    setCenter(pos);
    track->push_point(pos);
    updatePosition();
}

void DroneMarker::set_invisible(bool is_invisible){
    if (is_invisible){
        setIconSize(0);
    } else {
        setIconSize(size);
    }
}

DroneMarker::~DroneMarker(){
    delete track;
}

QgsPointXY DroneMarker::pos(){
    return center();
}
