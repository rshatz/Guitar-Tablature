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
            delete [] fretBoardButton[i];
        }
        delete [] fretBoardButton;
    }
    fretBoardfilled = false;
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

    fretBoardButton = new QPushButton *[6];

    QListIterator<int> i(scaleDegrees);
    for(int string = 0; string < 6; string++)
    {
        int notePos = tuningFormula[string];
        int y = yCoordinate[string];
        fretBoardButton[string] = new QPushButton[13];

        for(int fret = 0; fret < 13; fret++)
        {
            connect(&fretBoardButton[string][fret], SIGNAL(clicked()), this, SLOT(testSlot()));

            int x = xCoordinate[fret];
            if(notePos >= 12)
            {
                notePos = 0;
            }

            fretBoardButton[string][fret].setParent(QWidget::parentWidget());
            fretBoardButton[string][fret].setText(noteList[notePos]);
            fretBoardButton[string][fret].setGeometry(x, y, 38, 30);

            if(fretBoardButton[string][fret].text() == noteList[rootNote])
            {
                fretBoardButton[string][fret].setObjectName("rootButton");//set ID Selector for corresponding style sheet
                fretBoardButton[string][fret].setStyleSheet(
                            "QPushButton#rootButton{background-color: rgba(128, 0, 0, 200)}"
                            "QPushButton#rootButton:hover{border: 2px solid white}"
                            "QPushButton#rootButton:pressed{background-color: rgb(128, 0, 0)}");
            }
            else
            {
                fretBoardButton[string][fret].setObjectName("noteButton");//set ID Selector for corresponding style sheet
                fretBoardButton[string][fret].setStyleSheet(
                            "QPushButton#noteButton{background-color: rgba(0, 128, 128, 200)}"
                            "QPushButton#noteButton:hover{border: 2px solid white}"
                            "QPushButton#noteButton:pressed{background-color: rgb(0, 128, 128)}");
            }

            while(i.hasNext())
            {
                if(fretBoardButton[string][fret].text() == noteList[i.next()])
                {
                    fretBoardButton[string][fret].show();
                }
            }
            i.toFront();
            notePos++;
        }
    }
    fretBoardfilled = true;
}

void MusicScales::drawAllNotes()
{
    scaleDegrees.clear();
    clearFretBoard();
    const int yCoordinate[13] = {70, 114, 158, 202, 246, 290};

    const int xCoordinate[13] = {20, 100, 190, 280, 370, 460, 553, 643,
                          733, 825, 915, 1010, 1100};

    fretBoardButton = new QPushButton *[6];

    for(int string = 0; string < 6; string++)
    {
        int notePos = tuningFormula[string];
        int y = yCoordinate[string];
        fretBoardButton[string] = new QPushButton[13];

        for(int fret = 0; fret < 13; fret++)
        {
            connect(&fretBoardButton[string][fret], SIGNAL(clicked()), this, SLOT(testSlot()));

            int x = xCoordinate[fret];
            if(notePos >= 12)
            {
                notePos = 0;
            }

            fretBoardButton[string][fret].setParent(QWidget::parentWidget());
            fretBoardButton[string][fret].setText(noteList[notePos]);
            fretBoardButton[string][fret].setGeometry(x, y, 38, 30);

            fretBoardButton[string][fret].setObjectName("noteButton");//set ID Selector for corresponding style sheet
            fretBoardButton[string][fret].setStyleSheet(
                        "QPushButton#noteButton{background-color: teal;}"
                        "QPushButton#noteButton:hover{border: 2px solid grey;}"
                        "QPushButton#noteButton:pressed{background-color: #007A7A};");

            fretBoardButton[string][fret].show();
            notePos++;
        }
    }
    fretBoardfilled = true;
}

void MusicScales::testSlot()//delete
{
    qDebug() << "CLICKED!";
}

void MusicScales::buildTabButtons()
{
    const int yCoordinate[13] = {70, 114, 158, 202, 246, 290};

    const int xCoordinate[13] = {20, 100, 190, 280, 370, 460, 553, 643,
                          733, 825, 915, 1010, 1100};

    fretBoardButton = new QPushButton *[6];

    for(int string = 0; string < 6; string++)
    {
        int y = yCoordinate[string];
        fretBoardButton[string] = new QPushButton[13];

        for(int fret = 0; fret < 13; fret++)
        {
            connect(&fretBoardButton[string][fret], SIGNAL(clicked()), this, SLOT(testSlot()));

            int x = xCoordinate[fret];

            fretBoardButton[string][fret].setParent(QWidget::parentWidget());

            fretBoardButton[string][fret].setGeometry(x, y, 38, 30);

            fretBoardButton[string][fret].setObjectName("tabButton");//set ID Selector for corresponding style sheet
//            fretBoardButton[string][fret].setStyleSheet(
//                        "QPushButton#noteButton:hover{background-color: rgba(255, 255, 255, 50);"
//                        "QPushButton#noteButton:hover{border: 2px solid grey;}"
//                        "QPushButton#noteButton:pressed{background-color: #007A7A};");
            fretBoardButton[string][fret].show();

        }
    }
}
