#include "mapcontroller.h"


MapController::MapController(QWidget *parent){
    load_layers();

    data_map = new DataMapWidget(layers, parent);
    plan_map = new PlanMapWidget(layers, parent);
}


void MapController::load_layers(){
    load_vector_world();
//    load_raster_world();
//    load_vector_moscow();
}


void MapController::load_vector_world(){
    for (auto& path : VECTOR_WORLD_PATHS){
        layers.push_back(new QgsVectorLayer( QDir(QDir::currentPath()).filePath(path), "shp" ));
    }
}

void MapController::load_raster_world(){
    for (auto& path : RASTER_WORLD_PATHS){
        layers.push_back(new QgsRasterLayer( QDir(QDir::currentPath()).filePath(path), "tif" ));
    }
}

void MapController::load_vector_moscow(){
    for (auto& path : VECTOR_MOSCOW_PATHS){
        layers.push_back(new QgsVectorLayer( QDir(QDir::currentPath()).filePath(path), "shp" ));
    }
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

    for (auto layer : layers)
        delete layer;
}


void MapController::update_maps_geometry(){
    data_map->update_buttons_pos();
    plan_map->update_buttons_pos();
}


void MapController::update_drone_pos(QgsPointXY pos, double angle){
    drone_pos = pos;

    data_map->update_drone_pos(pos, angle);
}


void MapController::get_plan_points(QList<std::array<double, 3>>& arr){
    plan_map->get_plan_points(arr);
}


bool MapController::load_plan_to_file(const QString &path){
    return plan_map->load_plan_to_file(path);
}


bool MapController::load_plan_from_file(const QString &path){
    return plan_map->load_plan_from_file(path);
}


QString MapController::get_plan_file_format(){
    return plan_map->get_plan_file_format();
}


void MapController::plan_reset(){
    plan_map->plan_reset();
}
