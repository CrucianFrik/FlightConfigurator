#ifndef MAPCONTROLLER_H
#define MAPCONTROLLER_H



#include <QPair>

#include <qgsrasterlayer.h>
#include <qgssinglesymbolrenderer.h>

#include "datamapwidget.h"
#include "planmapwidget.h"



const QList< QString >  VECTOR_WORLD_PATHS = { "../../../maps/vector_world/water.shp",
                                               "../../../maps/vector_world/land.shp" };

const QList< QString > RASTER_WORLD_PATHS =  { "../../../maps/raster_world/worldmap.tif" };

const QList< QString > VECTOR_MOSCOW_PATHS = {  "../../../maps/vector_moscow/natural.shp",
                                                "../../../maps/vector_moscow/pofw.shp",
                                                "../../../maps/vector_moscow/water.shp",
                                                "../../../maps/vector_moscow/buildings.shp",
                                                "../../../maps/vector_moscow/pois.shp",
                                                "../../../maps/vector_moscow/land.shp",
                                                "../../../maps/vector_moscow/places.shp" };



class MapController{

public:
    MapController(QWidget* parent=nullptr);

    void get_plan_points(QList<std::array<double, 3>>& arr);

    bool load_plan_to_file(const QString& path);
    bool load_plan_from_file(const QString& path);

    QString get_plan_file_format();

    DataMapWidget* get_data_map();
    PlanMapWidget* get_plan_map();

    void update_maps_geometry();
    void update_drone_pos(QgsPointXY pos, double angle);

    void plan_reset();

    ~MapController();

private:
    void load_layers();
    void load_vector_world();
    void load_raster_world();
    void load_vector_moscow();

    DataMapWidget* data_map;
    PlanMapWidget* plan_map;

    QList<QgsMapLayer*> layers;

    QgsPointXY drone_pos;

};


#endif // MAPCONTROLLER_H
