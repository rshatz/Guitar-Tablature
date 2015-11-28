#ifndef MUSICSCALES_H
#define MUSICSCALES_H

#include <QLabel>
#include <QComboBox>
#include <QToolBar>
#include <QPushButton>
#include <QDockWidget>
#include <QPlainTextEdit>

class MusicScales : public QWidget
{
    Q_OBJECT

public:

    MusicScales(QWidget *parent = 0);

    void setKey(int scaleKey);
    void setScale(int scale);
    void setTuning(int tuning);
    void drawScale();

private:

    void buildScale();
    void clearFretBoard();

    QLabel **fretBoardNotes;
    bool fretBoardfilled;

    int *key;

    enum Scale { MAJOR, MAJOR_PENTATONIC, NATURAL_MINOR, MINOR_PENTATONIC,
         HARMONIC_MINOR, MELODIC_MINOR, BLUES, WHOLE_TONE,
         WHOLE_HALF_DIM, HALF_WHOLE_DIM, PHRYGIAN, LYDIAN,
         MIXOLYDIAN, AEOLIAN, LOCRIAN };

    enum Tuning { STANDARD, DROP_D, OPEN_A, OPEN_B, OPEN_C, OPEN_D,
           OPEN_E, OPEN_F, OPEN_G };

    const QList<QString> noteList = QList<QString>()
            << "A" << "A#" << "B" << "C" << "C#" << "D"
            << "D#" << "E" << "F" << "F#" << "G" << "G#";

    QList<int> scaleDegrees;
    QList<int> scaleFormula;
    QList<int> tuningFormula;
};


#endif // MUSICSCALES_H
