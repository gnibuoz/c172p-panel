#ifndef NAVIGATIONINDICATOR_H
#define NAVIGATIONINDICATOR_H

#include <QObject>
#include <QWidget>
#include <QPixmap>
#include <QPoint>
#include <QMutex>
#include "fgdata.h"
#include "knob.h"

class NavigationIndicator : public QWidget, public FGDataConsumer, public FGDataUpdater
{
	Q_OBJECT
public:
	explicit NavigationIndicator(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void set_prefix(const QString &p) { prefix = p; }

public slots:
    void update_obs(Knob::direcrion d);

private:
    void load_img();

    QString prefix; // nav data name prefix
    bool has_gs;
    bool in_range;
    bool gs_in_range;
    bool to_flag;
    bool from_flag;
    double radial_selected;
    double heading_deflection;
    double gs_deflection;
    double old_heading_deflection;
    double old_gs_deflection;
    Knob k_obs;

    static QMutex img_lock;
    static bool loaded;
    static QPixmap * img_ring;
    static QPixmap * img_frame;
    static QPixmap * img_plate;
    static QPixmap * img_to_from_flag;
    static QPixmap * img_gs_flag;
    static const QPoint needle[4];
};

#endif // NAVIGATIONINDICATOR_H
