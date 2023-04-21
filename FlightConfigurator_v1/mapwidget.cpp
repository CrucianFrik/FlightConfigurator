#include "mapwidget.h"


MapWidget::MapWidget(const QList<QgsMapLayer*>& layers, QWidget* parent)
    : QgsMapCanvas(parent),
      tool_pan{new QgsMapToolPan(this)},
      search_bar{new SearchBar(this)}
{
    full_zoom = layers[0]->extent();

    setLayers(layers);
    centralize_slot();

    set_settings();

    center_button   = new CentralizeButton(this);
    zoomin_button   = new ZoomInButton(this);
    zoomout_button  = new ZoomOutButton(this);

    connect(search_bar,      SIGNAL(returnPressed()), SLOT(move_to_search_query_slot()));
    connect(center_button,   SIGNAL(clicked()),       SLOT(centralize_slot())          );
    connect(zoomin_button,   SIGNAL(clicked()),       SLOT(zoomIn())                   );
    connect(zoomout_button,  SIGNAL(clicked()),       SLOT(zoomOut())                  );
}


void MapWidget::set_settings(){
    setPreviewJobsEnabled(PREVIEW_JOBS);
    enableAntiAliasing(ANTIALIASING);
    setWheelFactor(ZOOM_FACTOR_WHEEL);
    enable_pan(IS_PAN_ENABLE);

//    setRenderFlag(true);
}


MapWidget::~MapWidget(){
    delete tool_pan;
    delete search_bar;
    delete center_button;
    delete zoomin_button;
    delete zoomout_button;
}


void MapWidget::move_to(QgsPointXY pos){
    setCenter(pos);
    refresh();
}


void MapWidget::move_to_with_zoom(QgsPointXY pos){
    zoomScale(ZOOM_FACTOR_MOVE);
    move_to(pos);
}


void MapWidget::move_to_search_query_slot(){
    QgsPointXY queried_pos = str_to_point(search_bar->get_query());
    move_to_with_zoom(queried_pos);
}


void MapWidget::centralize_slot(){
    setExtent(full_zoom);
    refresh();
}


QgsPointXY MapWidget::str_to_point(QString str){
    QTextStream stream(&str);
    double posx=center().x(), posy=center().y();
    stream >> posy >> posx;
    return {posx, posy};
}


void MapWidget::update_buttons_pos(){
    search_bar     ->update_pos(size());
    center_button  ->update_pos(size());
    zoomin_button  ->update_pos(size());
    zoomout_button ->update_pos(size());
}


void MapWidget::enable_pan(bool is_enabled){
    if (!IS_PAN_ENABLE) return;

    if (is_enabled){
        setMapTool(tool_pan);
    } else {
        unsetMapTool(tool_pan);
    }
}
