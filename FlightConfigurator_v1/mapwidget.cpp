#include "mapwidget.h"


MapWidget::MapWidget(const QList<QgsMapLayer*>& layers)
    : QgsMapCanvas(),
      search_bar{new SearchBar(this)}
{
    for (auto layer: layers){
        setExtent(layer->extent());
    }
    setLayers(layers);
    set_settings();

    auto action_pan = new QAction(QString("Pan"), this);
    action_pan->setCheckable(true);
    connect(action_pan, SIGNAL(triggered()), SLOT(pan()));

    connect(search_bar->get_button(), SIGNAL(clicked()), SLOT(move_to_search_query()));

    tool_pan = new QgsMapToolPan(this);
    tool_pan->setAction(action_pan);

    pan();
}


void MapWidget::set_settings(){
    setPreviewJobsEnabled(preview_jobs);
    enableAntiAliasing(antialiasing);
    setWheelFactor(zoom_factor_wheel);
//    setRenderFlag(true);
}


MapWidget::~MapWidget(){
    delete tool_pan;
    delete search_bar;
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


QgsPointXY MapWidget::str_to_point(QString str){
    QTextStream stream(&str);
    double posx=center().x(), posy=center().y();
    stream >> posx >> posy;
    qDebug() << posx << posy;
    return {posx, posy};
}





SearchBar::SearchBar(QWidget* parent)
    : QLineEdit(parent),
      search_button{new QPushButton(this)}
{
    resize(bar_size);
    move(bar_pos);
    setPlaceholderText(bar_prompt);

    search_button->resize( bar_size.width()*search_button_size.width(), bar_size.height()*search_button_size.height() );
    search_button->move( width()*search_button_pos.x(), height()*search_button_pos.y() );
    search_button->setText( search_button_label );
}


SearchBar::~SearchBar(){
    delete search_button;
}


QString SearchBar::get_query() const {
    return text();
}
