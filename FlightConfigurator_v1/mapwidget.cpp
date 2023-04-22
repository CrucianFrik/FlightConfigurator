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
    bool is_query_correct = false;
    QgsPointXY queried_pos = get_query( is_query_correct );

    if (is_query_correct){
        move_to_with_zoom(queried_pos);
    }
}


void MapWidget::centralize_slot(){
    setExtent(full_zoom);
    refresh();
}


QgsPointXY MapWidget::get_query(bool &is_correct){
    QString query_str = search_bar->get_query();
    QStringList query_str_parts = query_str.split(query_sep, QString::SkipEmptyParts);

    bool is_y_double = false;
    bool is_x_double = false;
    double pos_y = query_str_parts[0].toDouble( &is_y_double );
    double pos_x = query_str_parts[1].toDouble( &is_x_double );

    if (query_str_parts.size() != 2 || !is_y_double || !is_x_double){
        qDebug() << "Incorrect coordinates";
        is_correct = false;
        return {0, 0};
    }

    is_correct = true;
    return {pos_x, pos_y};
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

void MapWidget::mousePressEvent(QMouseEvent *e){
    if (e->button() != Qt::RightButton){
        QgsMapCanvas::mousePressEvent(e);
    }
}
