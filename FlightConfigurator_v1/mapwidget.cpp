#include "mapwidget.h"


MapWidget::MapWidget(const QList<QgsMapLayer*>& layers, QWidget* parent)
    : QgsMapCanvas(parent),
      tool_pan{new QgsMapToolPan(this)},
      search_bar{new SearchBar(this)},
      drone_marker{new DroneMarker(this)}
{
    full_zoom = layers[0]->extent();

    setExtent(full_zoom);
    setLayers(layers);
    set_settings();

    enable_pan(true);

    center_button   = new CentralizeButton(this, center_button_pos);
    zoomin_button   = new ZoomInButton(this, zoomin_button_pos);
    zoomout_button  = new ZoomOutButton(this, zoomout_button_pos);
    follow_checkbox = new FollowCheckbox(this, follow_checkbox_pos);

    connect(search_bar,      SIGNAL(returnPressed()), SLOT(move_to_search_query()));
    connect(center_button,   SIGNAL(clicked()),       SLOT(centralize())          );
    connect(zoomin_button,   SIGNAL(clicked()),       SLOT(zoomIn())              );
    connect(zoomout_button,  SIGNAL(clicked()),       SLOT(zoomOut())             );
    connect(follow_checkbox, SIGNAL(clicked()),       SLOT(change_focus())        );

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
    delete zoomin_button;
    delete zoomout_button;
    delete follow_checkbox;
    delete drone_marker;
}


void MapWidget::move_to(QgsPointXY pos){
    zoomScale(zoom_factor_move);
    setCenter(pos);
    refresh();
}


void MapWidget::move_to_search_query(){
    if (is_focused){
        change_focus();
        waitWhileRendering();
    }

    QgsPointXY pos = str_to_point(search_bar->get_query());
    move_to(pos);
}


void MapWidget::centralize(){
    if (is_focused){
        change_focus();
        waitWhileRendering();
    }

    setExtent(full_zoom);
    setCenter({0,0});
    refresh();
}


QgsPointXY MapWidget::str_to_point(QString str){
    QTextStream stream(&str);
    double posx=center().x(), posy=center().y();
    stream >> posx >> posy;
    return {posx, posy};
}


void MapWidget::update_buttons_pos(){
    center_button->update_pos(size());
    zoomin_button->update_pos(size());
    zoomout_button->update_pos(size());
    follow_checkbox->update_pos(size());
}


void MapWidget::update_drone_pos(QgsPointXY pos){
    drone_marker->update_pos(pos);

    if (is_focused){
        waitWhileRendering();
        move_to_drone_pos();
    }
}


void MapWidget::change_focus(){
    follow_checkbox->switch_icon();
    if (!is_focused){
        move_to(drone_marker->center());
    }
    enable_pan(is_focused);
    is_focused = !is_focused;
}


void MapWidget::enable_pan(bool is_enabled){
    if (is_enabled){
        setMapTool(tool_pan);
    } else {
        unsetMapTool(tool_pan);
    }
}


void MapWidget::move_to_drone_pos(){
    setCenter(drone_marker->center());
    refresh();
}


void MapWidget::wheelEvent(QWheelEvent *e){
    QgsMapCanvas::wheelEvent(e);

    if (is_focused){
        stopRendering();
        move_to_drone_pos();
    }
}
