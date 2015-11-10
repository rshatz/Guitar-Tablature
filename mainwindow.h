#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QLabel>

#include <string>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:

    void scaleChanged();

private:

    void createToolBar();
    void majorDiatonic(int key);
    void majorPentatonic(int key);
    void minorDiatonic(int key);
    void minorPentatonic(int key);
    void writeScale();

    enum {MAJOR_DIATONIC, MAJOR_PENTATONIC, MINOR_DIATONIC, MINOR_PENTATONIC};

    QVector<int> scaleDegrees;
    const static QString notes[];

    QToolBar *selectionToolBar;

    QComboBox *keyComboBox;
    QComboBox *scaleComboBox;
    QComboBox *tuningComboBox;

    QLabel *keyLabel;
    QLabel *scaleLabel;
    QLabel *tuningLabel;
};

#endif // MAINWINDOW_H
