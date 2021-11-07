#include <QApplication>
#include <QPainter>
#include <cmath>
#include <QStyle>

#include "CircleMark.h"

CircleMark::CircleMark(short radius, QWidget *parent)
: QWidget(parent),
  radius(radius)
{
    resize(2*radius + 5, 2*radius + 5);
    btn_plus = new QPushButton("+", this);
    btn_minus = new QPushButton("-", this);

    connect(btn_minus, &QPushButton::pressed, this, &CircleMark::dec);
    connect(btn_plus, &QPushButton::pressed, this, &CircleMark::inc);
}

void CircleMark::paintEvent([[maybe_unused]] QPaintEvent *)
{
    QPainter painter(this);

    // Draw indicator background
    painter.setPen(QPen(QColor(indctr_bg_clr), radius / 10));
    painter.drawArc(this->width()/2 - radius, this->height()/2 - radius,
                    2 * radius, 2 * radius,
                    begin_angle * arc_coeff, -end_angle * arc_coeff);

    // Draw fill indicator
    painter.setPen(QPen(QColor(indctr_fill_clr), radius / 10));
    painter.drawArc(this->width()/2 - radius, this->height()/2 - radius,
                    2 * radius, 2 * radius,
                    begin_angle * arc_coeff, -fillAngle() * arc_coeff);

    // Draw indicator mark
    const double fill_angle = angleToRad(fillAngle() - (begin_angle - 90));
    painter.setPen(QPen(QColor(mark_clr), 1));
    painter.setBrush(QColor(mark_fill_clr));
    painter.drawEllipse(QPoint(this->width()/2 + radius * sin(fill_angle),
                               this->height()/2 - radius * cos(fill_angle)),
                        radius / 8, radius / 8);

    // Draw filling text
    painter.setPen(QPen(Qt::black, 2));
    painter.setFont(QFont("Arial", radius / 2));
    std::string fillingText = std::to_string(static_cast<double>(filling) / divider);
    if(divider == 1)
        fillingText.erase(fillingText.find('.'));
    else
        fillingText.erase(fillingText.find('.') + 1 + precision);
    painter.drawText(rect(),
                     Qt::AlignCenter,
                     QtPrivate::convertToQString(fillingText) );

    // Buttons
    btn_plus->setGeometry(this->width() / 2 + radius / 2,
                          this->height() / 2 + radius / 1.4,
                          radius / 2.5, radius / 2.5);
    btn_minus->setGeometry(this->width() / 2 - 0.9 * radius,
                           this->height() / 2 + radius / 1.4,
                           radius / 2.5, radius / 2.5);
}

void CircleMark::wheelEvent(QWheelEvent *event)
{

    if(event->angleDelta().y() > 0)
        this->inc();
    else if(event->angleDelta().y() < 0)
        this->dec();

    QWidget::wheelEvent(event);
}

void CircleMark::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_Plus: [[fallthrough]];
        case Qt::Key_Up:
            this->inc();
            break;

        case Qt::Key_Minus: [[fallthrough]];
        case Qt::Key_Down:
            this->dec();
            break;
    }
    QWidget::keyPressEvent(event);
}

[[maybe_unused]] void CircleMark::setRadius(short radius)
{ this->radius = radius; }

void CircleMark::enterEvent(QEnterEvent *event)
{
    setFocus();
    radius += 3;
    QWidget::enterEvent(event);
}

void CircleMark::leaveEvent(QEvent *event)
{
    radius -= 3;
    clearFocus();
    QWidget::leaveEvent(event);
}

double CircleMark::angleToRad(double rad)
{ return rad / 180 * M_PI; }

double CircleMark::fillAngle() const
{ return end_angle / static_cast<double>(max - min) * (filling - min); }

void CircleMark::inc()
{ if(filling < max) { ++filling; repaint(); emit valueChanged(); } }

void CircleMark::dec()
{ if(filling > min) { --filling; repaint(); emit valueChanged(); } }

double CircleMark::operator()()
{ return static_cast<double>(filling) / divider; }

void CircleMark::setLimits(long min, long max, ulong divider)
{
    this->min = min;
    this->max = max;
    this->divider = divider;
    this->filling = min;
}

void CircleMark::setPrecision(ushort precision)
{
    this->precision = precision;
}

void CircleMark::setFilling(long filling)
{
    if(filling >= min && filling <= max)
        this->filling = filling;
    else
        qDebug() << "setFilling(long): going out of limits." << Qt::endl;
}
