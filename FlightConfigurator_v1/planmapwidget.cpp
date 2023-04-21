#include "planmapwidget.h"


PlanMapWidget::PlanMapWidget(const QList<QgsMapLayer *> &layers, QWidget *parent)
    : MapWidget(layers, parent)
{
    center_button  ->set_pos_number(center_button_pos);
    zoomin_button  ->set_pos_number(zoomin_button_pos);
    zoomout_button ->set_pos_number(zoomout_button_pos);
}
