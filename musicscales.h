#ifndef MUSICSCALES_H
#define MUSICSCALES_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

class MusicScales : public QWidget
{
    Q_OBJECT

public:

    MusicScales(QWidget *parent = 0);

public slots:

    void setKey(int scaleKey);
    void setScale(int scale);
    void setTuning(int tuning);
    void drawScale();
    void drawAllNotes();
    void clearFretBoard();

    void testSlot(int string, int fret);//delete

private:

    void buildScale();

    enum { MAJOR, MAJOR_PENTATONIC, NATURAL_MINOR, MINOR_PENTATONIC,
         HARMONIC_MINOR, MELODIC_MINOR, BLUES, WHOLE_TONE,
         WHOLE_HALF_DIM, HALF_WHOLE_DIM, PHRYGIAN, LYDIAN,
         MIXOLYDIAN, AEOLIAN, LOCRIAN };

    enum { STANDARD, DROP_D, OPEN_A, OPEN_B, OPEN_C, OPEN_D,
           OPEN_E, OPEN_F, OPEN_G };

    const QList<QString> noteList = QList<QString>()
            << "A" << "A#" << "B" << "C" << "C#" << "D"
            << "D#" << "E" << "F" << "F#" << "G" << "G#";

    QList<int> scaleDegrees;
    QList<int> scaleFormula;
    QList<int> tuningFormula;

    QPushButton **fretBoardButton;
    bool fretBoardfilled;

    const int xCoordinate[13] = {20, 100, 190, 280, 370, 460, 553, 643,
                          733, 825, 915, 1010, 1100};
    const int yCoordinate[13] = {70, 114, 158, 202, 246, 290};

    int *key;
};

#endif // MUSICSCALES_H
