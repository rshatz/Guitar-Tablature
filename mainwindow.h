#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>

#include "musicscales.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void keyChange();
    void scaleChange();
    void tuningChange();
    void drawScale();

private:

    void createToolBar();

    QToolBar *selectionToolBar;

    QComboBox *keyComboBox;
    QComboBox *scaleComboBox;
    QComboBox *tuningComboBox;

    QPushButton *submitButton;

    QLabel **noteLabels;
    QLabel *fretBoardLabel;
    QLabel *keyLabel;
    QLabel *scaleLabel;
    QLabel *tuningLabel;

    MusicScales *musicScale;
};

#endif // MAINWINDOW_H
