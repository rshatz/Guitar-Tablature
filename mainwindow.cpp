#include <QToolBar>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
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

    scaleComboBox = new QComboBox;
    scaleComboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    scaleComboBox->addItem("major");
    scaleComboBox->addItem("major pentatonic");
    scaleComboBox->addItem("minor");
    scaleComboBox->addItem("minor pentatonic");

    tuningComboBox = new QComboBox;

    tuningComboBox->addItem("standard");
    tuningComboBox->addItem("D#");
    tuningComboBox->addItem("Drop D");

    QGridLayout *rightSideLayout = new QGridLayout;

    keyLabel = new QLabel("&key");
    keyLabel->setBuddy(keyComboBox);

    scaleLabel = new QLabel("&scale");
    scaleLabel->setBuddy(scaleComboBox);

    tuningLabel = new QLabel("&tuning");
    tuningLabel->setBuddy(tuningComboBox);

    rightSideLayout->addWidget(keyLabel, 0, 0, Qt::AlignRight);
    rightSideLayout->addWidget(keyComboBox, 0, 1);
    rightSideLayout->addWidget(scaleLabel, 1, 0, Qt::AlignRight);
    rightSideLayout->addWidget(scaleComboBox, 1, 1);
    rightSideLayout->addWidget(tuningLabel, 2, 0, Qt::AlignRight);
    rightSideLayout->addWidget(tuningComboBox);

    tabSheet = new QPlainTextEdit;

    QVBoxLayout *leftSideLayout = new QVBoxLayout;

    leftSideLayout->addWidget(tabSheet);

    QHBoxLayout *mainLayout = new QHBoxLayout;

    mainLayout->addLayout(leftSideLayout);
    mainLayout->addLayout(rightSideLayout);

    QWidget *window = new QWidget(this);

    window->setLayout(mainLayout);
    setCentralWidget(window);
}

MainWindow::~MainWindow()
{

}
