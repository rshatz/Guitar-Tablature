#include <QApplication>
#include <QFile>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow window;

    //QSize windowSize = w.sizeHint();//this block of code should
    //w.setFixedSize(windowSize);//be deleted to enable mainwindow resize

    QFile file(":/stylesheet.qss");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        window.setStyleSheet(file.readAll());
        file.close();
    }

    window.show();

    return app.exec();
}
