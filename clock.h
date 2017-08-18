#ifndef CLOCK_H
#define CLOCK_H

#include <QObject>
#include <QWidget>
#include <QPaintEvent>
#include "fgdata.h"

class Clock : public QWidget, public FGDataConsumer
{
    Q_OBJECT
public:
    explicit Clock(QWidget * parent = 0);
    void paintEvent(QPaintEvent *);
};

#endif // CLOCK_H
