#include <QApplication>
#include <QPainter>
#include <QEvent>
#include <cmath>

#include "CircleMark.h"

CircleMark::CircleMark(short radius, QWidget *parent)
: radius(radius),
  QWidget(parent)
{
    resize(2*radius + 5, 2*radius + 5);
}

void CircleMark::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setPen(QPen(QColor(0xd4d4d4), radius / 10));
    painter.drawEllipse(QPoint(this->width()/2, this->height()/2), radius, radius);

    painter.setPen(QPen(QColor(0x03f8fc) , radius / 10));
    painter.drawArc(this->width()/2 - radius, this->height()/2 - radius, 2 * radius, 2 * radius, 90 * 16 , -16 * 3.6 * percent);


    painter.setPen(QPen(QColor(0x0e7073), 1));
    painter.setBrush(QColor(0x1ac4c9));
    painter.drawEllipse(QPoint(  this->width()/2 + radius * sin(3.6 * percent / 180.0 * M_PI),
                                      this->height()/2 - radius * cos(3.6 * percent / 180.0 * M_PI)),radius / 8, radius / 8);


    painter.setPen(QPen(Qt::black, 2));
    painter.setFont(QFont("Arial", radius/1.5));
    painter.drawText(rect(), Qt::AlignCenter,QtPrivate::convertToQString(std::to_string(percent)));
}

void CircleMark::mousePressEvent(QMouseEvent * event)
{
    switch (event->button())
    {
        case Qt::LeftButton:
            if(percent != 100)
                ++percent;
            repaint();
            break;
        case Qt::RightButton:
            if(percent != 0)
                --percent;
            repaint();
            break;
    }
    QWidget::mousePressEvent(event);
}

void CircleMark::wheelEvent(QWheelEvent *event)
{

    {
        if(event->angleDelta().y() > 0)
        {
            if(percent != 100)
                ++percent;

            repaint();
        }
        else if(event->angleDelta().y() < 0)
        {
            if(percent != 0)
                --percent;

            repaint();
        }
    }

    QWidget::wheelEvent(event);
}

void CircleMark::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_Plus: case Qt::Key_Up:
            if(percent != 100)
                ++percent;
            repaint();
            break;

        case Qt::Key_Minus: case Qt::Key_Down:
            if(percent != 0)
                --percent;
            repaint();
            break;
    }
    QWidget::keyPressEvent(event);
}

void CircleMark::setRadius(short radius)
{ this->radius = radius; }

void CircleMark::enterEvent(QEnterEvent *event)
{
    setFocus();
    radius += 5;
    QWidget::enterEvent(event);
}

void CircleMark::leaveEvent(QEvent *event)
{
    radius -= 5;
    clearFocus();
    QWidget::leaveEvent(event);
}


