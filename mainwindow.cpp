#include <QDebug>

#include <QToolBar>
#include <QDockWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    noteLabel = new QLabel *[6];

    for(int i = 0; i < 6; i++)
    {
        noteLabel[i] = new QLabel[13];
        for(int u = 0; u < 13; u++)
        {
            noteLabel[i][u].setText("");
        }
    }

    createToolBar();

    fretBoardLabel = new QLabel(this);
    fretBoardLabel->setPixmap(QPixmap(":/FretBoard.jpg"));

    notesDisplayLabel = new QLabel(this);

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->setContentsMargins(60, 15, 50, 0);
    topLayout->addWidget(fretBoardLabel);
    topLayout->addWidget(notesDisplayLabel);
    topLayout->setSizeConstraint(QLayout::SetFixedSize);

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    tabSheet = new QPlainTextEdit;
    bottomLayout->addWidget(tabSheet);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(bottomLayout);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    QWidget *centralWidgetLayout = new QWidget;
    centralWidgetLayout->setLayout(mainLayout);

    setCentralWidget(centralWidgetLayout);

}

const QString MainWindow::notes[] = {"A", "A#", "B", "C", "C#", "D",
                                     "D#", "E", "F", "F#", "G", "G#"};

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
    scaleComboBox->insertSeparator(6);
    scaleComboBox->addItem("blues");
    scaleComboBox->addItem("whole tone");
    scaleComboBox->addItem("whole-half diminished ");
    scaleComboBox->addItem("half-whole diminished ");
    scaleComboBox->insertSeparator(11);
    scaleComboBox->addItem("All Notes");

    tuningComboBox = new QComboBox;
    tuningComboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    tuningLabel = new QLabel("   &Tuning ");
    tuningLabel->setBuddy(tuningComboBox);

    tuningComboBox->addItem("Standard");
    tuningComboBox->addItem("Drop D");
    //tuningComboBox->insertSeparator(2);
    tuningComboBox->addItem("Open A");
    tuningComboBox->addItem("Open C");
    tuningComboBox->addItem("Open D");
    tuningComboBox->addItem("Open D Minor");
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

    connect(submitButton, SIGNAL(clicked(bool)), this, SLOT(submitPressed()));
}

void MainWindow::submitPressed()
{
    for(int i = 0; i < 6; ++i) {
        delete [] noteLabel[i];
    }
    delete [] noteLabel;

    scaleDegrees.clear();
    tuningFormula.clear();
    notesDisplayLabel->clear();
    setScale();
    buildScale();
    setTuning();
    drawScale();

    QString noteList;
    for(int i = 0; i < scaleDegrees.size(); i++)
    {
        noteList += notes[scaleDegrees[i]];
        noteList += " ";
    }

    notesDisplayLabel->setText(noteList);
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
    case OPEN_C:
        tuningFormula << 7 << 3 << 10 << 3 << 10 << 3;
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
    int x = 45;
    int y = 38;

    noteLabel = new QLabel *[6];

    for(int i = 0; i < 6; i++)
    {
        noteLabel[i] = new QLabel[13];
        for(int u = 0; u < 13; u++)
        {
            noteLabel[i][u].setText("");
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

            noteLabel[string][fret].setParent(this);
            noteLabel[string][fret].setText(notes[notePos]);
            noteLabel[string][fret].setGeometry(x, y, 32, 32);

            while(i.hasNext())
            {
                if(noteLabel[string][fret].text() == notes[i.next()])
                {
                    noteLabel[string][fret].show();
                }
            }
            i.toFront();
            x += 95;//increment pixel length to next fret
            notePos++;
        }
        x = 45;
        y += 40;//increment pixel length to next string
    }
}
