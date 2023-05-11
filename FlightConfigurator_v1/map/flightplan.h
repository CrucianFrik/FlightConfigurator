#ifndef FLIGHTPLAN_H
#define FLIGHTPLAN_H



#include <QTableWidget>
#include <cmath>
#include <array>

#include <qgsrubberband.h>

#include "mapwidget.h"
#include "plan_attrs.h"



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

    void update_arrows_size(double extent_height, double extent_width);

    void clear();

    // fills given array with (LAT LON ALT)
    void get_points(QList<std::array<double, 3>>& arr);

    // returns true if wrote
    // path - absolute path to file
    // creates dirs and file if not exists
    // works only with {get_plan_file_format()} extention
    bool load_to_file(const QString& path);

    // returns true if read
    // path - absolute path to file
    // works only with {get_plan_file_format()} extention
    bool load_from_file(const QString& path);

    QString get_plan_file_format();

    ~FlightPlan();

private slots:
    void update_point(int row, int column);
    void del_button_pressed();

private:
    int count_digits(int number);

    void delete_point_from_polygon(int point_index);
    void move_polygon_point(int point_index, QgsPointXY new_pos);

    void add_arrow();
    void move_adj_arrows(int point_index);
    void delete_arrow(int point_index);


    QgsMapCanvas* cur_canvas;

    QList<PlanPoint*> plan_points;
    QList<PlanArrow*> plan_arrows;

    QgsRubberBand* possible_line;
    PlanPoint* possible_point;

    QTableWidget* table;

    double last_extent_height;
    double last_extent_width;

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

    const QString plan_format = "flyplan";
    const QString file_prompt = "LAT | LON | ALT";
    const QString comment_symbol = "#";

};



#endif // FLIGHTPLAN_H
