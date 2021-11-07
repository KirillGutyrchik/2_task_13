#pragma once
#include <QWidget>
#include <QMouseEvent>
#include <QPushButton>

static const int arc_coeff = 16;
static const int begin_angle = 210;
static const int end_angle   = (begin_angle - 90) * 2;
static const QRgb indctr_bg_clr = 0xd4d4d4;
static const QRgb indctr_fill_clr = 0x03f8fc;
static const QRgb mark_clr = 0x0e7073;
static const QRgb mark_fill_clr = 0x1ac4c9;


/*!
 * \brief QWidget in the form of a round indicator with customizable limits.
 *
 *
 * <b>Templates:</b>
 * <pre> long or double types. </pre> \n
 *
 *<b>Control when hovering over a widget:</b>
 *<ul>
 *  <li>keys "+-" and "↑↓".
 *  <li>scroll.
 *  <li>buttons in widget.
 *</ul>
 */
class CircleMark final : public QWidget
{
    Q_OBJECT
public:
    ///
    /// \param radius - short value in pixels.
    /// \param parent
    explicit CircleMark(short radius, QWidget* parent = nullptr);

    ///
    /// \param radius - short value in pixels.
    void setRadius(short radius);

    ///
    /// <b> sets indicator limits in the form: \n
    /// <pre> <b> min / divider ... max / divider \n
    /// \param min
    /// \param max
    /// \param divider
    void setLimits(long min, long max, ulong divider);

    ///
    /// \param precision - number of digits after decimal point(default: 2)
    void setPrecision(ushort precision);

    ///
    /// \param filling - number within min ... max
    void setFilling(long filling);

    ///
    /// \return double or long value in indicator.
    double operator() ();

private:
    static inline double angleToRad(double rad);
    inline double fillAngle() const;

signals:
    void valueChanged();

private slots:
    void inc();
    void dec();

private:
    void paintEvent(QPaintEvent* ) override;
    void wheelEvent(QWheelEvent* event) override;
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private:
    short   radius{50};

    long   min{0};
    long   max{100};
    ulong  divider{1};
    long   filling{min};
    ushort precision{2};

    QPushButton* btn_plus{nullptr};
    QPushButton* btn_minus{nullptr};
};
