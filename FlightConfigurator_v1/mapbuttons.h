#ifndef MAPBUTTONS_H
#define MAPBUTTONS_H



#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QDir>
#include <QDebug>

#include <qgsmapcanvas.h>
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



#endif // MAPBUTTONS_H
