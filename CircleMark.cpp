#include <QApplication>
#include <QPainter>
#include <cmath>
#include <QStyle>

#include "CircleMark.h"

template <typename type>
CircleMark<type>::CircleMark(short radius, QWidget *parent)
: QWidget(parent),
  radius(radius)
{
    resize(2*radius + 5, 2*radius + 5);
    btn_plus = new QPushButton("+", this);
    btn_minus = new QPushButton("-", this);

    connect(btn_minus, &QPushButton::pressed, this, &CircleMark::dec);
    connect(btn_plus, &QPushButton::pressed, this, &CircleMark::inc);
}

template <typename type>
void CircleMark<type>::paintEvent([[maybe_unused]] QPaintEvent *)
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
    QString fillingText = QtPrivate::convertToQString(std::to_string(filling / divider));
    if constexpr(std::is_same<type, double>::value)
    {
        if( filling / divider == 0
            && static_cast<double>(filling) / divider < 0)
            { fillingText.push_front('-'); }

        fillingText.push_back(
        QtPrivate::convertToQString(
        "." + std::to_string(std::abs(filling % divider))));
    }
    painter.drawText(rect(),
                     Qt::AlignCenter,
                     fillingText );

    // Buttons
    btn_plus->setGeometry(this->width() / 2 + radius / 2,
                          this->height() / 2 + radius / 1.4,
                          radius / 2.5, radius / 2.5);
    btn_minus->setGeometry(this->width() / 2 - 0.9 * radius,
                           this->height() / 2 + radius / 1.4,
                           radius / 2.5, radius / 2.5);
}

template <typename type>
void CircleMark<type>::wheelEvent(QWheelEvent *event)
{

    if(event->angleDelta().y() > 0)
        this->inc();
    else if(event->angleDelta().y() < 0)
        this->dec();

    QWidget::wheelEvent(event);
}

template <typename type>
void CircleMark<type>::keyPressEvent(QKeyEvent *event)
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

template <typename type>
void CircleMark<type>::setRadius(short radius)
{ this->radius = radius; }

template <typename type>
void CircleMark<type>::enterEvent(QEnterEvent *event)
{
    setFocus();
    radius += 3;
    QWidget::enterEvent(event);
}

template <typename type>
void CircleMark<type>::leaveEvent(QEvent *event)
{
    radius -= 3;
    clearFocus();
    QWidget::leaveEvent(event);
}

template <typename type>
double CircleMark<type>::angleToRad(double rad)
{ return rad / 180 * M_PI; }

template <typename type>
double CircleMark<type>::fillAngle() const
{ return end_angle / static_cast<double>(max - min) * (filling - min); }

template <typename type>
void CircleMark<type>::inc()
{ if(filling < max) { ++filling; repaint(); } }

template <typename type>
void CircleMark<type>::dec()
{ if(filling > min) { --filling; repaint(); } }

template<class type>
type CircleMark<type>::operator()()
{ return static_cast<type>(filling) / divider; }

template<class type>
void CircleMark<type>::setLimits(long min, long max, long divider)
{
    this->min = min;
    this->max = max;
    this->divider = divider;
    this->filling = min;
}


template class CircleMark<long>;
template class CircleMark<double>;

