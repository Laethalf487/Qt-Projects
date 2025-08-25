#pragma once
#include <QWidget>
#include <QVector>
#include <QPoint>
#include <QColor>

struct PaintPoint {
    QPoint pos;
    QColor color;
};

struct PaintStroke {
    QVector<PaintPoint> points;
};

class PaintWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PaintWidget(QWidget* parent = nullptr);

    void setBrushColor(const QColor& color);

protected:
    void paintEvent(QPaintEvent*) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    QVector<PaintStroke> strokes;
    PaintStroke currentStroke;
    QColor brushColor;
    bool drawing = false;
};
