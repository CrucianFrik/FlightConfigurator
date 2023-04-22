#ifndef DRONEMARKER_H
#define DRONEMARKER_H


#include <QDebug>
#include <QtMath>

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



class DroneMarker : protected QgsRubberBand {

public:
    DroneMarker(QgsMapCanvas* canvas);

    QgsPointXY get_pos();

    void set_location(QgsPointXY new_pos, double new_angle);

    void set_size(double new_size);

    ~DroneMarker();

private:
    void update_location();

    QgsPointXY pos;
    double size=0.1;
    double angle;

    DroneTrack* track;

    QColor color = QColor(255, 0, 0);
    QList<QgsPointXY> plane_figure = {{0,2}, {1,-1}, {-1,-1}};

};



#endif // DRONEMARKER_H
