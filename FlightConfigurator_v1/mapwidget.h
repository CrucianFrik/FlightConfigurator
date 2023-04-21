#ifndef MAPWIDGET_H
#define MAPWIDGET_H



#include <QAction>
#include <QTextStream>

#include <qgsmaptoolpan.h>
#include <qgsvectorlayer.h>

#include <mapbuttons.h>



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
    void enable_pan(bool is_enabled);
    void set_settings();

    QgsPointXY str_to_point(QString str);


    QgsRectangle full_zoom;

    QgsMapToolPan* tool_pan;

    SearchBar*        search_bar;
    CentralizeButton* center_button;
    ZoomInButton*     zoomin_button;
    ZoomOutButton*    zoomout_button;

    const double ZOOM_FACTOR_WHEEL = 1.3;
    const double ZOOM_FACTOR_MOVE  = 1e6;
    const bool ANTIALIASING  = true;
    const bool PREVIEW_JOBS  = true;
    const bool IS_PAN_ENABLE = true;

};



#endif // MAPWIDGET_H
