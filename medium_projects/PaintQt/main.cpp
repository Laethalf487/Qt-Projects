#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QFrame>
#include <QColorDialog>
#include "paintwidget.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QMainWindow window;
    QWidget* central = new QWidget;
    QVBoxLayout* mainLayout = new QVBoxLayout(central);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->setSpacing(0);

    /*
     * Set the Toolbar
     */
    QFrame* toolbar = new QFrame;
    toolbar->setObjectName("toolbar");
    QHBoxLayout* toolbarLayout = new QHBoxLayout(toolbar);
    toolbarLayout->setContentsMargins(10, 10, 10, 10);
    toolbarLayout->setSpacing(20);

    /*
	 * Create toolbar buttons to undo, redo, and clear the canvas
     */
    QPushButton* undoBtn = new QPushButton("Undo");
    QPushButton* redoBtn = new QPushButton("Redo");
    QPushButton* clearBtn = new QPushButton("Clear");

    toolbarLayout->addWidget(undoBtn);
    toolbarLayout->addWidget(redoBtn);
    toolbarLayout->addWidget(clearBtn);

    /*
	 * Set the main content area with sidebar and PaintWidget
     */
    QHBoxLayout* contentLayout = new QHBoxLayout;
    QWidget* contentWidget = new QWidget;
    contentWidget->setLayout(contentLayout);

    /*
	 * Set the Sidebar 
     */
    QFrame* sidebar = new QFrame;
    sidebar->setObjectName("sidebar");
    sidebar->setFixedWidth(250);
    QVBoxLayout* sidebarLayout = new QVBoxLayout(sidebar);
    sidebarLayout->setContentsMargins(10, 10, 10, 10);
    sidebarLayout->setSpacing(15);

    /*
	 * Set the PaintWidget
     */
    PaintWidget* paint = new PaintWidget;
    paint->setMinimumSize(600, 400);

    /*
	 * Create a label for the brush size and the slider to adjust brush size
	 * Add a label to show the current brush size
     */
    QLabel* brushLabel = new QLabel("Brush Size :");
    brushLabel->setAlignment(Qt::AlignCenter);

    QSlider* brushSlider = new QSlider(Qt::Horizontal);
    brushSlider->setRange(1, 30);
    brushSlider->setValue(paint->getBrushSize());
    QLabel* brushValue = new QLabel(QString::number(paint->getBrushSize()));
	brushValue->setAlignment(Qt::AlignCenter);

    QObject::connect(brushSlider, &QSlider::valueChanged, [=](int value) {
        paint->setBrushSize(value);
        brushValue->setText(QString::number(value));
        });

    sidebarLayout->addWidget(brushLabel);
    sidebarLayout->addWidget(brushSlider);
    sidebarLayout->addWidget(brushValue);

    /*
	 * Create a label for the brush color and a button to open a color palette
	 * Display the current brush color
     */
    QLabel* sidebarLabel = new QLabel("Color Palette :");
    sidebarLabel->setAlignment(Qt::AlignCenter);

    QPushButton* chooseColorBtn = new QPushButton("Choose Color");

    QLabel* currentColorLabel = new QLabel;
    currentColorLabel->setFixedSize(60, 40);
    currentColorLabel->setStyleSheet("background-color: black; border: 2px solid #333;");

    QObject::connect(chooseColorBtn, &QPushButton::clicked, [=]() {
        QColor color = QColorDialog::getColor(paint->getBrushColor(), nullptr, "Choose brush color");
        if (color.isValid()) {
            paint->setBrushColor(color);
            currentColorLabel->setStyleSheet(
                QString("background-color: %1; border: 2px solid #333;").arg(color.name())
            );
        }
        });

    sidebarLayout->addWidget(sidebarLabel);
    sidebarLayout->addWidget(chooseColorBtn);
    sidebarLayout->addWidget(currentColorLabel);
    sidebarLayout->addStretch(1);

    /*
	 * Assemble the main layout
     */
    contentLayout->addWidget(sidebar);
    contentLayout->addWidget(paint, 1);

    mainLayout->addWidget(toolbar);
    mainLayout->addWidget(contentWidget, 1);
    window.setCentralWidget(central);

    /*
	 * Connect buttons to PaintWidget functions
     */
    QObject::connect(undoBtn, &QPushButton::clicked, [=]() { paint->undo(); });
    QObject::connect(redoBtn, &QPushButton::clicked, [=]() { paint->redo(); });
    QObject::connect(clearBtn, &QPushButton::clicked, [=]() { paint->clearCanvas(); });

    /*
	 * Apply custom styles to the application
     */
    QString style = R"(
        QWidget { font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; background-color: #f0f0f0; }
        #toolbar { background-color: #2c3e50; color: white; }
        #sidebar { background-color: white; border-right: 1px solid #ddd; }
        QPushButton { background-color: #34495e; border: none; color: white; padding: 8px 12px; border-radius: 4px; }
        QPushButton:hover { background-color: #4a6741; }
        QSlider::groove:horizontal { height: 6px; background: #ddd; border-radius: 3px; }
        QSlider::handle:horizontal { background: #3498db; border: 1px solid #2980b9; width: 14px; height: 14px; margin: -5px 0; border-radius: 7px; }
        QLabel { font-size: 14px; }
    )";
    app.setStyleSheet(style);

    window.showMaximized();
    return app.exec();
}
