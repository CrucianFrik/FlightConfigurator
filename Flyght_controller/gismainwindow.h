#ifndef GIS_GUI_GISMAINWINDOW_H
#define GIS_GUI_GISMAINWINDOW_H

#include <QMainWindow>
//#include "widgets/menu/MenuController.h"
//#include "widgets/map/GISMapContoller.h"
//#include "database/DatabaseController.h"


namespace gisUI {
    class GISMainWindow : public QMainWindow {
    Q_OBJECT
    public:
        explicit GISMainWindow(QWidget *parent = nullptr);

        ~GISMainWindow() = default;

    private:
//        MenuController* menuController;
        QToolBar* toolBar;
//        GISMapContoller* mapController;
//        DatabaseController* dbController;

    };
}

#endif //GIS_GUI_GISMAINWINDOW_H
