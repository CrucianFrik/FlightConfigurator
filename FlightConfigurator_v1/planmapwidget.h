#ifndef PLANMAPWIDGET_H
#define PLANMAPWIDGET_H



#include "mapwidget.h"


class PlanMapWidget : public MapWidget {
Q_OBJECT

public:
    PlanMapWidget(const QList<QgsMapLayer*>& layers, QWidget* parent=nullptr);

private:
    const int center_button_pos   = 1;
    const int zoomin_button_pos   = 3;
    const int zoomout_button_pos  = 2;

};



#endif // PLANMAPWIDGET_H
