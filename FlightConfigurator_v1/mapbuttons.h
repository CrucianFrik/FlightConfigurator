#ifndef MAPBUTTONS_H
#define MAPBUTTONS_H



#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QDir>
#include <QDebug>

#include <qgsmapcanvas.h>
#include <qgsvertexmarker.h>



const QSize button_size = {35, 35};
const QPoint button_indent = {10, 10};
const QPoint button_icon_indent = {8, 8};

const QString zoomin_icon_path = "../../icons/zoomin_icon.png";
const QString zoomout_icon_path = "../../icons/zoomout_icon.png";
const QString centralize_icon_path = "../../icons/centralize_icon.png";
const QString follow_icon_path = "../../icons/follow_icon.png";
const QString unfollow_icon_path = "../../icons/unfollow_icon.png";



class SearchBar : public QLineEdit{
Q_OBJECT

public:
    SearchBar(QWidget* parent=nullptr);

    QString get_query() const;

    ~SearchBar();

private:
    const QSize bar_size = {200, 30};
    const QPoint bar_pos = {7, 5};
    const QString bar_prompt = "Enter coordinates";

    QPushButton* search_button;
    const QSizeF search_button_size = {0.1, 0.8};
    const QPointF search_button_pos = {0.88, 0.1};
    const QString icon_path = "../../icons/search_icon.png";

};




class MapButton : public QPushButton {

public:
    void update_pos(QSize win_size);

    ~MapButton() = default;

protected:
    MapButton(QWidget* parent, int pos_number, const QString& icon_path);

private:
    QSize m_size = button_size;
    QSize m_icon_size = {m_size.width()-button_icon_indent.x(), m_size.height()-button_icon_indent.y()};
    QPoint m_pos;

};



class ZoomInButton : public MapButton {
Q_OBJECT
public:
    ZoomInButton(QWidget* parent, int pos_number)
        : MapButton(parent, pos_number, zoomin_icon_path) {}
};



class ZoomOutButton : public MapButton {
Q_OBJECT
public:
    ZoomOutButton(QWidget* parent, int pos_number)
        : MapButton(parent, pos_number, zoomout_icon_path) {}
};



class CentralizeButton : public MapButton {
Q_OBJECT
public:
    CentralizeButton(QWidget* parent, int pos_number)
        : MapButton(parent, pos_number, centralize_icon_path) {}
};




class MapCheckbox : public MapButton{

public:

    void switch_icon();

    ~MapCheckbox();

protected:
    MapCheckbox(QWidget* parent, int pos_number, const QString& enable_icon_path,
                const QString& disable_icon_path);

private:
    QIcon* m_enable_icon;
    QIcon* m_disable_icon;

    bool is_enable = false;

};



class FollowCheckbox : public MapCheckbox {
Q_OBJECT
public:
    FollowCheckbox(QWidget* parent, int pos_number)
        : MapCheckbox(parent, pos_number, follow_icon_path, unfollow_icon_path) {}
};




class DroneMarker : public QgsVertexMarker{

public:
    DroneMarker(QgsMapCanvas* canvas);

    void update_pos(QgsPointXY pos);
    void set_invisible(bool is_invisible);

    ~DroneMarker() = default;

private:
    QColor color = QColor(255, 0, 0);
    int size = 20;
    int icon_type = QgsVertexMarker::ICON_CIRCLE;

};



#endif // MAPBUTTONS_H
