#ifndef PLANMAPWIDGET_H
#define PLANMAPWIDGET_H


#include <QMouseEvent>

#include <qgsmapmouseevent.h>
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

    void update_possible_line(QgsPointXY pos);
    void clear_possible_line();

private:
    QList<double> alts;
    const double default_alt = 0.0;

    QList<QgsPointXY> points;

    QgsRubberBand* possible_line;

    const int drawed_width = 3;
    const int possible_width = 2;
    const QColor color = QColor(255, 0, 0);
    const Qt::PenStyle drawed_style = Qt::SolidLine;
    const Qt::PenStyle possible_style = Qt::DashLine;

};



class PlanMapWidget : public MapWidget {
Q_OBJECT

public:
    PlanMapWidget(const QList<QgsMapLayer*>& layers, QWidget* parent=nullptr);

    ~PlanMapWidget();

private:
    void mousePressEvent(QMouseEvent* e) override;
    void mouseMoveEvent(QMouseEvent* e) override;
    void mouseReleaseEvent(QMouseEvent* e) override;


    FlightPlan* flight_plan;

    bool is_plan_drawing = true;

    bool is_right_button_pressed = false;

    const int center_button_pos   = 1;
    const int zoomin_button_pos   = 3;
    const int zoomout_button_pos  = 2;

};



#endif // PLANMAPWIDGET_H
