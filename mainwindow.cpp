#include <QDebug>

#include <QToolBar>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createToolBar();
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

    keyComboBox->addItem("A");
    keyComboBox->addItem("A#");
    keyComboBox->addItem("B");
    keyComboBox->addItem("C");
    keyComboBox->addItem("C#");
    keyComboBox->addItem("D");
    keyComboBox->addItem("D#");
    keyComboBox->addItem("E");
    keyComboBox->addItem("F");
    keyComboBox->addItem("F#");
    keyComboBox->addItem("G");
    keyComboBox->addItem("G#");

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


    tuningComboBox = new QComboBox;
    tuningComboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    tuningLabel = new QLabel("   &Tuning ");
    tuningLabel->setBuddy(tuningComboBox);

    tuningComboBox->addItem("standard");
    tuningComboBox->addItem("D#");
    tuningComboBox->addItem("Drop D");

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

    connect(submitButton, SIGNAL(clicked(bool)), this, SLOT(writeScale()));
}

void MainWindow::writeScale()
{
    scaleDegrees.clear();
    scaleChanged();
    for(int i = 0; i < scaleDegrees.size(); i++)
    {
        qDebug() << notes[scaleDegrees[i]];
    }

    qDebug() << "";
    qDebug() << "";
}

void MainWindow::scaleChanged()
{
    switch(scaleComboBox->currentIndex())
    {
    case MAJOR:
        major();
        break;
    case MAJOR_PENTATONIC:
        majorPentatonic();
        break;
    case NATURAL_MINOR:
        naturalMinor();
        break;
    case MINOR_PENTATONIC:
        minorPentatonic();
        break;
    case HARMONIC_MINOR:
        harmonicMinor();
        break;
    case MELODIC_MINOR:
        melodicMinor();
        break;
    case BLUES:
        blues();
        break;
    case WHOLE_TONE:
        wholeTone();
        break;
    case WHOLE_HALF_DIM:
        wholeHalfDim();
        break;
    case HALF_WHOLE_DIM:
        halfWholeDim();
        break;
    case PHRYGIAN:
        phrygian();
        break;
    case LYDIAN:
        lydian();
        break;
    case MIXOLYDIAN:
        mixolydian();
        break;
    case AEOLIAN:
        aeolian();
        break;
    case LOCRIAN:
        locraian();
        break;
    }
}

void MainWindow::major()
{
    const int formula[] = {2, 2, 1, 2, 2, 2, 1};
    const int SIZE = 7;
    buildScale(formula, SIZE);
}

void MainWindow::majorPentatonic()
{
    const int formula[] = {2, 2, 3, 2, 3};
    const int SIZE = 5;
    buildScale(formula, SIZE);
}

void MainWindow::naturalMinor()
{
    const int formula[] = {2, 1, 2, 2, 1, 2, 2};
    const int SIZE = 7;
    buildScale(formula, SIZE);
}

void MainWindow::minorPentatonic()
{
    const int formula[] = {3, 2, 2, 3, 2};
    const int SIZE = 5;
    buildScale(formula, SIZE);
}

void MainWindow::harmonicMinor()
{
    const int formula[] = {2, 1, 2, 2, 1, 3, 2};
    const int SIZE = 7;
    buildScale(formula, SIZE);
}

void MainWindow::melodicMinor()
{
    const int formula[] = {2, 1, 2, 2, 2, 2, 1};
    const int SIZE = 7;
    buildScale(formula, SIZE);
}

void MainWindow::blues()
{
    const int formula[] = {3, 2, 1, 1, 3, 2};
    const int SIZE = 6;
    buildScale(formula, SIZE);
}

void MainWindow::wholeTone()
{
    const int formula[] = {2, 2, 2, 2, 2, 2};
    const int SIZE = 6;
    buildScale(formula, SIZE);
}

void MainWindow::wholeHalfDim()
{
    const int formula[] = {2, 1, 2, 1, 2, 1, 2, 1};
    const int SIZE = 8;
    buildScale(formula, SIZE);
}

void MainWindow::halfWholeDim()
{
    const int formula[] = {1, 2, 1, 2, 1, 2, 1, 2};
    const int SIZE = 8;
    buildScale(formula, SIZE);
}

void MainWindow::phrygian()
{

}

void MainWindow::lydian()
{

}

void MainWindow::mixolydian()
{

}

void MainWindow::aeolian()
{

}

void MainWindow::locraian()
{

}

void MainWindow::buildScale(const int scaleFormula[], const int size)
{
    int position = keyComboBox->currentIndex();
    for(int i = 0; i < size; i++)
    {
        scaleDegrees.append(position % 12);
        position += scaleFormula[i];
    }
}



