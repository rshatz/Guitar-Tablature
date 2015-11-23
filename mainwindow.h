#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QPlainTextEdit>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:

    void submitPressed();

private:

    void createToolBar();
    void setScale();
    void setTuning();
    void buildScale();
    void drawScale();

    enum { MAJOR, MAJOR_PENTATONIC, NATURAL_MINOR, MINOR_PENTATONIC,
         HARMONIC_MINOR, MELODIC_MINOR, BLUES, WHOLE_TONE,
         WHOLE_HALF_DIM, HALF_WHOLE_DIM, PHRYGIAN, LYDIAN,
         MIXOLYDIAN, AEOLIAN, LOCRIAN };

    enum { STANDARD, DROP_D, OPEN_A, OPEN_B, OPEN_C, OPEN_D,
           OPEN_E, OPEN_F, OPEN_G };

    QVector<int> scaleDegrees;
    QList<int> scaleFormula;
    QList<int> tuningFormula;
    const static QString notes[];

    QToolBar *selectionToolBar;

    QComboBox *keyComboBox;
    QComboBox *scaleComboBox;
    QComboBox *tuningComboBox;

    QPushButton *submitButton;

    QDockWidget *fretBoardDock;
    QPlainTextEdit *tabSheet;

    QLabel **noteLabels;
    QLabel *fretBoardLabel;
    QLabel *keyLabel;
    QLabel *scaleLabel;
    QLabel *tuningLabel;
    QLabel *notesDisplayLabel;

    QLabel *noteOnDot;
};

#endif // MAINWINDOW_H
