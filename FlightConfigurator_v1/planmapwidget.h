#ifndef PLANMAPWIDGET_H
#define PLANMAPWIDGET_H



#include <qgsrubberband.h>

#include "mapwidget.h"



class FlightPlan : protected QgsRubberBand {

public:
    FlightPlan(QgsMapCanvas* canvas);

    void set_point_pos(int point_index, QgsPointXY new_pos);
    QgsPointXY get_point_pos(int point_index);

    void set_point_alt(int point_index, double alt);
    double get_point_alt(int point_index);

    void add_point(QgsPointXY pos);

    void delete_point(int point_index);

    int points_count();

private:
    QList<double> alts;
    const double default_alt = 0.0;

    const int line_width = 3;
    const QColor color = QColor(255, 0, 0);
    const Qt::PenStyle line_style = Qt::SolidLine;

};



class PlanMapWidget : public MapWidget {
Q_OBJECT

public:
    PlanMapWidget(const QList<QgsMapLayer*>& layers, QWidget* parent=nullptr);

    ~PlanMapWidget();

private:
    FlightPlan* flight_plan;

    const int center_button_pos   = 1;
    const int zoomin_button_pos   = 3;
    const int zoomout_button_pos  = 2;

};



#endif // PLANMAPWIDGET_H
