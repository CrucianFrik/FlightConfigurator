#include "mapbuttons.h"


SearchBar::SearchBar(QWidget* parent)
    : QLineEdit(parent),
      search_button{new QPushButton(this)}
{
    resize(BAR_SIZE);
    setPlaceholderText(BAR_PROMPT);

    search_button->resize( BAR_SIZE.width()*SEARCH_BUTTON_SIZE.width(),
                           BAR_SIZE.height()*SEARCH_BUTTON_SIZE.height() );
    search_button->move( width() * SEARCH_BUTTON_POS.x(),
                        height() * SEARCH_BUTTON_POS.y() );
    search_button->setIcon(QIcon( QDir(QDir::currentPath()).filePath(SEARCH_ICON_PATH) ));

    connect(search_button, SIGNAL(pressed()), this, SIGNAL(returnPressed()));
}

SearchBar::~SearchBar(){
    delete search_button;
}

QString SearchBar::get_query() const {
    return text();
}

void SearchBar::update_pos(QSize win_size){
    move(BAR_POS);
}



MapButton::MapButton(QWidget* parent, const QString& icon_path)
    : QPushButton(parent)
{
    setIcon(QIcon( QDir(QDir::currentPath()).filePath(icon_path) ));
    setIconSize(m_icon_size);

    resize(m_size);
}

void MapButton::update_pos(QSize win_size){
    move(win_size.width() - m_pos.x(),
         win_size.height() - m_pos.y());
}

void MapButton::set_pos_number(int pos_number){
    m_pos = {(BUTTON_INDENT.x() + m_size.width()) * pos_number,
              BUTTON_INDENT.y() + m_size.height()};
}



MapCheckbox::MapCheckbox(QWidget* parent, const QString& enable_icon_path,
                         const QString& disable_icon_path)
    : MapButton(parent, disable_icon_path),
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
