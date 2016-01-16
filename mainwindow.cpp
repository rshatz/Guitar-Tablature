#include <QHBoxLayout>
#include <QToolBar>
#include <QDebug>

#include "mainwindow.h"
#include "musicscales.h"

const int IdRole = Qt::UserRole;
MainWindow::MainWindow()
{
    setWindowTitle("Guitar Scales");

    musicScale = new MusicScales();

    createToolBar();

    fretBoardImage = new QLabel;
    fretBoardImage->setPixmap(QPixmap(":/fretboard.png"));

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->setContentsMargins(60, 20, 50, 20);
    topLayout->addWidget(fretBoardImage);
    topLayout->addWidget(musicScale);
    topLayout->setSizeConstraint(QLayout::SetFixedSize);

    QWidget *centralWidget = new QWidget;
    centralWidget->setStyleSheet("background: black;");
    centralWidget->setLayout(topLayout);
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

    keyComboBox->addItem("A", MusicScales::A);
    keyComboBox->addItem("A#", MusicScales::A_SHARP);
    keyComboBox->addItem("B", MusicScales::B);
    keyComboBox->addItem("C", MusicScales::C);
    keyComboBox->addItem("C#", MusicScales::C_SHARP);
    keyComboBox->addItem("D", MusicScales::D);
    keyComboBox->addItem("D#", MusicScales::D_SHARP);
    keyComboBox->addItem("E", MusicScales::E);
    keyComboBox->addItem("F", MusicScales::F);
    keyComboBox->addItem("F#", MusicScales::F_SHARP);
    keyComboBox->addItem("G", MusicScales::G);
    keyComboBox->addItem("G#", MusicScales::G_SHARP);

    keyLabel = new QLabel("&Key");
    keyLabel->setContentsMargins(10, 0, 5, 0);
    keyLabel->setBuddy(keyComboBox);

    scaleComboBox = new QComboBox;
    scaleComboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    scaleComboBox->addItem("major", MusicScales::MAJOR);
    scaleComboBox->addItem("major pentatonic", MusicScales::MAJOR_PENTATONIC);
    scaleComboBox->addItem("natural minor", MusicScales::NATURAL_MINOR);
    scaleComboBox->addItem("minor pentatonic", MusicScales::MINOR_PENTATONIC);
    scaleComboBox->addItem("harmonic minor", MusicScales::HARMONIC_MINOR);
    scaleComboBox->addItem("melodic minor", MusicScales::MELODIC_MINOR);
    scaleComboBox->addItem("blues", MusicScales::BLUES);
    scaleComboBox->addItem("whole tone", MusicScales::WHOLE_TONE);
    scaleComboBox->addItem("whole-half diminished", MusicScales::WHOLE_HALF_DIM);
    scaleComboBox->addItem("half-whole diminished", MusicScales::HALF_WHOLE_DIM);
    scaleComboBox->addItem("phrygian", MusicScales::PHRYGIAN);
    scaleComboBox->addItem("lydian", MusicScales::LYDIAN);
    scaleComboBox->addItem("mixolydian", MusicScales::MIXOLYDIAN);
    scaleComboBox->addItem("aeolian", MusicScales::AEOLIAN);
    scaleComboBox->addItem("locrian", MusicScales::LOCRIAN);

    scaleLabel = new QLabel("S&cale ");
    scaleLabel->setContentsMargins(10, 0, 2, 0);
    scaleLabel->setBuddy(scaleComboBox);

    tuningComboBox = new QComboBox;
    tuningComboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    tuningComboBox->addItem("Standard", MusicScales::STANDARD);
    tuningComboBox->addItem("Drop D", MusicScales::DROP_D);
    tuningComboBox->addItem("Open A", MusicScales::OPEN_A);
    tuningComboBox->addItem("Open B", MusicScales::OPEN_B);
    tuningComboBox->addItem("Open C", MusicScales::OPEN_C);
    tuningComboBox->addItem("Open D", MusicScales::OPEN_D);
    tuningComboBox->addItem("Open E", MusicScales::OPEN_E);
    tuningComboBox->addItem("Open F", MusicScales::OPEN_F);
    tuningComboBox->addItem("Open G", MusicScales::OPEN_G);

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
    MusicScales::Key key = MusicScales::Key(keyComboBox->itemData(
                keyComboBox->currentIndex(), IdRole).toInt()); //need to study this more
        musicScale->setKey(key);
}

void MainWindow::scaleChanged()
{
    MusicScales::Scale scale = MusicScales::Scale(scaleComboBox->itemData(
                scaleComboBox->currentIndex(), IdRole).toInt()); //need to study this more
        musicScale->setScale(scale);
}

void MainWindow::tuningChanged()
{
    MusicScales::Tuning tuning = MusicScales::Tuning(tuningComboBox->itemData(
                tuningComboBox->currentIndex(), IdRole).toInt()); //need to study this more
        musicScale->setTuning(tuning);
}

void MainWindow::tabMode()
{
    musicScale->tabMode();
}

void MainWindow::showScale()
{
    musicScale->drawScale();
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
