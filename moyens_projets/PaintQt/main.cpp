#include <QApplication>
#include <QWidget>
#include "paintwidget.h"

/*
* Create de main window and the drawing area
* Sets title and size of the window
*/

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	QWidget window;
	window.setWindowTitle("PaintQt");
	window.resize(800, 600);

	PaintWidget* paintArea = new PaintWidget(&window);
	paintArea->setGeometry(0, 0, 800, 600);

	window.show();
	return app.exec();
}