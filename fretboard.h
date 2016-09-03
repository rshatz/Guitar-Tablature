#ifndef FRETBOARD_H
#define FRETBOARD_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

class Fretboard : public QWidget
{
    Q_OBJECT

public:

    Fretboard(QWidget *parent = 0);

    enum Key { A, A_SHARP, B, C, C_SHARP, D, D_SHARP, E, F, F_SHARP, G, G_SHARP };

    enum Scale { MAJOR, MAJOR_PENTATONIC, NATURAL_MINOR, MINOR_PENTATONIC,
         HARMONIC_MINOR, MELODIC_MINOR, BLUES, WHOLE_TONE,
         WHOLE_HALF_DIM, HALF_WHOLE_DIM, PHRYGIAN, LYDIAN,
         MIXOLYDIAN, AEOLIAN, LOCRIAN };

    enum Tuning { STANDARD, DROP_D, OPEN_A, OPEN_B, OPEN_C, OPEN_D,
           OPEN_E, OPEN_F, OPEN_G };

    void setKey(int scaleKey);
    void setScale(int scale);
    void setTuning(int tuning);
    void drawScale();
    void tabMode();

private:

    void clearFretboard();
    void buildScale();
    void testSlot(int string, int fret);//delete

    const QList<QString> noteList = QList<QString>()
            << "A" << "A#" << "B" << "C" << "C#" << "D"
            << "D#" << "E" << "F" << "F#" << "G" << "G#";

    QList<int> scaleDegrees;
    QList<int> scaleFormula;
    QList<int> tuningFormula;

    int *key;

    QLabel *fretBoardImage;
    QPushButton **fretBoardButton;

    bool fretBoardfilled;

    const int xCoordinate[13] = {20, 100, 190, 280, 370, 460, 553, 643,
                          733, 825, 915, 1010, 1100};
    const int yCoordinate[6] = {70, 114, 158, 202, 246, 290};
};

#endif // FRETBOARD_H
