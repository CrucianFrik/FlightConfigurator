#ifndef HORIZON_H
#define HORIZON_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QPainter>

class Aviagorizont_Viev : public QWidget{
     Q_OBJECT
public:
    explicit Aviagorizont_Viev(QWidget* parent=nullptr);
    ~Aviagorizont_Viev();

    void set_label_name(QLabel* label);

    void update();
    void update(double pitch, double roll);

private:
    double _pitch = 0.0;
    double _roll  = 0.0;
    QLabel* _draw_label;
};

#endif // HORIZON_H