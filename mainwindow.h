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
    void majorScale(int key);
    void majorPent(int key);
    void minorScale(int key);
    void minorPent(int key);

    enum {MAJORDIAT, MAJORPENT, MINORDIAT, MINORPENT};

    QVector<int> *scaleDegrees;
    QString *notes;

    QToolBar *selectionToolBar;

    QComboBox *keyComboBox;
    QComboBox *scaleComboBox;
    QComboBox *tuningComboBox;

    QLabel *keyLabel;
    QLabel *scaleLabel;
    QLabel *tuningLabel;
};

#endif // MAINWINDOW_H
