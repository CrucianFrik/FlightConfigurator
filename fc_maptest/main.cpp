#include <stdlib.h>
#include <iostream>
#include <QDir>
#include <QDebug>
#include <QPair>

#include <qgsapplication.h>

#include "mapwindow.h"


int main(int argc, char *argv[]) {
    QgsApplication app(argc, argv,true);

    QList< QPair<QString, QString> > layers_paths = {{"../maps/kx-world-land-areas-110-million-SHP/world-land-areas-110-million.shp", "land"},
                                                     {"../maps/kx-world-bathymetry-110-million-SHP/world-bathymetry-110-million.shp", "bath"}};

    QList<QgsMapLayer*> layers;
    for (auto& path : layers_paths){
        layers.push_back(new QgsVectorLayer( QDir(QDir::currentPath()).filePath(path.first), path.second, "ogr" ));
    }

    MapWindow wnd(layers);
    wnd.show();

    return app.exec();
}
