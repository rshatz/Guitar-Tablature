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

    void keyChanged();
    void scaleChanged();
    void tuningChanged();
    void showScale();
    void tabMode();
    void checkBoxState();//delete?

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
