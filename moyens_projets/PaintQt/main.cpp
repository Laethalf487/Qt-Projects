#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QColorDialog>
#include <QVBoxLayout>
#include "paintwidget.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("PaintQt");

    QVBoxLayout* layout = new QVBoxLayout(&window);

    /*
     * Create the PaintWidget for drawing
     */
    PaintWidget* paint = new PaintWidget();
    layout->addWidget(paint);

    /*
     * Create a button to choose brush color
     */
    QPushButton* colorButton = new QPushButton("Choisir couleur");
    layout->addWidget(colorButton);

    QObject::connect(colorButton, &QPushButton::clicked, paint, [paint]() {
        QColor color = QColorDialog::getColor(paint->palette().color(paint->backgroundRole()),
            paint,
            "Choisir couleur du pinceau");
        if (color.isValid()) {
            paint->setBrushColor(color);
        }
    });


    window.setLayout(layout);
    window.resize(800, 600);
    window.show();

    return app.exec();
}
