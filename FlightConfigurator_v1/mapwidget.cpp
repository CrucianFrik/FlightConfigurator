#include "mapwidget.h"


MapWidget::MapWidget(const QList<QgsMapLayer*>& layers, QWidget* parent)
    : QgsMapCanvas(parent),
      tool_pan{new QgsMapToolPan(this)},
      search_bar{new SearchBar(this)},
      center_button{new CentralizeButton(this)},
      drone_marker{new DroneMarker(this)}
{
    full_zoom = layers[0]->extent();

    setExtent(full_zoom);
    setLayers(layers);
    set_settings();

    auto action_pan = new QAction(QString("Pan"), this);
    action_pan->setCheckable(true);
    connect(action_pan, SIGNAL(triggered()), SLOT(pan()));
    tool_pan->setAction(action_pan);
    pan();

    connect(search_bar, SIGNAL(returnPressed()), SLOT(move_to_search_query()));

    connect(center_button, SIGNAL(clicked()), SLOT(centralize()));

//    qDebug() << layers[0]->crs().description();
//    setDestinationCrs(layers[0]->crs());
//    qDebug() << mapSettings().destinationCrs().authid();

//    auto wgs84 = QgsCoordinateReferenceSystem("EPSG:4326");
//    qDebug() << wgs84.authid();
//    qDebug() << wgs84.description();
//    auto cur_crs = mapSettings().destinationCrs();
//    qDebug() << cur_crs.authid();
//    qDebug() << cur_crs.description();
//    auto transform_context = mapSettings().transformContext();
//    wgs84_to_cur = new QgsCoordinateTransform(wgs84, cur_crs, transform_context);
//    QgsPointXY test(55,37);
//    qDebug() << wgs84_to_cur->transform(test).x() << wgs84_to_cur->transform(test).y();
}


void MapWidget::set_settings(){
    setPreviewJobsEnabled(preview_jobs);
    enableAntiAliasing(antialiasing);
    setWheelFactor(zoom_factor_wheel);
//    setDestinationCrs(QgsCoordinateReferenceSystem("WGS84"));

//    setRenderFlag(true);
}


MapWidget::~MapWidget(){
    delete tool_pan;
    delete search_bar;
    delete center_button;
    delete drone_marker;
}


void MapWidget::move_to(QgsPointXY pos){
    zoomScale(zoom_factor_move);
    setCenter(pos);
    refresh();
}


void MapWidget::move_to_search_query(){
    QgsPointXY pos = str_to_point(search_bar->get_query());
    move_to(pos);
}


void MapWidget::centralize(){
    setCenter({0,0});
    setExtent(full_zoom);
    refresh();
}


void MapWidget::pan(){
    setMapTool(tool_pan);
}


QgsPointXY MapWidget::str_to_point(QString str){
    QTextStream stream(&str);
    double posx=center().x(), posy=center().y();
    stream >> posx >> posy;
    return {posx, posy};
}


void MapWidget::update_buttons_pos(){
    center_button->update_pos(size());
}


void MapWidget::update_drone_pos(QgsPointXY pos){
    drone_marker->update_pos(pos);
}




