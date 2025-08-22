#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <Qt>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("InteractiveQt");

    /*
     * Create a vertical layout and center its contents
     */
    QVBoxLayout* layout = new QVBoxLayout(&window);
    layout->setAlignment(Qt::AlignCenter);

    /*
     * Create a button that changes the window's background color
     * Increment a counter each time the button is clicked
     */
    QPushButton* button = new QPushButton("Click here!");
    layout->addWidget(button, 0, Qt::AlignCenter);

    /*
     * Create a label to display the counter
     */
    QLabel* counterLabel = new QLabel("Number of clicks: 0");
    layout->addWidget(counterLabel, 0, Qt::AlignCenter);

    int counter = 0;

    /*
     * Connect the button's clicked signal to a lambda function
     * Changes the color randomly and updates the counter label
     */
    QObject::connect(button, &QPushButton::clicked, [&]() {
        counter++;
        window.setStyleSheet(QString("background-color: rgb(%1, %2, %3);")
            .arg(rand() % 256)
            .arg(rand() % 256)
            .arg(rand() % 256));

        counterLabel->setText(QString("Number of clicks: %1").arg(counter));
        });

    /*
     * Set the layout, resize, and show the window
     */
    window.setLayout(layout);
    window.resize(300, 300);
    window.show();

    return app.exec();
}
