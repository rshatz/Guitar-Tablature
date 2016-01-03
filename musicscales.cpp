#include <QDebug>
#include "musicscales.h"

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
        scaleFormula << 1 << 2 << 2 << 2 << 1 << 2 << 2;
        break;
    case LYDIAN:
        scaleFormula << 2 << 2 << 2 << 1 << 2 << 2 << 1;
        break;
    case MIXOLYDIAN:
        scaleFormula << 2 << 2 << 1 << 2 << 2 << 1 << 2;
        break;
    case AEOLIAN:
        scaleFormula << 2 << 1 << 2 << 2 << 1 << 2 << 2;
        break;
    case LOCRIAN:
        scaleFormula << 1 << 2 << 2 << 1 << 2 << 2 << 2;
        break;
    }
}

void MusicScales::setTuning(int tuning)
{
    //tuning formulas created starting on 1st string
    //instead of traditional method of being created
    //starting on the 6th string. Hence, formulas are
    //represented here in backwards order.
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
        tuningFormula << 6 << 2 << 9 << 2 << 9 << 2;
    case OPEN_C:
        tuningFormula << 7 << 3 << 10 << 3 << 10 << 3;
        break;
    case OPEN_D:
        tuningFormula << 5 << 0 << 9 << 5 << 0 << 5;
        break;
    case OPEN_E:
        tuningFormula << 7 << 2 << 11 << 7 << 2 << 7;
        break;
    case OPEN_F:
        tuningFormula << 8 << 0 << 8 << 3 << 8 << 3;
        break;
    case OPEN_G:
        tuningFormula << 5 << 2 << 10 << 5 << 10 << 5;
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

    const int yCoordinate[13] = {70, 114, 158, 202, 246, 290};

    const int xCoordinate[13] = {20, 100, 190, 280, 370, 460, 553, 643,
                          733, 825, 915, 1010, 1100};

    int rootNote = scaleDegrees[0];

    fretBoardNotes = new QPushButton *[6];

    QListIterator<int> i(scaleDegrees);
    for(int string = 0; string < 6; string++)
    {
        int notePos = tuningFormula[string];
        int y = yCoordinate[string];
        fretBoardNotes[string] = new QPushButton[13];

        for(int fret = 0; fret < 13; fret++)
        {
            connect(&fretBoardNotes[string][fret], SIGNAL(clicked(bool)),
                    this, SLOT(testSlot()));
            int x = xCoordinate[fret];
            if(notePos >= 12)
            {
                notePos = 0;
            }

            fretBoardNotes[string][fret].setParent(QWidget::parentWidget());
            fretBoardNotes[string][fret].setText(noteList[notePos]);
            fretBoardNotes[string][fret].setGeometry(x, y, 38, 30);

            if(fretBoardNotes[string][fret].text() == noteList[rootNote])
            {
                fretBoardNotes[string][fret].setObjectName("rootButton");//set ID Selector for corresponding style sheet
                fretBoardNotes[string][fret].setStyleSheet("QPushButton#rootButton{background-color: maroon;}"
                                                           "QPushButton#rootButton:hover{border: 2px solid grey;}"
                                                           "QPushButton#rootButton:pressed{background-color: #780000};"
                                                           );

            }
            else
            {
                fretBoardNotes[string][fret].setObjectName("noteButton");//set ID Selector for corresponding style sheet
                fretBoardNotes[string][fret].setStyleSheet("QPushButton#noteButton{background-color: teal;}"
                                                           "QPushButton#noteButton:hover{border: 2px solid grey;}"
                                                           "QPushButton#noteButton:pressed{background-color: #007A7A};"
                                                           );
            }

            while(i.hasNext())
            {
                if(fretBoardNotes[string][fret].text() == noteList[i.next()])
                {
                    fretBoardNotes[string][fret].show();
                }
            }
            i.toFront();
            notePos++;
        }
    }
    fretBoardfilled = true;
}

void MusicScales::testSlot()
{
    qDebug() << "CLICKED!";
}
