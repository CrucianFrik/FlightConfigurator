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



CentralizeButton::CentralizeButton(QWidget *parent)
    : QPushButton(parent)
{
    resize(m_size);
    setIcon(QIcon( QDir(QDir::currentPath()).filePath(m_icon_path) ));
    setIconSize(m_icon_size);
}

void CentralizeButton::update_pos(QSize win_size){
    move(win_size.width()-m_size.width()-m_indent.x(),
         win_size.height()-m_size.height()-m_indent.y());
}



FocusSwitch::FocusSwitch(QWidget *parent)
    : QPushButton(parent),
      enable_icon{new QIcon(QDir(QDir::currentPath()).filePath(m_enable_icon_path))},
      disable_icon{new QIcon(QDir(QDir::currentPath()).filePath(m_disable_icon_path))}
{
    resize(m_size);
    setIcon(*disable_icon);
    setIconSize(m_icon_size);
}

void FocusSwitch::update_pos(QSize win_size){
    move(win_size.width()-m_size.width()-m_indent.x(),
         win_size.height()-m_size.height()-m_indent.y());
}

void FocusSwitch::chande_icon(){
    if (!is_enable) {
        setIcon(*enable_icon);
    } else {
        setIcon(*disable_icon);
    }
    update();
    is_enable = !is_enable;
}

FocusSwitch::~FocusSwitch(){
    delete enable_icon;
    delete disable_icon;
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
