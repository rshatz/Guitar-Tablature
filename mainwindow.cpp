#include <QHBoxLayout>
#include <QGridLayout>
#include <QToolBar>
#include <QDebug>

#include "mainwindow.h"
#include "fretboard.h"
#include "tabarea.h"

const int IdRole = Qt::UserRole;
MainWindow::MainWindow()
{
    setWindowTitle("Guitar Scales");

    fretboard = new Fretboard;
    tabArea = new TabArea(this);

    createToolBar();

    QVBoxLayout *topLayout = new QVBoxLayout;

    topLayout->addWidget(fretboard);
    topLayout->setContentsMargins(50, 10, 60, 50);
    //topLayout->addWidget(tabArea);
    //topLayout->setSizeConstraint(QLayout::SetFixedSize);

    QVBoxLayout *bottomLayout = new QVBoxLayout;
    bottomLayout->addWidget(tabArea);
    bottomLayout->setSizeConstraint(QLayout::SetFixedSize);

    //topLayout->addLayout(bottomLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(bottomLayout);
    //setLayout(mainLayout);

    QWidget *centralWidget = new QWidget;
    //centralWidget->setStyleSheet("background: black;");
    centralWidget->setLayout(mainLayout);
    //centralWidget->setLayout(bottomLayout);
    setCentralWidget(centralWidget);

    tabMode();
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

    keyComboBox->addItem("A", Fretboard::A);
    keyComboBox->addItem("A#", Fretboard::A_SHARP);
    keyComboBox->addItem("B", Fretboard::B);
    keyComboBox->addItem("C", Fretboard::C);
    keyComboBox->addItem("C#", Fretboard::C_SHARP);
    keyComboBox->addItem("D", Fretboard::D);
    keyComboBox->addItem("D#", Fretboard::D_SHARP);
    keyComboBox->addItem("E", Fretboard::E);
    keyComboBox->addItem("F", Fretboard::F);
    keyComboBox->addItem("F#", Fretboard::F_SHARP);
    keyComboBox->addItem("G", Fretboard::G);
    keyComboBox->addItem("G#", Fretboard::G_SHARP);

    keyLabel = new QLabel("&Key");
    keyLabel->setContentsMargins(10, 0, 5, 0);
    keyLabel->setBuddy(keyComboBox);

    scaleComboBox = new QComboBox;
    scaleComboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    scaleComboBox->addItem("major", Fretboard::MAJOR);
    scaleComboBox->addItem("major pentatonic", Fretboard::MAJOR_PENTATONIC);
    scaleComboBox->addItem("natural minor", Fretboard::NATURAL_MINOR);
    scaleComboBox->addItem("minor pentatonic", Fretboard::MINOR_PENTATONIC);
    scaleComboBox->addItem("harmonic minor", Fretboard::HARMONIC_MINOR);
    scaleComboBox->addItem("melodic minor", Fretboard::MELODIC_MINOR);
    scaleComboBox->addItem("blues", Fretboard::BLUES);
    scaleComboBox->addItem("whole tone", Fretboard::WHOLE_TONE);
    scaleComboBox->addItem("whole-half diminished", Fretboard::WHOLE_HALF_DIM);
    scaleComboBox->addItem("half-whole diminished", Fretboard::HALF_WHOLE_DIM);
    scaleComboBox->addItem("phrygian", Fretboard::PHRYGIAN);
    scaleComboBox->addItem("lydian", Fretboard::LYDIAN);
    scaleComboBox->addItem("mixolydian", Fretboard::MIXOLYDIAN);
    scaleComboBox->addItem("aeolian", Fretboard::AEOLIAN);
    scaleComboBox->addItem("locrian", Fretboard::LOCRIAN);

    scaleLabel = new QLabel("S&cale ");
    scaleLabel->setContentsMargins(10, 0, 2, 0);
    scaleLabel->setBuddy(scaleComboBox);

    tuningComboBox = new QComboBox;
    tuningComboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    tuningComboBox->addItem("Standard", Fretboard::STANDARD);
    tuningComboBox->addItem("Drop D", Fretboard::DROP_D);
    tuningComboBox->addItem("Open A", Fretboard::OPEN_A);
    tuningComboBox->addItem("Open B", Fretboard::OPEN_B);
    tuningComboBox->addItem("Open C", Fretboard::OPEN_C);
    tuningComboBox->addItem("Open D", Fretboard::OPEN_D);
    tuningComboBox->addItem("Open E", Fretboard::OPEN_E);
    tuningComboBox->addItem("Open F", Fretboard::OPEN_F);
    tuningComboBox->addItem("Open G", Fretboard::OPEN_G);

    tuningLabel = new QLabel("&Tuning ");
    tuningLabel->setContentsMargins(10, 0, 2, 0);
    tuningLabel->setBuddy(tuningComboBox);

    submitButton = new QPushButton("Submit");

    clearButton = new QPushButton("Clear");

    allNoteCheckBox = new QCheckBox("Show All &Notes");//possibly not needed

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

    connect(keyComboBox, SIGNAL(activated(int)), this, SLOT(keyChanged()));
    connect(scaleComboBox, SIGNAL(activated(int)), this, SLOT(scaleChanged()));
    connect(tuningComboBox, SIGNAL(activated(int)), this, SLOT(tuningChanged()));
    connect(clearButton, SIGNAL(clicked(bool)), this, SLOT(tabMode()));
    connect(submitButton, SIGNAL(clicked(bool)), this, SLOT(showScale()));

    keyChanged();
    scaleChanged();
    tuningChanged();
}

void MainWindow::keyChanged()
{
    Fretboard::Key key = Fretboard::Key(keyComboBox->itemData(
                keyComboBox->currentIndex(), IdRole).toInt()); //need to study this more
    fretboard->setKey(key);
}

void MainWindow::scaleChanged()
{
    Fretboard::Scale scale = Fretboard::Scale(scaleComboBox->itemData(
                scaleComboBox->currentIndex(), IdRole).toInt()); //need to study this more
    fretboard->setScale(scale);
}

void MainWindow::tuningChanged()
{
    Fretboard::Tuning tuning = Fretboard::Tuning(tuningComboBox->itemData(
                tuningComboBox->currentIndex(), IdRole).toInt()); //need to study this more
    fretboard->setTuning(tuning);
}

void MainWindow::tabMode()
{
    fretboard->tabMode();
}

void MainWindow::showScale()
{
    fretboard->drawScale();
}

void MainWindow::checkBoxState()
{
    if(allNoteCheckBox->isChecked())
    {
        keyComboBox->setEnabled(false);
        scaleComboBox->setEnabled(false);
        connect(allNoteCheckBox, SIGNAL(clicked(bool)), fretboard, SLOT(drawAllNotes()));
        connect(submitButton, SIGNAL(clicked(bool)), fretboard, SLOT(drawAllNotes()));
    }
    else
    {
        keyComboBox->setEnabled(true);
        scaleComboBox->setEnabled(true);
        tuningComboBox->setEnabled(true);
        submitButton->setEnabled(true);
        connect(allNoteCheckBox, SIGNAL(clicked(bool)), fretboard, SLOT(drawScale()));
        connect(submitButton, SIGNAL(clicked(bool)), fretboard, SLOT(drawScale()));
    }
}
