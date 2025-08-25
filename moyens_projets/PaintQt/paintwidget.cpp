#include "paintwidget.h"
#include <QPainter>
#include <QMouseEvent>

PaintWidget::PaintWidget(QWidget* parent)
    : QWidget(parent),
    brushColor(Qt::black),
    brushSize(5),
    drawing(false),
    historyIndex(-1)
{
    setAttribute(Qt::WA_StaticContents);
}

QColor PaintWidget::getBrushColor() const { return brushColor; }
void PaintWidget::setBrushColor(const QColor& color) { brushColor = color; }

int PaintWidget::getBrushSize() const { return brushSize; }
void PaintWidget::setBrushSize(int size) { brushSize = size; }

void PaintWidget::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    painter.fillRect(rect(), Qt::white);

    // Dessiner les traits passés
    for (const auto& stroke : strokes) {
        if (stroke.points.size() < 2) continue;
        painter.setPen(QPen(stroke.color, stroke.size, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        for (int i = 1; i < stroke.points.size(); ++i) {
            painter.drawLine(stroke.points[i - 1], stroke.points[i]);
        }
    }

    // Dessiner le trait en cours
    if (drawing && currentStroke.points.size() > 1) {
        painter.setPen(QPen(currentStroke.color, currentStroke.size, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        for (int i = 1; i < currentStroke.points.size(); ++i) {
            painter.drawLine(currentStroke.points[i - 1], currentStroke.points[i]);
        }
    }
}

void PaintWidget::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        drawing = true;
        currentStroke = { QVector<QPoint>{event->pos()}, brushColor, brushSize };
        update();
    }
}

void PaintWidget::mouseMoveEvent(QMouseEvent* event) {
    if (drawing) {
        currentStroke.points.append(event->pos());
        update();
    }
}

void PaintWidget::mouseReleaseEvent(QMouseEvent* event) {
    if (drawing && event->button() == Qt::LeftButton) {
        strokes.append(currentStroke);
        drawing = false;
        saveHistory();
        update();
    }
}

void PaintWidget::saveHistory() {
    // Supprimer l’historique futur si on a dessiné après un undo
    while (history.size() > historyIndex + 1)
        history.pop_back();

    history.append(strokes);
    historyIndex++;
    if (history.size() > 50) {
        history.removeFirst();
        historyIndex--;
    }
}

void PaintWidget::undo() {
    if (historyIndex > 0) {
        historyIndex--;
        strokes = history[historyIndex];
        update();
    }
}

void PaintWidget::redo() {
    if (historyIndex + 1 < history.size()) {
        historyIndex++;
        strokes = history[historyIndex];
        update();
    }
}

void PaintWidget::clearCanvas() {
    strokes.clear();
    saveHistory();
    update();
}

void PaintWidget::loadImage(const QImage& image) {
    // ? Correction : peindre directement l'image dans les strokes
    strokes.clear();

    // On transforme l'image en un fond
    background = image.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    update();
}

QImage PaintWidget::getImage() const {
    QImage image(size(), QImage::Format_ARGB32);
    image.fill(Qt::white);
    QPainter painter(&image);

    // Dessiner le fond si on a chargé une image
    if (!background.isNull()) {
        painter.drawImage(0, 0, background);
    }

    // Dessiner les traits
    for (const auto& stroke : strokes) {
        if (stroke.points.size() < 2) continue;
        painter.setPen(QPen(stroke.color, stroke.size, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        for (int i = 1; i < stroke.points.size(); ++i) {
            painter.drawLine(stroke.points[i - 1], stroke.points[i]);
        }
    }
    return image;
}
