#ifndef MAPWIDGET_H
#define MAPWIDGET_H


#include <QWidget>
#include <QAction>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>
#include <QTextStream>
#include <QDir>


#include <qgsmapcanvas.h>
#include <qgsmaptoolpan.h>
#include <qgsvectorlayer.h>
#include <qgsvertexmarker.h>


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
    const QSize button_size = {25, 25};
    const QPoint indent = {10, 10};
    const QString icon_path = "../../icons/centralize_icon.png";

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




class MapWidget : public QgsMapCanvas{
Q_OBJECT

public:
    MapWidget(const QList<QgsMapLayer*>& layers, QWidget* parent=nullptr);

    void move_to(QgsPointXY pos);

    void update_buttons_pos();

    void update_drone_pos(QgsPointXY pos);

    ~MapWidget();

private slots:
    void pan();
    void move_to_search_query();
    void centralize();

private:
    void set_settings();
    QgsPointXY str_to_point(QString str);

    QgsMapToolPan* tool_pan;

    SearchBar* search_bar;

    CentralizeButton* center_button;
    QgsRectangle full_zoom;

    DroneMarker* drone_marker;


    const double zoom_factor_wheel = 1.3;
    const double zoom_factor_move = 1e6;
    const bool antialiasing = true;
    const bool preview_jobs = true;

};



#endif // MAPWIDGET_H
