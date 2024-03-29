#ifndef MAPWIDGET_H
#define MAPWIDGET_H



#include <QAction>
#include <QTextStream>
#include <QString>
#include <Qt>

#include <qgsmaptoolpan.h>
#include <qgsmapmouseevent.h>
#include <qgsvectorlayer.h>

#include "mapbuttons.h"



class MapWidget : public QgsMapCanvas{
Q_OBJECT

public:
    MapWidget(const QList<QgsMapLayer*>& layers, QWidget* parent=nullptr);

    void move_to(QgsPointXY pos);
    void move_to_with_zoom(QgsPointXY pos);

    virtual void update_buttons_pos();

    ~MapWidget();

protected slots:    
    virtual void move_to_search_query_slot();

    virtual void centralize_slot();

protected:
    virtual void mousePressEvent(QMouseEvent* e) override;
    virtual void mouseMoveEvent(QMouseEvent* e) override;

    void enable_pan(bool is_enabled);


    QgsRectangle full_zoom;

    QgsMapToolPan* tool_pan;

    SearchBar*          search_bar;
    CurrentCoordinates* cur_coords;
    CentralizeButton*   center_button;
    ZoomInButton*       zoomin_button;
    ZoomOutButton*      zoomout_button;

private:
    void set_settings();


    QgsVertexMarker* falt_point;

    QgsPointXY get_query(bool& is_correct);
    const QString query_sep = " ";

    const double ZOOM_FACTOR_WHEEL = 1.3;
    const double ZOOM_FACTOR_MOVE  = 2e3;
    const bool ANTIALIASING  = true;
    const bool PREVIEW_JOBS  = true;
    const bool IS_PAN_ENABLE = true;

};



#endif // MAPWIDGET_H
