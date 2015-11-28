#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QPlainTextEdit>

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

    QDockWidget *fretBoardDock;

    QLabel **noteLabels;
    QLabel *fretBoardLabel;
    QLabel *keyLabel;
    QLabel *scaleLabel;
    QLabel *tuningLabel;

    QLabel *noteOnDot;

    MusicScales *musicScale;
};

#endif // MAINWINDOW_H
