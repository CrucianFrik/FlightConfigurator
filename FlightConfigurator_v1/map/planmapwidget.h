#ifndef PLANMAPWIDGET_H
#define PLANMAPWIDGET_H



#include <QMouseEvent>

#include <qgsrubberband.h>

#include "mapwidget.h"
#include "flightplan.h"



class PlanMapWidget : public MapWidget {
Q_OBJECT

public:
    PlanMapWidget(const QList<QgsMapLayer*>& layers, QWidget* parent=nullptr);

    void set_table(QTableWidget* t);

    void get_plan_points(QList<std::array<double, 3>>& arr);

    bool load_plan_to_file(const QString& path);
    bool load_plan_from_file(const QString& path);

    QString get_plan_file_format();

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
