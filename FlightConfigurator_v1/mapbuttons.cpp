#include "mapbuttons.h"


SearchBar::SearchBar(QWidget* parent)
    : QLineEdit(parent),
      search_button{new QPushButton(this)}
{
    resize(bar_size);
    move(bar_pos);
    setPlaceholderText(bar_prompt);

    search_button->resize( bar_size.width()*search_button_size.width(), bar_size.height()*search_button_size.height() );
    search_button->move( width()*search_button_pos.x(), height()*search_button_pos.y() );
    search_button->setIcon(QIcon( QDir(QDir::currentPath()).filePath(icon_path) ));

    connect(search_button, SIGNAL(pressed()), this, SIGNAL(returnPressed()));
}

SearchBar::~SearchBar(){
    delete search_button;
}

QString SearchBar::get_query() const {
    return text();
}



DroneMarker::DroneMarker(QgsMapCanvas *canvas)
    : QgsVertexMarker(canvas)
{
    setFillColor(color);
    setIconSize(size);
    setIconType(icon_type);
}

void DroneMarker::update_pos(QgsPointXY pos){
    setCenter(pos);
    updatePosition();
}

void DroneMarker::set_invisible(bool is_invisible){
    if (is_invisible){
        setIconSize(0);
    } else {
        setIconSize(size);
    }
}



CentralizeButton::CentralizeButton(QWidget *parent)
    : QPushButton(parent)
{
    resize(button_size);
    setIcon(QIcon( QDir(QDir::currentPath()).filePath(icon_path) ));
}

void CentralizeButton::update_pos(QSize win_size){
    move(win_size.width()-button_size.width()-indent.x(),
         win_size.height()-button_size.height()-indent.y());
}
