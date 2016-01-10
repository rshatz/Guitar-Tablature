#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>

#include "musicscales.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

private slots:

    void checkBoxState();

private:

    void createToolBar();

    QToolBar *selectionToolBar;

    QCheckBox *allNoteCheckBox;
    QComboBox *keyComboBox;
    QComboBox *scaleComboBox;
    QComboBox *tuningComboBox;

    QPushButton *submitButton;
    QPushButton *clearButton;

    QLabel *fretBoardImage;
    QLabel *keyLabel;
    QLabel *scaleLabel;
    QLabel *tuningLabel;

    MusicScales *musicScale;
};

#endif // MAINWINDOW_H
