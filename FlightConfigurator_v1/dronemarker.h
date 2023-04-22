#ifndef DRONEMARKER_H
#define DRONEMARKER_H


#include <QDebug>

#include <qgsvertexmarker.h>
#include <qgsmapcanvas.h>
#include <qgsrubberband.h>



class DroneTrack : protected QgsRubberBand {

public:
    DroneTrack(QgsMapCanvas* canvas);

    void push_point(QgsPointXY point);

private:
    const int line_width = 3;
    const QColor color = QColor(255, 0, 0);
    const Qt::PenStyle line_style = Qt::SolidLine;
    const int max_points_number = 100;

};



class DroneMarker : protected QgsVertexMarker{

public:
    DroneMarker(QgsMapCanvas* canvas);

    QgsPointXY pos();

    void update_pos(QgsPointXY pos);

    void set_invisible(bool is_invisible);

    ~DroneMarker();

private:
    DroneTrack* track;

    QColor color = QColor(255, 0, 0);
    int size = 20;
    int icon_type = QgsVertexMarker::ICON_CIRCLE;

};



#endif // DRONEMARKER_H
