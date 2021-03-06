#ifndef KNOB_H
#define KNOB_H

#include <QObject>
#include <QWidget>
#include <QWheelEvent>
#include <QPixmap>
#include <QString>

class Knob : public QWidget
{
    Q_OBJECT
public:
    explicit Knob(QWidget *parent, const QString &img);
    void wheelEvent(QWheelEvent *we);
    void paintEvent(QPaintEvent *);
    enum direcrion { LEFT, RIGHT};

signals:
    void rotated(Knob::direcrion);

private:
    int angle;
    QPixmap img_knob;
};

#endif // KNOB_H
