#include <QApplication>
#include <QFile>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QSize windowSize = w.sizeHint();//this block of code should
    w.setFixedSize(windowSize);//should be deleted to enable mainwindow resize

    QFile file(":/stylesheet.qss");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        w.setStyleSheet(file.readAll());
        file.close();
    }

    w.show();

    return a.exec();
}
