#pragma once
#include <QWidget>
#include <QMouseEvent>
#include <QPushButton>

static const int arc_coeff = 16;
static constexpr int begin_angle = 210;
static constexpr int end_angle   = (begin_angle - 90) * 2;
static const QRgb indctr_bg_clr = 0xd4d4d4;
static const QRgb indctr_fill_clr = 0x03f8fc;
static const QRgb mark_clr = 0x0e7073;
static const QRgb mark_fill_clr = 0x1ac4c9;

template <class type>
class CircleMark : public QWidget
{
private:
    short   radius{50};

    long  min{0};
    long  max{100};
    long  divider{1};
    long  filling{min};
    QPushButton* btn_plus{nullptr};
    QPushButton* btn_minus{nullptr};

private:
    static inline double angleToRad(double rad);
    inline double fillAngle() const;

private slots:
    inline void inc();
    inline void dec();

private:
    void paintEvent(QPaintEvent* ) override;
    void wheelEvent(QWheelEvent* event) override;
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

public:
    explicit CircleMark(short radius, QWidget* parent = nullptr);
    void setRadius(short radius);
    void setLimits(long min, long max, long divider);

    type operator() ();
};
