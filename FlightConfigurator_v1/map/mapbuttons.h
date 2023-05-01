#ifndef MAPBUTTONS_H
#define MAPBUTTONS_H



#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QDir>
#include <QDebug>

#include <qgsmapcanvas.h>
#include <qgsvertexmarker.h>



const QSize BUTTON_SIZE = {35, 35};
const QPoint BUTTON_INDENT = {10, 10};
const QPoint BUTTON_ICON_INDENT = {8, 8};

const QString ZOOMIN_ICON_PATH = "../../../icons/zoomin_icon.png";
const QString ZOOMOUT_ICON_PATH = "../../../icons/zoomout_icon.png";
const QString CENTRALIZE_ICON_PATH = "../../../icons/centralize_icon.png";
const QString FOLLOW_ICON_PATH = "../../../icons/follow_icon.png";
const QString UNFOLLOW_ICON_PATH = "../../../icons/unfollow_icon.png";
const QString SEARCH_ICON_PATH = "../../../icons/search_icon.png";



class SearchBar : public QLineEdit {
Q_OBJECT

public:
    SearchBar(QWidget* parent=nullptr);

    QString get_query() const;
    void update_pos(QSize win_size);

    ~SearchBar();

private:
    const QSize BAR_SIZE = {200, 30};
    const QPoint BAR_POS = {7, 5};
    const QString BAR_PROMPT = "Enter coordinates";

    QPushButton* search_button;
    const QSizeF SEARCH_BUTTON_SIZE = {0.1, 0.8};
    const QPointF SEARCH_BUTTON_POS = {0.88, 0.1};

};




class MapButton : public QPushButton {

public:
    void update_pos(QSize win_size);
    void set_pos_number(int pos_number);

    ~MapButton() = default;

protected:
    MapButton(QWidget* parent, const QString& icon_path);

private:
    QSize m_size = BUTTON_SIZE;
    QSize m_icon_size = {m_size.width()-BUTTON_ICON_INDENT.x(), m_size.height()-BUTTON_ICON_INDENT.y()};
    QPoint m_pos;

};



class ZoomInButton : public MapButton {
Q_OBJECT
public:
    ZoomInButton(QWidget* parent)
        : MapButton(parent, ZOOMIN_ICON_PATH) {}
};



class ZoomOutButton : public MapButton {
Q_OBJECT
public:
    ZoomOutButton(QWidget* parent)
        : MapButton(parent, ZOOMOUT_ICON_PATH) {}
};



class CentralizeButton : public MapButton {
Q_OBJECT
public:
    CentralizeButton(QWidget* parent)
        : MapButton(parent, CENTRALIZE_ICON_PATH) {}
};




class MapCheckbox : public MapButton{

public:
    void switch_icon();

    ~MapCheckbox();

protected:
    MapCheckbox(QWidget* parent, const QString& enable_icon_path,
                const QString& disable_icon_path);

private:
    QIcon* m_enable_icon;
    QIcon* m_disable_icon;

    bool is_enable = false;

};



class FollowCheckbox : public MapCheckbox {
Q_OBJECT
public:
    FollowCheckbox(QWidget* parent)
        : MapCheckbox(parent, FOLLOW_ICON_PATH, UNFOLLOW_ICON_PATH) {}
};



#endif // MAPBUTTONS_H
