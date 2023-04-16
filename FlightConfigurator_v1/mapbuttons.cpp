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


MapButton::MapButton(QWidget* parent, int pos_number, const QString& icon_path)
    : QPushButton(parent)
{
    setIcon(QIcon( QDir(QDir::currentPath()).filePath(icon_path) ));
    setIconSize(m_icon_size);

    resize(m_size);
    m_pos = {pos_number * (button_indent.x() + m_size.width()), button_indent.y() + m_size.height()};
}

void MapButton::update_pos(QSize win_size){
    move(win_size.width() - m_pos.x(),
         win_size.height() - m_pos.y());
}



MapCheckbox::MapCheckbox(QWidget* parent, int pos_number, const QString& enable_icon_path,
                         const QString& disable_icon_path)
    : MapButton(parent, pos_number, disable_icon_path),
      m_enable_icon{new QIcon(enable_icon_path)},
      m_disable_icon{new QIcon(disable_icon_path)}
{ }

void MapCheckbox::switch_icon(){
    is_enable = !is_enable;
    if (is_enable) {
        setIcon(*m_enable_icon);
    } else {
        setIcon(*m_disable_icon);
    }
    update();
}

MapCheckbox::~MapCheckbox(){
    delete m_enable_icon;
    delete m_disable_icon;
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
