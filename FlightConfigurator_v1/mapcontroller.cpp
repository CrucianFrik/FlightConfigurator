#include "mapcontroller.h"


MapController::MapController(QWidget *parent){
    load_layers();

    data_map = new DataMapWidget(layers, parent);
    plan_map = new PlanMapWidget(layers, parent);
}


void MapController::load_layers(){
    for (auto& path : MAP_LAYER_PATHS) layers.push_back(new QgsVectorLayer( QDir(QDir::currentPath()).filePath(path.first), path.second, "ogr" ));
//    layers.push_back(new QgsRasterLayer("/home/k7ps/QtProjects/FlightConfigurator/maps/raster/worldmap.tif","tif"));
}


DataMapWidget* MapController::get_data_map(){
    return data_map;
}


PlanMapWidget* MapController::get_plan_map(){
    return plan_map;
}


MapController::~MapController(){
    delete data_map;
    delete plan_map;
}


void MapController::update_maps_geometry(){
    data_map->update_buttons_pos();
    plan_map->update_buttons_pos();
}


void MapController::update_drone_pos(QgsPointXY pos){
    drone_pos = pos;

    data_map->update_drone_pos(pos);
}
