#ifndef AIRSPEEDINDICATOR_H
#define AIRSPEEDINDICATOR_H

#include <QObject>
#include <QWidget>
#include <QPoint>
#include <QPixmap>
#include <QMutex>
#include "fgdata.h"

class AirSpeedIndicator : public QWidget, public FGDataConsumer
{
	Q_OBJECT
public:
	explicit AirSpeedIndicator(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);

private:
    double scale_angle();
    void load_img();

    double asi_kt;
    static const QPoint needle[4];

    static QMutex img_lock;
    static bool loaded;
    static QPixmap * img_plate;
    static QPixmap * img_frame;

    static const double angle_scale_map[20][2];
};

#endif // AIRSPEEDINDICATOR_H
