#include "notebutton.h"

#include <QPushButton>

NoteButton::NoteButton(int[], int s, int f, QWidget *parent) : QPushButton(parent)
{
    string = s;
    fret = f;

    connect(this, SIGNAL(clicked(bool)), this, SLOT(reemitClicked()));
}

void NoteButton::reemitClicked()
{
    emit clicked(string, fret);
}
