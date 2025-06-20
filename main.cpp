#include "MainWindow.h"
#include <QApplication>

//Hecho por: Fernando Israel Gomez Sandoval 21041252

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString iconPath = "C:\\Users\\ferba\\Development\\Kratos\\recursos\\omega1.ico";
    a.setWindowIcon(QIcon(iconPath));
    Kratos w;
    w.show();
    return a.exec();
}
