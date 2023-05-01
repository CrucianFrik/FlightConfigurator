#ifndef PLANMAPWIDGET_H
#define PLANMAPWIDGET_H


#include <QMouseEvent>
#include <QTableWidget>

#include <qgsmapmouseevent.h>
#include <qgsrubberband.h>

#include "mapwidget.h"



const QString DELETE_ICON_PATH = "../../../icons/delete_icon.png";

enum {
    COLUMN_LAT,
    COLUMN_LON,
    COLUMN_ALT,
    COLUMN_DEL
};



class FlightPlan : protected QgsRubberBand {
Q_OBJECT

public:
    FlightPlan(QgsMapCanvas* canvas);

    void set_point_pos(int point_index, QgsPointXY new_pos);
    void set_point_pos_x(int point_index, double x);
    void set_point_pos_y(int point_index, double y);

    QgsPointXY get_point_pos(int point_index);

    void set_point_alt(int point_index, double alt);
    double get_point_alt(int point_index);

    void add_point(QgsPointXY pos);

    void delete_point(int point_index);

    int points_count();

    void update_possible_line(QgsPointXY pos);
    void clear_possible_line();

    void set_table(QTableWidget* t);

private slots:
    void update_point(int row, int column);
    void del_button_pressed();

private:
    QList<double> alts;
    const double default_alt = 0.0;

    QList<QgsPointXY> points;

    QgsRubberBand* possible_line;

    QTableWidget* table;

    const QBrush error_cell_color = QBrush(QColor(255, 0, 0));
    const QBrush default_cell_color = QBrush(QColor(255, 255, 255));

    const int pos_precision = 6;
    const int alt_precision = 2;

    QIcon delete_button_icon = QIcon( QDir(QDir::currentPath()).filePath(DELETE_ICON_PATH));

    const int drawed_width = 3;
    const int possible_width = 2;
    const QColor color = QColor(255, 0, 0);
    const Qt::PenStyle drawed_style = Qt::SolidLine;
    const Qt::PenStyle possible_style = Qt::DashLine;

};



class PlanMapWidget : public MapWidget {
Q_OBJECT

public:
    PlanMapWidget(const QList<QgsMapLayer*>& layers, QWidget* parent=nullptr);

    void set_table(QTableWidget* t);

    ~PlanMapWidget();

private:
    void mousePressEvent(QMouseEvent* e) override;
    void mouseMoveEvent(QMouseEvent* e) override;
    void mouseReleaseEvent(QMouseEvent* e) override;


    FlightPlan* flight_plan;

    bool is_plan_drawing = true;

    bool is_right_button_pressed = false;

    const int center_button_pos   = 1;
    const int zoomin_button_pos   = 3;
    const int zoomout_button_pos  = 2;

};



#endif // PLANMAPWIDGET_H
