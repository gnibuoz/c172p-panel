#ifndef TURNSLIPINDICATOR_H
#define TURNSLIPINDICATOR_H

#include <QObject>
#include <QWidget>
#include <QMutex>
#include <QPixmap>
#include "fgdata.h"

class TurnSlipIndicator : public QWidget, public FGDataConsumer
{
	Q_OBJECT
public:
	explicit TurnSlipIndicator(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);

private:
    double turn_to_angle();
    void load_img();

    double turn;
    double slip;
    double spin;

    static QMutex img_lock;
    static bool loaded;
    static QPixmap * img_plane;
    static QPixmap * img_frame;
    static QPixmap * img_plate;
};

#endif // TURNSLIPINDICATOR_H
