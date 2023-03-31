#include "mapwindow.h"

MapWindow::MapWindow(const QList<QgsMapLayer*>& layers){
    canvas = new QgsMapCanvas;
    for (auto layer: layers){
        canvas->setExtent(layer->extent());
    }
    canvas->setLayers(layers);

    setCentralWidget(canvas);

    auto action_pan = new QAction(QString("Pan"), this);
    action_pan->setCheckable(true);

    connect(action_pan, SIGNAL(triggered()), SLOT(pan()));

    tool_pan = new QgsMapToolPan(canvas);
    tool_pan->setAction(action_pan);

    pan();
}
