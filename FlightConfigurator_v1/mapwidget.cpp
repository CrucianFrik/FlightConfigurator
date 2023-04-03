#include "mapwidget.h"


MapWidget::MapWidget(const QList<QgsMapLayer*>& layers)
    : QgsMapCanvas()
{
    for (auto layer: layers){
        setExtent(layer->extent());
    }
    setLayers(layers);

    auto action_pan = new QAction(QString("Pan"), this);
    action_pan->setCheckable(true);

    connect(action_pan, SIGNAL(triggered()), SLOT(pan()));

    tool_pan = new QgsMapToolPan(this);
    tool_pan->setAction(action_pan);

    pan();
}



MapWidget::~MapWidget(){
    delete tool_pan;
}
