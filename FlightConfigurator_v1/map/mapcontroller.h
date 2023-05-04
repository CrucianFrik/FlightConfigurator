#ifndef MAPCONTROLLER_H
#define MAPCONTROLLER_H



#include <QPair>

#include <qgsrasterlayer.h>

#include "datamapwidget.h"
#include "planmapwidget.h"



const QList< QPair<QString, QString> > MAP_LAYER_PATHS = {
     {"../../../maps/vector/kx-world-land-areas-110-million-SHP/world-land-areas-110-million.shp", "land"},
     {"../../../maps/vector/kx-world-bathymetry-110-million-SHP/world-bathymetry-110-million.shp", "bath"}
//         {"../../maps/vector/test/gis_osm_buildings_a_free_1.shp", "1"},
//         {"../../maps/vector/test/gis_osm_landuse_a_free_1.shp", "2"},
//         {"../../maps/vector/test/gis_osm_places_a_free_1.shp", "3"},
//         {"../../maps/vector/test/gis_osm_places_free_1.shp", "4"},
        };




class MapController{

public:
    MapController(QWidget* parent=nullptr);

    void load_layers();

    DataMapWidget* get_data_map();
    PlanMapWidget* get_plan_map();

    void update_maps_geometry();
    void update_drone_pos(QgsPointXY pos, double angle);

    ~MapController();

private:
    DataMapWidget* data_map;
    PlanMapWidget* plan_map;

    QList<QgsMapLayer*> layers;

    QgsPointXY drone_pos;

};


#endif // MAPCONTROLLER_H
