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
    const int max_points_number = 300;

};



class DroneMarker : protected QgsRubberBand {

public:
    DroneMarker(QgsMapCanvas* canvas);

    QgsPointXY get_pos();

    void set_location(QgsPointXY new_pos, double new_angle);

    void update_size(double extent_height, double extent_width);

    void set_size(double new_size);

    ~DroneMarker();

private:
    void update_location();

    QgsPointXY pos;
    double size=0.1;
    double angle;
    const double win_height_to_size_koef = 1.0 / 60;

    DroneTrack* track;

    QColor color = QColor(255, 0, 0);
    QList<QgsPointXY> plane_figure = {{0,-2.4},{1,-2.5},{1,-1.8},{0.5,-1.6},{0.5,-0.5},{2,-1},{2,-0.2},{1.9,0},{1.7,0.15},
                                      {0.6,0.5},{0.52,0.67},{0.5,1.5},{0.41,2.0},{0.19,2.4},{0,2.47}};

};



#endif // DRONEMARKER_H
