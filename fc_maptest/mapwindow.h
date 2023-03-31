#ifndef MAPWINDOW_H
#define MAPWINDOW_H


#include <QMainWindow>
#include <QAction>

#include <qgsmapcanvas.h>
#include <qgsmaptoolpan.h>
#include <qgsvectorlayer.h>



class MapWindow : public QMainWindow {
Q_OBJECT

public:
    MapWindow(const QList<QgsMapLayer*>& layers);

    ~MapWindow() = default;

private slots:
    void pan(){ canvas->setMapTool(tool_pan); }

private:
    QgsMapCanvas* canvas;

    QgsMapToolPan* tool_pan;

};

#endif // MAPWINDOW_H
