#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QSize windowSize = w.sizeHint();

    w.setFixedSize(windowSize);
    w.show();

    return a.exec();
}
