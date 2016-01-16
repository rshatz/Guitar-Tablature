#include <QPainter>
#include "tabarea.h"

TabArea::TabArea(QWidget *parent) : QWidget(parent)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}

void TabArea::paintEvent(QPaintEvent * /*event*/)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));
    //painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));
    //painter.drawEllipse(80, 80, 400, 240);
    painter.drawLine(10, 50, 2000, 50);
}
