
#include <QDebug>
#include "musicscales.h"
#include "mainwindow.h"

MusicScales::MusicScales(QWidget *parent) : QWidget(parent)
{
    fretBoardfilled = false;
}

void MusicScales::setKey(int scaleKey)
{
    key = new int(scaleKey);
}

void MusicScales::setScale(int scale)
{
    scaleFormula.clear();
    switch(scale)
    {
    case MAJOR:
        scaleFormula << 2 << 2 << 1 << 2 << 2 << 2 << 1;
        break;
    case MAJOR_PENTATONIC:
        scaleFormula << 2 << 2 << 3 << 2 << 3;
        break;
    case NATURAL_MINOR:
        scaleFormula << 2 << 1 << 2 << 2 << 1 << 2 << 2;
        break;
    case MINOR_PENTATONIC:
        scaleFormula << 3 << 2 << 2 << 3 << 2;
        break;
    case HARMONIC_MINOR:
        scaleFormula << 2 << 1 << 2 << 2 << 1 << 3 << 2;
        break;
    case MELODIC_MINOR:
        scaleFormula << 2 << 1 << 2 << 2 << 2 << 2 << 1;
        break;
    case BLUES:
        scaleFormula << 3 << 2 << 1 << 1 << 3 << 2;
        break;
    case WHOLE_TONE:
        scaleFormula << 2 << 2 << 2 << 2 << 2 << 2;
        break;
    case WHOLE_HALF_DIM:
        scaleFormula << 2 << 1 << 2 << 1 << 2 << 1 << 2 << 1;
        break;
    case HALF_WHOLE_DIM:
        scaleFormula << 1 << 2 << 1 << 2 << 1 << 2 << 1 << 2;
        break;
    case PHRYGIAN:

        break;
    case LYDIAN:

        break;
    case MIXOLYDIAN:

        break;
    case AEOLIAN:

        break;
    case LOCRIAN:

        break;
    }
}

void MusicScales::setTuning(int tuning)
{
    tuningFormula.clear();
    switch(tuning)
    {
    case STANDARD:
        tuningFormula << 7 << 2 << 10 << 5 << 0 << 7;
        break;
    case DROP_D:
        tuningFormula << 7 << 2 << 10 << 5 << 0 << 5;
        break;
    case OPEN_A:
        tuningFormula << 7 << 0 << 7 << 4 << 0 << 7;
        break;
    case OPEN_B:
        tuningFormula << 2 << 9 << 2 << 9 << 2 << 6;
    case OPEN_C:
        tuningFormula << 7 << 3 << 10 << 3 << 10 << 3;
        break;
    case OPEN_D:
        tuningFormula << 5 << 0 << 5 << 9 << 0 << 5;
        break;
    case OPEN_E:
        tuningFormula << 7 << 2 << 7 << 11 << 2 << 7;
        break;
    case OPEN_F:
        tuningFormula << 3 << 8 << 3 << 8 << 0 << 3;
        break;
    case OPEN_G:
        tuningFormula << 5 << 10 << 5 << 10 << 2 << 5;
        break;
    }
}

void MusicScales::buildScale()
{
    int noteIndex = *key;
    for(int i = 0; i < scaleFormula.size(); i++)
    {
        scaleDegrees.append(noteIndex % 12);
        noteIndex += scaleFormula[i];
    }
}

void MusicScales::clearFretBoard()
{
    if(fretBoardfilled)
    {
        for(int i = 0; i < 6; i++)
        {
            delete [] fretBoardNotes[i];
        }
        delete [] fretBoardNotes;
    }
}

void MusicScales::drawScale()
{
    scaleDegrees.clear();
    clearFretBoard();

    buildScale();

    int x = 10;
    int y = 45;
    int rootNote = scaleDegrees[0];

    fretBoardNotes = new QLabel *[6];

    QListIterator<int> i(scaleDegrees);
    for(int string = 0; string < 6; string++)
    {
        int notePos = tuningFormula[string];
        fretBoardNotes[string] = new QLabel[13];

        for(int fret = 0; fret < 13; fret++)
        {
            if(notePos >= 12)
            {
                notePos = 0;
            }

            fretBoardNotes[string][fret].setParent(QWidget::parentWidget());
            fretBoardNotes[string][fret].setText(noteList[notePos]);
            fretBoardNotes[string][fret].setGeometry(x, y, 35, 35);

            if(fretBoardNotes[string][fret].text().contains("#"))
            {
                if(fretBoardNotes[string][fret].text()
                        == noteList[rootNote])
                {
                    fretBoardNotes[string][fret].setStyleSheet(
                                "padding: 2px;"
                                "font-size: 24px;"
                                "font: large Consolas;"
                                "color: white;"
                                "background-image: url(:/redDot.png);");
                }
                else
                {
                    fretBoardNotes[string][fret].setStyleSheet(
                                "padding: 2px;"
                                "font-size: 24px;"
                                "font: large Consolas;"
                                "color: white;"
                                "background-image: url(:/blueDot.png);");
                }
            }
            else
            {
                if(fretBoardNotes[string][fret].text()
                        == noteList[rootNote])
                {
                    fretBoardNotes[string][fret].setStyleSheet(
                                "padding: 3px;"
                                "font-size: 24px;"
                                "font: large Consolas;"
                                "color: white;"
                                "background-image: url(:/redDot.png);");
                }
                else
                {
                    fretBoardNotes[string][fret].setStyleSheet(
                                "padding: 3px;"
                                "font-size: 24px;"
                                "font: large Consolas;"
                                "color: white;"
                                "background-image: url(:/blueDot.png);");
                }
            }
            while(i.hasNext())
            {
                if(fretBoardNotes[string][fret].text() == noteList[i.next()])
                {
                    fretBoardNotes[string][fret].show();
                }
            }
            i.toFront();
            x += 95;//increment pixel length to next fret
            notePos++;
        }
        x = 10;
        y += 40;//increment pixel length to next string
    }
    fretBoardfilled = true;
}
