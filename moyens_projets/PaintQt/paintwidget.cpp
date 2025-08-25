#include "paintwidget.h"
#include <QPainter>
#include <QMouseEvent>

/*
 * PaintWidget Implementation 
 */
PaintWidget::PaintWidget(QWidget* parent)
    : QWidget(parent),
    brushColor(Qt::black),
    brushSize(5),
    drawing(false),
    historyIndex(-1)
{
    setAttribute(Qt::WA_StaticContents);
}

/*
 * Getters and Setters for brush color and size
 */
QColor PaintWidget::getBrushColor() const { return brushColor; }
void PaintWidget::setBrushColor(const QColor& color) { brushColor = color; }

int PaintWidget::getBrushSize() const { return brushSize; }
void PaintWidget::setBrushSize(int size) { brushSize = size; }

/*
 * Set up the painting area and handle mouse events
 */
void PaintWidget::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    painter.fillRect(rect(), Qt::white);

    for (const auto& stroke : strokes) {
        if (stroke.points.size() < 2) continue;
        painter.setPen(QPen(stroke.color, stroke.size, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        for (int i = 1; i < stroke.points.size(); ++i) {
            painter.drawLine(stroke.points[i - 1], stroke.points[i]);
        }
    }

    if (drawing && currentStroke.points.size() > 1) {
        painter.setPen(QPen(currentStroke.color, currentStroke.size, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        for (int i = 1; i < currentStroke.points.size(); ++i) {
            painter.drawLine(currentStroke.points[i - 1], currentStroke.points[i]);
        }
    }
}

/*
 * If the left mouse button is pressed, start a new stroke
 */
void PaintWidget::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        drawing = true;
        currentStroke = { QVector<QPoint>{event->pos()}, brushColor, brushSize };
        update();
    }
}

/*
 * If the mouse is moved while drawing, add points to the current stroke
 */
void PaintWidget::mouseMoveEvent(QMouseEvent* event) {
    if (drawing) {
        currentStroke.points.append(event->pos());
        update();
    }
}

/*
 * If the left mouse button is released, finish the current stroke
 */
void PaintWidget::mouseReleaseEvent(QMouseEvent* event) {
    if (drawing && event->button() == Qt::LeftButton) {
        strokes.append(currentStroke);
        drawing = false;
        saveHistory();
        update();
    }
}

/*
 * Save the current state to history for undo/redo functionality
 */
void PaintWidget::saveHistory() {
    while (history.size() > historyIndex + 1)
        history.pop_back();

    history.append(strokes);
    historyIndex++;
    if (history.size() > 50) {
        history.removeFirst();
        historyIndex--;
    }
}

/*
 * Undo the last drawing action
 */
void PaintWidget::undo() {
    if (historyIndex > 0) {
        historyIndex--;
        strokes = history[historyIndex];
        update();
    }
}

/*
 * Redo the previous action if available
 */
void PaintWidget::redo() {
    if (historyIndex + 1 < history.size()) {
        historyIndex++;
        strokes = history[historyIndex];
        update();
    }
}

/*
 * Clear the canvas and reset history
 */
void PaintWidget::clearCanvas() {
    strokes.clear();
    saveHistory();
    update();
}

/*
 * Load an image as the background of the canvas
 */
void PaintWidget::loadImage(const QImage& image) {
    strokes.clear();

    background = image.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    update();
}

/*
 * Get the current canvas as a QImage including the background and strokes to save or export
 */
QImage PaintWidget::getImage() const {
    QImage image(size(), QImage::Format_ARGB32);
    image.fill(Qt::white);
    QPainter painter(&image);

    if (!background.isNull()) {
        painter.drawImage(0, 0, background);
    }

    for (const auto& stroke : strokes) {
        if (stroke.points.size() < 2) continue;
        painter.setPen(QPen(stroke.color, stroke.size, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        for (int i = 1; i < stroke.points.size(); ++i) {
            painter.drawLine(stroke.points[i - 1], stroke.points[i]);
        }
    }
    return image;
}
