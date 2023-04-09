#ifndef MAPWIDGET_H
#define MAPWIDGET_H


#include <QWidget>
#include <QAction>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>
#include <QTextStream>

#include <qgsmapcanvas.h>
#include <qgsmaptoolpan.h>
#include <qgsvectorlayer.h>



class SearchBar : public QLineEdit{
Q_OBJECT

public:
    SearchBar(QWidget* parent=nullptr);

    QString get_query() const;

    ~SearchBar();

private:
    QSize bar_size = {200, 30};
    QPoint bar_pos = {7, 5};
    QString bar_prompt = "Enter coordinates";

    QPushButton* search_button;
    QSizeF search_button_size = {0.1, 0.8};
    QPointF search_button_pos = {0.88, 0.1};
    QString search_button_label = "🔎";

};




class MapWidget : public QgsMapCanvas{
Q_OBJECT

public:
    MapWidget(const QList<QgsMapLayer*>& layers, QWidget* parent=nullptr);

    void move_to(QgsPointXY pos);

    ~MapWidget();

private slots:
    void pan(){ setMapTool(tool_pan); }
    void move_to_search_query();
    void centralize();

private:
    void set_settings();
    QgsPointXY str_to_point(QString str);

    QgsMapToolPan* tool_pan;

    SearchBar* search_bar;
    QPushButton* center_button;
    QgsRectangle start_extent;

    const double zoom_factor_wheel = 1.3;
    const double zoom_factor_move = 1e6;
    const bool antialiasing = true;
    const bool preview_jobs = true;

    const QSize center_button_size = {30, 30};
    const QPoint center_button_pos = {10, 10};
    const QString center_button_label = "◼️";
};



#endif // MAPWIDGET_H
