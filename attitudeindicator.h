#ifndef ATTITUDEINDICATOR_H
#define ATTITUDEINDICATOR_H

#include <QObject>
#include <QWidget>
#include <QPoint>
#include <QPixmap>
#include <QMutex>
#include "fgdata.h"
#include "knob.h"

class AttitudeIndicator : public QWidget, public FGDataConsumer, public FGDataUpdater
{
	Q_OBJECT
public:
	explicit AttitudeIndicator(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);

public slots:
    void update_offset(Knob::direcrion d);

private:
    double pitch_to_translate() { return ai_pitch * 2 + ai_pitch_offset; }
    void load_img();

    double ai_pitch;
    double ai_pitch_offset;
    double ai_roll;
    Knob k_offset;

    static QMutex img_lock;
    static bool loaded;
    static QPixmap * img_horizon2;
    static QPixmap * img_horizon3;
    static QPixmap * img_plane;
    static QPixmap * img_frame;
};

#endif // ATTITUDEINDICATOR_H
