#ifndef PLANMAPWIDGET_H
#define PLANMAPWIDGET_H



#include <QMouseEvent>

#include <qgsmapmouseevent.h>
#include <qgsrubberband.h>

#include "mapwidget.h"
#include "flightplan.h"



class PlanMapWidget : public MapWidget {
Q_OBJECT

public:
    PlanMapWidget(const QList<QgsMapLayer*>& layers, QWidget* parent=nullptr);

    void set_table(QTableWidget* t);

    ~PlanMapWidget();

private slots:
    void update_arrows_size();

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
