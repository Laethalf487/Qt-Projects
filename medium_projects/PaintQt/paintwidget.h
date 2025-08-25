#pragma once
#include <QWidget>
#include <QVector>
#include <QColor>
#include <QPoint>
#include <QImage>

/*
 * Structure to hold a single stroke's data
 */
struct Stroke {
    QVector<QPoint> points;
    QColor color;
    int size;
};

class PaintWidget : public QWidget {
    Q_OBJECT

public:
    explicit PaintWidget(QWidget* parent = nullptr);

    QColor getBrushColor() const;
    void setBrushColor(const QColor& color);

    int getBrushSize() const;
    void setBrushSize(int size);

    void undo();
    void redo();
    void clearCanvas();
    void loadImage(const QImage& image);
    QImage getImage() const;

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    QVector<Stroke> strokes;
    Stroke currentStroke;
    QColor brushColor;
    int brushSize;
    bool drawing;

    QVector<QVector<Stroke>> history;
    int historyIndex;

    QImage background;

    void saveHistory();
};
