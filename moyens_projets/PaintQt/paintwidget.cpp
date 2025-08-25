#include "paintwidget.h"
#include <QPainter>
#include <QMouseEvent>

PaintWidget::PaintWidget(QWidget* parent) : QWidget(parent), brushColor(Qt::black) {}

void PaintWidget::setBrushColor(const QColor& color) {
    brushColor = color;
}

void PaintWidget::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
        
    for (const auto& stroke : strokes) {
        for (int i = 1; i < stroke.points.size(); ++i) {
            painter.setPen(stroke.points[i].color);
            painter.drawLine(stroke.points[i - 1].pos, stroke.points[i].pos);
        }
    }
    
    for (int i = 1; i < currentStroke.points.size(); ++i) {
        painter.setPen(currentStroke.points[i].color);
        painter.drawLine(currentStroke.points[i - 1].pos, currentStroke.points[i].pos);
    }
}

void PaintWidget::mousePressEvent(QMouseEvent* event) {
    drawing = true;
    currentStroke.points.clear();
    currentStroke.points.append({ event->pos(), brushColor });
    update();
}

void PaintWidget::mouseMoveEvent(QMouseEvent* event) {
    if (drawing) {
        currentStroke.points.append({ event->pos(), brushColor });
        update();
    }
}

void PaintWidget::mouseReleaseEvent(QMouseEvent*) {
    if (drawing) {
        strokes.append(currentStroke);
        currentStroke.points.clear();
        drawing = false;
    }
}
