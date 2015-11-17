#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QHBoxLayout>

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
    void createDockWindow();
    void changeScale();
    void setTuning();
    void major();
    void majorPentatonic();
    void naturalMinor();
    void minorPentatonic();
    void harmonicMinor();
    void melodicMinor();
    void blues();
    void wholeTone();
    void wholeHalfDim();
    void halfWholeDim();
    void phrygian();
    void lydian();
    void mixolydian();
    void aeolian();
    void locraian();
    void buildScale(const int scaleFormula[], const int size);
    void drawScale();

    enum { MAJOR, MAJOR_PENTATONIC, NATURAL_MINOR, MINOR_PENTATONIC,
         HARMONIC_MINOR, MELODIC_MINOR, BLUES, WHOLE_TONE,
         WHOLE_HALF_DIM, HALF_WHOLE_DIM, PHRYGIAN, LYDIAN,
         MIXOLYDIAN, AEOLIAN, LOCRIAN };

    enum { STANDARD, DROP_D, OPEN_A, OPEN_C, OPEN_D, OPEN_DM, OPEN_G };

    QWidget *topWindowWidget;

    QVector<int> scaleDegrees;
    int *tuningPositions;
    const static QString notes[];

    QToolBar *selectionToolBar;

    QComboBox *keyComboBox;
    QComboBox *scaleComboBox;
    QComboBox *tuningComboBox;

    QPushButton *submitButton;

    QDockWidget *fretBoardDock;
    QPlainTextEdit *tabSheet;

    QHBoxLayout *topLayout;
    QLabel **noteLabel;
    QLabel *fretBoardLabel;
    QLabel *keyLabel;
    QLabel *scaleLabel;
    QLabel *tuningLabel;
    QLabel *notesDisplayLabel;
};

#endif // MAINWINDOW_H
