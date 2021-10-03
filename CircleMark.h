#pragma once
#include <QWidget>
#include <QMouseEvent>

class CircleMark final : public QWidget
{
private:
    short   radius{50};
    uint8_t percent{0};

private:
    void paintEvent(QPaintEvent* ) override;
    void mousePressEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

public:
    CircleMark(short radius, QWidget* parent = nullptr);
    void setRadius(short radius);
};
