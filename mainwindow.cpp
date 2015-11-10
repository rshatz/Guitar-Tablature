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

MainWindow::~MainWindow()
{

}

void MainWindow::createToolBar()
{
    notes = new QString[12];

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
    case MAJORDIAT:
        majorScale(keyComboBox->currentIndex());
        break;
    case MAJORPENT:
        majorScale(keyComboBox->currentIndex());
        break;
    case MINORDIAT:
        minorScale(keyComboBox->currentIndex());
        break;
    case MINORPENT:
        minorScale(keyComboBox->currentIndex());
        break;
    }
}

void MainWindow::majorScale(int key)
{
    const int major[] = {2, 2, 1, 2, 2, 2, 1};
    const int SIZE = 7;
    scaleDegrees = new QVector<int>(SIZE);

    int position = key;
    for(int i = 0; i < SIZE; i++)
    {
        int num = position % 12;
        scaleDegrees->append(num);
        position += major[i];
    }
}

void MainWindow::majorPent(int key)
{

}

void MainWindow::minorScale(int key)
{
    const int minor[] = {2, 1, 2, 2, 1, 2, 2};
    int postion = key;
}

void MainWindow::minorPent(int key)
{

}





