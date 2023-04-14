#ifndef MAPBUTTONS_H
#define MAPBUTTONS_H



#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QDir>
#include <QDebug>
#include <QCheckBox>

#include <qgsmapcanvas.h>
#include <qgsvertexmarker.h>



const QSize button_size = {35, 35};
const QPoint button_indent = {10, 10};
const QPoint button_icon_indent = {4, 4};



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



class CentralizeButton : public QPushButton{
Q_OBJECT

public:
    CentralizeButton(QWidget* parent=nullptr);

    void update_pos(QSize win_size);

    ~CentralizeButton() = default;

private:
    const QSize m_size = button_size;
    const QPoint m_indent = {2*button_indent.x()+button_size.width(), button_indent.y()};
    const QString m_icon_path = "../../icons/centralize_icon.png";
    const QSize m_icon_size = {m_size.width()-2*button_icon_indent.x(), m_size.height()-2*button_icon_indent.y()};

};



class FocusSwitch: public QPushButton {
Q_OBJECT

public:
    FocusSwitch(QWidget* parent=nullptr);

    void update_pos(QSize win_size);
    void chande_icon();

    ~FocusSwitch();

private:
    const QSize m_size = button_size;
    const QPoint m_indent = button_indent;
    const QString m_enable_icon_path = "../../icons/focus_icon.png";
    const QString m_disable_icon_path = "../../icons/unfocus_icon.png";
    const QSize m_icon_size = {m_size.width()-button_icon_indent.x(), m_size.height()-button_icon_indent.y()};

    bool is_enable=false;

    QIcon* enable_icon;
    QIcon* disable_icon;
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
