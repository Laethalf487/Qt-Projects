#pragma once
#include <QWidget>
#include <QVector>
#include <QPoint>

class PaintWidget : public QWidget {
	Q_OBJECT

public:
	explicit PaintWidget(QWidget* parent = nullptr);

protected:
	void paintEvent(QPaintEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;

/*
* Store the points where the user has drawn 
*/
private:
	QVector<QPoint> points;
};