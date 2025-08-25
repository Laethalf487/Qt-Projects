#include "paintwidget.h"
#include <QPainter>
#include <QMouseEvent>

PaintWidget::PaintWidget(QWidget* parent) : QWidget(parent) {}

void PaintWidget::paintEvent(QPaintEvent*) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen(Qt::black);

	for (int i = 1; i < points.size(); ++i) {
		painter.drawLine(points[i - 1], points[i]);
	}
}

void PaintWidget::mousePressEvent(QMouseEvent* event) {
	points.append(event->pos());
	update();
}

void PaintWidget::mouseMoveEvent(QMouseEvent* event) {
	points.append(event->pos());
	update();
}