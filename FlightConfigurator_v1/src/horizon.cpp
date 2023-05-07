#include "horizon.h"

Aviagorizont_Viev::Aviagorizont_Viev(QWidget* parent){};

Aviagorizont_Viev::~Aviagorizont_Viev()
{
    delete _draw_label;
};

void Aviagorizont_Viev::set_label_name(QLabel* label)
{
    _draw_label = label;
    this->update(10,60);
};

void Aviagorizont_Viev::update(double pitch, double roll)
{
    _pitch = pitch;
    _roll = roll;
    this->update();
}

void Aviagorizont_Viev::update()
{
    QPixmap plane(":/horizon/plane_mock.png");
    QPixmap eath(":/horizon/horizon_line.png");
    QPixmap fone(":/horizon/black_back_ground.png");
    QPixmap markups(":/horizon/markups.png");
    QPixmap rotate(fone.size());
    

    QPainter p1(&rotate);
    p1.drawPixmap(0, 0, fone);
    
    p1.end();


    QPainter p2(&rotate);
    p2.drawPixmap(0, (_pitch)*(400/180)-200, eath);
    p2.drawPixmap(0, 0, markups);
    // p2.drawText( QPoint(200, 200), QString("%1").arg(_pitch));
    p2.end();
    

    QPainter p3(&rotate);
    p3.setRenderHint(QPainter::Antialiasing);
    p3.setRenderHint(QPainter::SmoothPixmapTransform);
    p3.setRenderHint(QPainter::HighQualityAntialiasing);

    p3.translate(fone.size().width() / 2, fone.size().height() / 2 );
    p3.rotate(_roll);
    p3.translate(-fone.size().width() / 2, -fone.size().height() / 2);

    p3.drawPixmap(0, 0, plane);
    p3.end();

    _draw_label->setPixmap(rotate);
}

