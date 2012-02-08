#include <QtGui/QApplication>

#include "ComplexNetsGui/inc/mainwindow.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    ComplexNetsGui::MainWindow w;
    w.show();
    return a.exec();
}
