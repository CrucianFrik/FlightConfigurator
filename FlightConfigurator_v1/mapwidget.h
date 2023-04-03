#ifndef MAPWIDGET_H
#define MAPWIDGET_H


#include <QWidget>
#include <QAction>
#include <QInputDialog>

#include <qgsmapcanvas.h>
#include <qgsmaptoolpan.h>
#include <qgsvectorlayer.h>



class MapWidget : public QgsMapCanvas{
Q_OBJECT

public:
    MapWidget(const QList<QgsMapLayer*>& layers);

    ~MapWidget();

private slots:
    void pan(){ setMapTool(tool_pan); }

private:
    QgsMapToolPan* tool_pan;
};


#endif // MAPWIDGET_H
