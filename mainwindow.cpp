#include <QHBoxLayout>
#include <QToolBar>
#include <QFile>
#include <QDebug>

#include "mainwindow.h"
#include "musicscales.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("Guitar Scales");

    musicScale = new MusicScales;
    createToolBar();

    fretBoardLabel = new QLabel;
    fretBoardLabel->setPixmap(QPixmap(":/fretboard.png"));

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->setContentsMargins(60, 20, 50, 20);
    topLayout->addWidget(fretBoardLabel);
    topLayout->addWidget(musicScale);
    topLayout->setSizeConstraint(QLayout::SetFixedSize);

    QWidget *centralWidget = new QWidget;
    centralWidget->setStyleSheet("background: black;");
    centralWidget->setLayout(topLayout);
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{

}

void MainWindow::createToolBar()
{
    selectionToolBar = addToolBar("Selection Tool Bar");
    selectionToolBar->setMovable(false);

    keyComboBox = new QComboBox;
    keyComboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);

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

    keyLabel = new QLabel("   &Key ");
    keyLabel->setBuddy(keyComboBox);

    scaleComboBox = new QComboBox;
    scaleComboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    scaleComboBox->addItem("major");
    scaleComboBox->addItem("major pentatonic");
    scaleComboBox->addItem("natural minor");
    scaleComboBox->addItem("minor pentatonic");
    scaleComboBox->addItem("harmonic minor");
    scaleComboBox->addItem("melodic minor");
    scaleComboBox->addItem("blues");
    scaleComboBox->addItem("whole tone");
    scaleComboBox->addItem("whole-half diminished ");
    scaleComboBox->addItem("half-whole diminished ");
    scaleComboBox->addItem("phrygian");
    scaleComboBox->addItem("lydian");
    scaleComboBox->addItem("mixolydian");
    scaleComboBox->addItem("aeolian");
    scaleComboBox->addItem("locrian");

    scaleLabel = new QLabel("   S&cale ");
    scaleLabel->setBuddy(scaleComboBox);

    tuningComboBox = new QComboBox;
    tuningComboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    tuningComboBox->addItem("Standard");
    tuningComboBox->addItem("Drop D");
    tuningComboBox->addItem("Open A");
    tuningComboBox->addItem("Open B");
    tuningComboBox->addItem("Open C");
    tuningComboBox->addItem("Open D");
    tuningComboBox->addItem("Open E");
    tuningComboBox->addItem("Open F");
    tuningComboBox->addItem("Open G");

    tuningLabel = new QLabel("   &Tuning ");
    tuningLabel->setBuddy(tuningComboBox);

    submitButton = new QPushButton("Submit");
    clearButton = new QPushButton("Clear");

    allNoteCheckBox = new QCheckBox("Show All &Notes");
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
    selectionToolBar->addSeparator();
    selectionToolBar->addWidget(clearButton);
    selectionToolBar->addSeparator();
    selectionToolBar->addWidget(allNoteCheckBox);

    connect(keyComboBox, SIGNAL(activated(int)), musicScale, SLOT(setKey(int)));
    connect(scaleComboBox, SIGNAL(activated(int)), musicScale, SLOT(setScale(int)));
    connect(tuningComboBox, SIGNAL(activated(int)), musicScale, SLOT(setTuning(int)));
    connect(clearButton, SIGNAL(clicked(bool)), musicScale, SLOT(clearFretBoard()));
    connect(allNoteCheckBox, SIGNAL(toggled(bool)), this, SLOT(checkBoxState()));

    musicScale->setKey(0);
    musicScale->setScale(0);
    musicScale->setTuning(0);

    checkBoxState();
}

void MainWindow::checkBoxState()
{
    if(allNoteCheckBox->isChecked())
    {
        keyComboBox->setEnabled(false);
        scaleComboBox->setEnabled(false);
        connect(allNoteCheckBox, SIGNAL(clicked(bool)), musicScale, SLOT(drawAllNotes()));
        connect(submitButton, SIGNAL(clicked(bool)), musicScale, SLOT(drawAllNotes()));
    }
    else
    {
        keyComboBox->setEnabled(true);
        scaleComboBox->setEnabled(true);
        tuningComboBox->setEnabled(true);
        submitButton->setEnabled(true);
        connect(allNoteCheckBox, SIGNAL(clicked(bool)), musicScale, SLOT(drawScale()));
        connect(submitButton, SIGNAL(clicked(bool)), musicScale, SLOT(drawScale()));
    }
}
