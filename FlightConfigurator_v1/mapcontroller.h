#ifndef MAPCONTROLLER_H
#define MAPCONTROLLER_H



#include <QPair>

#include <qgsrasterlayer.h>

#include "mapwidget.h"



const QList< QPair<QString, QString> > map_layers_paths =
    {{"../../maps/vector/kx-world-land-areas-110-million-SHP/world-land-areas-110-million.shp", "land"},
     {"../../maps/vector/kx-world-bathymetry-110-million-SHP/world-bathymetry-110-million.shp", "bath"}};




class MapController{
public:
    MapController(QWidget* parent=nullptr);

    void load_layers();

    MapWidget* get_data_map();
    MapWidget* get_plan_map();

    void update_maps_geometry();
    void update_drone_pos(QgsPointXY pos);

    ~MapController();

private:
    MapWidget* data_map;
    MapWidget* plan_map;

    QList<QgsMapLayer*> layers;

    QgsPointXY drone_pos;

};


#endif // MAPCONTROLLER_H
