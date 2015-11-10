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
    scaleComboBox->addItem("minor");
    scaleComboBox->addItem("minor pentatonic");

    tuningComboBox = new QComboBox;
    tuningComboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    tuningLabel = new QLabel("   &Tuning ");
    tuningLabel->setBuddy(tuningComboBox);

    tuningComboBox->addItem("standard");
    tuningComboBox->addItem("D#");
    tuningComboBox->addItem("Drop D");

    selectionToolBar->addWidget(keyLabel);
    selectionToolBar->addWidget(keyComboBox);
    selectionToolBar->addSeparator();
    selectionToolBar->addWidget(scaleLabel);
    selectionToolBar->addWidget(scaleComboBox);
    selectionToolBar->addSeparator();
    selectionToolBar->addWidget(tuningLabel);
    selectionToolBar->addWidget(tuningComboBox);

    connect(keyComboBox, SIGNAL(activated(int)), this, SLOT(scaleChanged()));
    connect(scaleComboBox, SIGNAL(activated(int)), this, SLOT(scaleChanged()));
}

void MainWindow::scaleChanged()
{
    switch(scaleComboBox->currentIndex())
    {
    case MAJOR_DIATONIC:
        majorDiatonic(keyComboBox->currentIndex());
        break;
    case MAJOR_PENTATONIC:
        majorPentatonic(keyComboBox->currentIndex());
        break;
    case MINOR_DIATONIC:
        minorDiatonic(keyComboBox->currentIndex());
        break;
    case MINOR_PENTATONIC:
        minorPentatonic(keyComboBox->currentIndex());
        break;
    }

    writeScale();
}

void MainWindow::majorDiatonic(int key)
{
    scaleDegrees.clear();
    const int majorDiat[] = {2, 2, 1, 2, 2, 2, 1};
    const int SIZE = 7;

    int position = key;
    for(int i = 0; i < SIZE; i++)
    {
        scaleDegrees.append(position % 12);
        position += majorDiat[i];
    }
}

void MainWindow::majorPentatonic(int key)
{
    scaleDegrees.clear();
    const int majorPent[] = {2, 2, 3, 2, 3};
    const int SIZE = 5;

    int position = key;
    for(int i = 0; i < SIZE; i++)
    {
        scaleDegrees.append(position % 12);
        position += majorPent[i];
    }
}

void MainWindow::minorDiatonic(int key)
{
    scaleDegrees.clear();
    const int minorDiat[] = {2, 1, 2, 2, 1, 2, 2};
    const int SIZE = 7;

    int position = key;
    for(int i = 0; i < SIZE; i++)
    {
        scaleDegrees.append(position % 12);
        position += minorDiat[i];
    }
}

void MainWindow::minorPentatonic(int key)
{
    scaleDegrees.clear();
    const int minorPent[] = {3, 2, 2, 3, 2};
    const int SIZE = 5;

    int position = key;
    for(int i = 0; i < SIZE; i++)
    {
        scaleDegrees.append(position % 12);
        position += minorPent[i];
    }
}

void MainWindow::writeScale()
{
    for(int i = 0; i < scaleDegrees.size(); i++)
    {
        qDebug() << notes[scaleDegrees[i]];
    }
}
