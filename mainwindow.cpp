#include <QHBoxLayout>
#include <QToolBar>
#include <QFile>

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
    //scaleComboBox->insertSeparator(6);
    // adding separator counts as an index in combo box causing
    // combo box index to misalign with enum index
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

    selectionToolBar = addToolBar("Selection Tool Bar");
    selectionToolBar->setMovable(false);

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

    connect(keyComboBox, SIGNAL(activated(int)),
            this, SLOT(keyChange()));
    connect(scaleComboBox, SIGNAL(activated(int)),
            this, SLOT(scaleChange()));
    connect(tuningComboBox, SIGNAL(activated(int)),
            this, SLOT(tuningChange()));
    connect(submitButton, SIGNAL(clicked(bool)),
            this, SLOT(drawScale()));

    keyChange();
    scaleChange();
    tuningChange();
}

void MainWindow::keyChange()
{
    musicScale->setKey(keyComboBox->currentIndex());
}

void MainWindow::scaleChange()
{
    musicScale->setScale(scaleComboBox->currentIndex());
}

void MainWindow::tuningChange()
{
    musicScale->setTuning(tuningComboBox->currentIndex());
}

void MainWindow::drawScale()
{
    musicScale->drawScale();
}
