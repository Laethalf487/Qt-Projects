#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QVBoxLayout>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("InteractiveQt");

    QVBoxLayout* layout = new QVBoxLayout(&window);

    QPushButton* button = new QPushButton("Cliquez-moi !");
    layout->addWidget(button);

    int* counter = new int(0);

    QObject::connect(button, &QPushButton::clicked, [&]() {
        (*counter)++;
        window.setStyleSheet(QString("background-color: rgb(%1, %2, %3);")
            .arg(rand() % 256)
            .arg(rand() % 256)
            .arg(rand() % 256));
        QMessageBox::information(&window, "Compteur",
            QString("Nombre de clics : %1").arg(*counter));
        });

    window.setLayout(layout);
    window.resize(300, 200);
    window.show();

    return app.exec();
}
