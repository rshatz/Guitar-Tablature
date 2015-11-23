#include <QDebug>

#include <QToolBar>
#include <QDockWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    noteLabels = new QLabel *[6];

    for(int i = 0; i < 6; i++)
    {
        noteLabels[i] = new QLabel[13];
        for(int u = 0; u < 13; u++)
        {
            noteLabels[i][u].setText("");
        }
    }

    createToolBar();

//    QHBoxLayout *bottomLayout = new QHBoxLayout;
//    tabSheet = new QPlainTextEdit;
//    bottomLayout->addWidget(tabSheet);

//    QVBoxLayout *mainLayout = new QVBoxLayout;
//    mainLayout->addLayout(topLayout);
//    mainLayout->addLayout(bottomLayout);
//    mainLayout->setContentsMargins(0, 0, 0, 0);

    fretBoardLabel = new QLabel;
    fretBoardLabel->setPixmap(QPixmap(":/FretBoard.jpg"));

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->setContentsMargins(60, 20, 50, 20);
    topLayout->addWidget(fretBoardLabel);
    topLayout->setSizeConstraint(QLayout::SetFixedSize);

    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(topLayout);
    setCentralWidget(centralWidget);

    connect(submitButton, SIGNAL(clicked(bool)), this, SLOT(submitPressed()));    
}

const QString MainWindow::notes[] = {" A", "A#", " B", " C", "C#", " D",
                                     "D#", " E", " F", "F#", " G", "G#"};

MainWindow::~MainWindow()
{

}

void MainWindow::createToolBar()
{
    selectionToolBar = addToolBar("Selection Tool Bar");

    keyComboBox = new QComboBox;
    keyComboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    keyLabel = new QLabel("   &Key ");
    keyLabel->setBuddy(keyComboBox);

    for(int i = 0; i < 11; i++)
    {
        keyComboBox->addItem(notes[i]);
    }

    scaleComboBox = new QComboBox;
    scaleComboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    scaleLabel = new QLabel("   S&cale ");
    scaleLabel->setBuddy(scaleComboBox);

    scaleComboBox->addItem("major");
    scaleComboBox->addItem("major pentatonic");
    scaleComboBox->addItem("natural minor");
    scaleComboBox->addItem("minor pentatonic");
    scaleComboBox->addItem("harmonic minor");
    scaleComboBox->addItem("melodic minor");
    //scaleComboBox->insertSeparator(6);
    // adding separator counts as an index in combo box causing
    // combo box index to misalign with enum index
    scaleComboBox->addItem("blues");
    scaleComboBox->addItem("whole tone");
    scaleComboBox->addItem("whole-half diminished ");
    scaleComboBox->addItem("half-whole diminished ");
    scaleComboBox->addItem("All Notes");

    tuningComboBox = new QComboBox;
    tuningComboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    tuningLabel = new QLabel("   &Tuning ");
    tuningLabel->setBuddy(tuningComboBox);

    tuningComboBox->addItem("Standard");
    tuningComboBox->addItem("Drop D");
    tuningComboBox->addItem("Open A");
    tuningComboBox->addItem("Open B");
    tuningComboBox->addItem("Open C");
    tuningComboBox->addItem("Open D");
    tuningComboBox->addItem("Open E");
    tuningComboBox->addItem("Open F");
    tuningComboBox->addItem("Open G");

    submitButton = new QPushButton("Submit");

    selectionToolBar->addWidget(keyLabel);
    selectionToolBar->addWidget(keyComboBox);
    selectionToolBar->addSeparator();
    selectionToolBar->addWidget(scaleLabel);
    selectionToolBar->addWidget(scaleComboBox);
    selectionToolBar->addSeparator();
    selectionToolBar->addWidget(tuningLabel);
    selectionToolBar->addWidget(tuningComboBox);
    selectionToolBar->addSeparator();
    selectionToolBar->addWidget(submitButton);
}

void MainWindow::submitPressed()
{
    for(int i = 0; i < 6; ++i) {
        delete [] noteLabels[i];
    }
    delete [] noteLabels;

    scaleDegrees.clear();
    tuningFormula.clear();
    //notesDisplayLabel->clear();

    setScale();
    buildScale();
    setTuning();
    drawScale();

//    QString noteList;
//    for(int i = 0; i < scaleDegrees.size(); i++)
//    {
//        noteList += notes[scaleDegrees[i]];
//        noteList += " ";
//    }

//    notesDisplayLabel->setText(noteList);
}

void MainWindow::setScale()
{
    switch(scaleComboBox->currentIndex())
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

void MainWindow::setTuning()
{
    switch(tuningComboBox->currentIndex())
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

void MainWindow::buildScale()
{
    int position = keyComboBox->currentIndex();
    for(int i = 0; i < scaleFormula.size(); i++)
    {
        scaleDegrees.append(position % 12);
        position += scaleFormula[i];
    }
    scaleFormula.clear();
}

void MainWindow::drawScale()
{
    int x = 10;
    int y = 45;

    noteLabels = new QLabel *[6];

    for(int i = 0; i < 6; i++)
    {
        noteLabels[i] = new QLabel[13];
        for(int u = 0; u < 13; u++)
        {
            noteLabels[i][u].setText("");
        }
    }

    QVectorIterator<int> i(scaleDegrees);
    for(int string = 0; string < 6; string++)
    {
        int notePos = tuningFormula[string];

        for(int fret = 0; fret < 13; fret++)
        {
            if(notePos >= 12)
            {
                notePos = 0;
            }

            noteLabels[string][fret].setParent(this);
            noteLabels[string][fret].setText(notes[notePos]);
            noteLabels[string][fret].setStyleSheet(
                        "font-size: 22px;"
                        "font: bold large Times New Roman;"
                        "color: white;"
                        "background-image: url(:/noteDot.png);"
                        //"text-align: center;"
                        );
            noteLabels[string][fret].setGeometry(x, y, 32, 32);

            while(i.hasNext())
            {
                if(noteLabels[string][fret].text() == notes[i.next()])
                {
                    noteLabels[string][fret].show();
                }
            }
            i.toFront();
            x += 95;//increment pixel length to next fret
            notePos++;
        }
        x = 10;
        y += 40;//increment pixel length to next string
    }
}
