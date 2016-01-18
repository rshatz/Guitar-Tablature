#ifndef TABAREA_H
#define TABAREA_H

#include <QWidget>
#include <QPen>
#include <QLine>

class TabArea : public QWidget
{
    Q_OBJECT
public:
    TabArea(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:

    QPen pen;

    QLine *stringLine;

};

#endif // TABAREA_H
