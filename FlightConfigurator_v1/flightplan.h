#ifndef FLIGHTPLAN_H
#define FLIGHTPLAN_H



#include <QTableWidget>

#include <qgsrubberband.h>

#include "mapwidget.h"



const QString DELETE_ICON_PATH = "../../icons/delete_icon.png";

enum {
    COLUMN_LAT,
    COLUMN_LON,
    COLUMN_ALT,
    COLUMN_DEL
};



class PlanPoint : protected QgsVertexMarker {

public:
    PlanPoint(QgsMapCanvas* canvas, QgsPointXY pos);

    void set_pos(QgsPointXY new_pos);
    QgsPointXY get_pos();

    void set_alt(double alt);
    double get_alt();

private:
    double alt;
    const double default_alt = 0.0;
    const QColor fill_color = QColor(255,0,0);
    const QColor outline_color = QColor(0,0,0);
    const int outline_width = 2;
    const int icon_size = 15;
    const IconType icon_type = ICON_CIRCLE;

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

    ~FlightPlan();

private slots:
    void update_point(int row, int column);
    void del_button_pressed();

private:
    QgsMapCanvas* cur_canvas;

    QList<PlanPoint*> plan_points;

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



#endif // FLIGHTPLAN_H
