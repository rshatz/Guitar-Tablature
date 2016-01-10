#ifndef NOTEBUTTON_H
#define NOTEBUTTON_H

#include <QPushButton>

class NoteButton : public QPushButton
{
    Q_OBJECT

public:

    NoteButton(int [], int string, int fret, QWidget *parent);

signals:

    void clicked(int fret, int string);

private slots:

    void reemitClicked();

private:

    int string;
    int fret;
};

#endif // NOTEBUTTON_H
