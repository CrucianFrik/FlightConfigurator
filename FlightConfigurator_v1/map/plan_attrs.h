#ifndef PLAN_ATTRS_H
#define PLAN_ATTRS_H



#include <QtMath>

#include <qgsvertexmarker.h>
#include <qgsrubberband.h>
#include <qgsmapcanvas.h>



const QString DELETE_ICON_PATH = ":/icons/delete_icon.png";



class PlanPoint : protected QgsVertexMarker {

public:
    PlanPoint(QgsMapCanvas* canvas, QgsPointXY pos);

    void set_pos(QgsPointXY new_pos);
    QgsPointXY get_pos();

    void set_alt(double alt);
    double get_alt();

    void set_visible(bool is_visible);

    void update_color();

private:
    double alt;
    QColor cur_fill_color;

    bool m_visible = true;

    const QColor low_color = QColor::fromHsv(120, 255, 255);
    const QColor high_color = QColor::fromHsv(0, 255, 255);
    const double min_alt = 10.;
    const double max_alt = 300.;

    const double default_alt = 50.;
    const QColor outline_color = QColor(0,0,0);
    const int outline_width = 2;
    const int icon_size = 15;
    const IconType icon_type = ICON_CIRCLE;

};



class PlanArrow : protected QgsRubberBand {

public:
    PlanArrow(QgsMapCanvas* canvas, QgsPointXY start_point, QgsPointXY end_point,
                double extent_height, double extent_width);

    QgsPointXY get_pos();

    void update_pos(QgsPointXY start_point, QgsPointXY end_point);

    void update_size(double extent_height, double extent_width);

private:
    void update_location();

    QgsPointXY pos;
    double size=0.1;
    double angle;
    const double win_height_to_size_koef = 1.0 / 100;

    QColor color = QColor(255, 0, 0);
    QList<QgsPointXY> arrow_figure = {{1,-1.5},{0,1.5},{-1,-1.5}};

};



#endif // PLAN_ATTRS_H
